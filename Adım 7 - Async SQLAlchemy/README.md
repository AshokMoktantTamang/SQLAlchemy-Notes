## Adım 7 – Async SQLAlchemy

Bu adım, **asyncio** tabanlı uygulamalarda (FastAPI, aiohttp vb.) SQLAlchemy’nin **async engine** ve **AsyncSession** kullanımına odaklanır.

Kapsanan konular:

- `create_async_engine` ve async bağlantı URL’leri (aiosqlite, asyncpg)  
- `AsyncSession` ve `async_sessionmaker`  
- Async ortamda `select`, `execute`, `scalars` kullanımı  
- Lazy loading kısıtı ve eager loading zorunluluğu  
- `run_sync()` ile senkron kod çalıştırma  
- FastAPI ile dependency injection örneği  

Önceki adımlardaki ORM kavramları (Session, transaction, relationship) aynı kalır; fark **await** ve **async with** kullanımıdır.

---

### 1. Neden Async?

- **I/O-bound** işlerde (veritabanı, HTTP) thread bloklamadan diğer istekler işlenebilir.  
- FastAPI / Starlette gibi async framework’lerle uyumlu.  
- Çok sayıda eşzamanlı bağlantıda kaynak kullanımı genelde senkron pool’a göre daha verimli olabilir.  

Async kullanmak **zorunlu** değildir; senkron SQLAlchemy de production’da yaygındır. Proje async ise bu adım rehber niteliğindedir.

---

### 2. Async Engine ve URL

Async engine için **async destekleyen bir sürücü** gerekir:

| Veritabanı   | Async URL örneği                          | Sürücü   |
|-------------|-------------------------------------------|----------|
| SQLite      | `sqlite+aiosqlite:///db.sqlite`           | aiosqlite |
| PostgreSQL  | `postgresql+asyncpg://user:pass@host/db`  | asyncpg  |
| MySQL       | `mysql+aiomysql://...` veya `mysql+asyncmy://...` | aiomysql / asyncmy |

```python
from sqlalchemy.ext.asyncio import create_async_engine

# SQLite (demo / test)
engine = create_async_engine(
    "sqlite+aiosqlite:///async_demo.db",
    echo=True,
)

# PostgreSQL (production)
# engine = create_async_engine(
#     "postgresql+asyncpg://user:pass@localhost:5432/dbname",
#     echo=False,
#     pool_size=10,
#     max_overflow=20,
# )
```

**Not:** Bu adımdaki demolar SQLite + aiosqlite kullanır. Çalıştırmak için:

```bash
pip install aiosqlite greenlet
```

veya:

```bash
pip install -r requirements-async.txt
```

---

### 3. AsyncSession ve async_sessionmaker

Session factory, **async** kullanacak şekilde `AsyncSession` ile kurulur:

```python
from sqlalchemy.ext.asyncio import AsyncSession, async_sessionmaker, create_async_engine

engine = create_async_engine("sqlite+aiosqlite:///async_demo.db", echo=False)

AsyncSessionLocal = async_sessionmaker(
    bind=engine,
    class_=AsyncSession,
    expire_on_commit=False,
    autoflush=False,
    autocommit=False,
)
```

- **expire_on_commit=False:** Commit sonrası nesnelerin attribute’larına erişirken sessizce tekrar sorgu atılmaz; async’te lazy re-load desteklenmediği için bu ayar önerilir.  
- **async with AsyncSessionLocal() as session:** Session’ı context manager ile alıp iş bitince kapatmak yeterli.

---

### 4. Sorgulama: execute, scalars, scalar_one_or_none

Tüm veritabanı erişimi **await** ile yapılır:

```python
from sqlalchemy import select

async with AsyncSessionLocal() as session:
    result = await session.execute(select(User).where(User.id == 1))
    user = result.scalar_one_or_none()

    result = await session.execute(select(User).order_by(User.id))
    users = result.scalars().all()
```

- `session.get(User, id)` de kullanılabilir: `user = await session.get(User, 1)`  
- `result.scalars()` → tek sütun/entity listesi; `.all()`, `.first()` vb.  
- `result.scalar_one_or_none()` → tek nesne veya None  
- `result.scalar_one()` → tek nesne; yoksa veya birden fazlaysa hata.

---

### 5. Ekleme, Güncelleme, Silme

```python
async with AsyncSessionLocal() as session:
    async with session.begin():
        user = User(name="Ali", email="ali@example.com")
        session.add(user)
        # begin() bloğu bitince otomatik commit
```

Veya:

```python
async with AsyncSessionLocal() as session:
    session.add(User(name="Ayşe", email="ayse@example.com"))
    await session.commit()
```

Güncelleme: nesneyi çekip attribute atayıp `commit`. Silme: `await session.delete(obj)` ardından `await session.commit()`.

---

### 6. Lazy Loading Kullanılamaz

AsyncSession’da **lazy loading** (ilişkiye ilk erişimde sessizce ek sorgu) **yapılmaz**; böyle bir erişim hata veya beklenmeyen davranış üretir.

Çözüm: İlişkileri her zaman **eager loading** ile yükleyin:

```python
from sqlalchemy.orm import selectinload

result = await session.execute(
    select(User).options(selectinload(User.orders)).where(User.id == 1)
)
user = result.scalar_one()
# user.orders artık yüklü; ek sorgu yok
```

`joinedload`, `contains_eager` da kullanılabilir (Adım 3–4’te anlatıldığı gibi).

---

### 7. run_sync() – Senkron Kod Çalıştırma

Bazen mevcut senkron fonksiyonu (ör. `Base.metadata.create_all`) async session/connection içinde çalıştırmak gerekir. Bunun için **run_sync** kullanılır:

```python
from sqlalchemy import text
from sqlalchemy.ext.asyncio import AsyncSession

async def init_db(async_engine):
    async with async_engine.begin() as conn:
        await conn.run_sync(Base.metadata.create_all)
```

Session içinde de:

```python
async with AsyncSessionLocal() as session:
    await session.run_sync(some_sync_function)
```

`run_sync` içinde verilen fonksiyon, sync connection/session alır; bu fonksiyon async değildir.

---

### 8. FastAPI ile Kullanım

Her istek için bir AsyncSession üretip dependency olarak enjekte etmek yaygındır:

```python
from fastapi import Depends
from sqlalchemy.ext.asyncio import AsyncSession

async def get_db() -> AsyncSession:
    async with AsyncSessionLocal() as session:
        try:
            yield session
            await session.commit()
        except Exception:
            await session.rollback()
            raise
        finally:
            await session.close()

@router.get("/users/{user_id}")
async def read_user(user_id: int, db: AsyncSession = Depends(get_db)):
    result = await db.execute(select(User).where(User.id == user_id))
    user = result.scalar_one_or_none()
    if not user:
        raise HTTPException(404)
    return user
```

---

### 9. Özet – Async Kontrol Listesi

- [ ] Bağlantı URL’i async sürücülü mü? (`sqlite+aiosqlite`, `postgresql+asyncpg` vb.)  
- [ ] `create_async_engine` ve `async_sessionmaker(..., class_=AsyncSession)` kullanıldı mı?  
- [ ] Tüm DB erişimi `await session.execute` / `await session.commit` ile mi?  
- [ ] İlişkiler için lazy’e güvenilmiyor mu? (selectinload / joinedload kullanılıyor mu?)  
- [ ] `expire_on_commit=False` ayarlandı mı?  
- [ ] Session her istekte açılıp kapatılıyor mu? (async with)  

Bu adımın sonunda, FastAPI veya başka bir async framework içinde SQLAlchemy’yi **AsyncSession** ile güvenle kullanmaya hazır olmalısınız.

---

### 10. Demo Scriptleri ve Gereksinimler

Bu dizindeki örnekleri çalıştırmak için önce async SQLite sürücüsünü ve greenlet'i kurun:

```bash
pip install -r requirements-async.txt
```

Ardından:

```bash
cd "Adım 7 - Async SQLAlchemy"
python demo_async_basic.py
python demo_async_session_context.py
```

- **database_async.py** – `create_async_engine`, `async_sessionmaker`, `init_db` (run_sync ile).  
- **models.py** – Async demo için basit `AsyncUser` modeli.  
- **demo_async_basic.py** – Tek bir async fonksiyonda create/select.  
- **demo_async_session_context.py** – Context manager ile session yaşam döngüsü.
