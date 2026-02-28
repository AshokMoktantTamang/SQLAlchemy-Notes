## Adım 6 – Performance & Production

Bu adım, SQLAlchemy tabanlı uygulamaları **yüksek performans** ve **production ortamı** için hazırlamaya odaklanır.

Kapsanan konular:

- Connection pool yapılandırması ve performans parametreleri  
- N+1’den kaçınma ve eager loading stratejileri (özet)  
- Bulk insert/update ve toplu işlemler  
- İndeks kullanımı ve sorgu optimizasyonu  
- Production için Session yaşam döngüsü (request-scoped)  
- Hata yönetimi, yeniden deneme ve transaction sınırları  
- Loglama ve izleme  
- Veritabanı sağlık kontrolü (health check)  
- Ölçekleme ve güvenlik notları  

Bu adım, önceki adımlardaki ORM, relationship ve migration bilgisini **canlı sistem** gereksinimleriyle birleştirir.

---

### 1. Connection Pool Yapılandırması

Engine, varsayılan olarak bir **connection pool** kullanır. Production’da bu parametreler bilinçli ayarlanmalıdır.

#### 1.1 Temel Parametreler

```python
from sqlalchemy import create_engine

engine = create_engine(
    "postgresql+psycopg2://user:pass@localhost:5432/dbname",
    pool_size=10,           # Havuzda sabit tutulacak bağlantı sayısı
    max_overflow=20,        # pool_size doluysa ek açılabilecek bağlantı
    pool_timeout=30,       # Havuzdan bağlantı bekleme süresi (saniye)
    pool_recycle=1800,     # 30 dk'dan eski bağlantıyı yenile (idle timeout önlemi)
    pool_pre_ping=True,    # Kullanımdan önce bağlantıyı test et (stale connection önlemi)
    echo=False,            # Production'da SQL loglama genelde kapatılır
    future=True,
)
```

- **pool_size:** Eşzamanlı istek sayısına göre seçilir; DB sunucusunun `max_connections` limitini aşmamalıdır.  
- **max_overflow:** Ani trafik artışlarında ek bağlantı; toplam üst sınır `pool_size + max_overflow`.  
- **pool_recycle:** Bulut veya proxy arkasındaki DB’lerde idle timeout ile kopan bağlantıları önlemek için kullanılır.  
- **pool_pre_ping:** Havuzdan alınan bağlantının hâlâ geçerli olup olmadığını kontrol eder; “connection already closed” benzeri hataları azaltır.

#### 1.2 SQLite Notu

SQLite varsayılan olarak tek bağlantılı bir “pool” kullanır. Geliştirme ve demo için uygundur; production’da genelde PostgreSQL/MySQL kullanılır.

---

### 2. N+1 ve Eager Loading (Özet)

N+1 problemi: Ana varlıkları çektikten sonra her biri için ilişkili veriyi ayrı sorguda çekmek.

**Çözüm:** İlişkiyi tek seferde yükleyen stratejiler (Adım 3 ve 4’te detaylı anlatıldı):

- `selectinload(Entity.relation)` – İkinci bir `WHERE id IN (...)` sorgusu ile ilişkiyi doldurur; row explosion yok.  
- `joinedload(Entity.relation)` – JOIN ile tek sorguda getirir; ilişki büyükse satır patlamasına dikkat.  
- `contains_eager(Entity.relation)` – Kendi yazdığınız JOIN’i ilişkiye eşler.

Production’da hangi endpoint’te hangi ilişkinin yükleneceğini açıkça seçmek (lazy’e güvenmemek) en iyi pratiktir.

---

### 3. Bulk ve Toplu İşlemler

Çok sayıda kayıt eklerken veya güncellerken tek tek INSERT/UPDATE yerine toplu işlem kullanmak performansı ciddi şekilde artırır.

#### 3.1 Toplu INSERT (add_all + flush)

```python
session.add_all([Model(...) for _ in range(1000)])
session.commit()
```

Session bir flush’ta birçok INSERT’i batch’leyebilir; sürücü ve SQLAlchemy sürümüne bağlı olarak `insertmanyvalues` vb. kullanılabilir.

#### 3.2 Core ile Bulk Insert

Sadece INSERT yapıyorsanız ve ORM nesnesine ihtiyacınız yoksa, Core API ile daha da hızlı olabilir:

```python
from sqlalchemy import insert

stmt = insert(MyTable).values([{"name": f"item_{i}"} for i in range(5000)])
with engine.connect() as conn:
    conn.execute(stmt)
    conn.commit()
```

#### 3.3 Toplu Güncelleme (bulk update)

Belirli koşula uyan tüm satırları güncellemek için tek UPDATE kullanın; döngü içinde tek tek `session.get` + attribute ataması yapmayın.

```python
from sqlalchemy import update

stmt = update(MyTable).where(MyTable.status == "pending").values(status="processed")
session.execute(stmt)
session.commit()
```

---

### 4. İndeks ve Sorgu Optimizasyonu

- **Sık filtre/sıralama yapılan kolonlara index ekleyin:** `Column(..., index=True)` veya migration ile `op.create_index(...)`.  
- **Büyük tablolarda LIMIT kullanın:** Sınırsız `query.all()` yerine `limit`/`offset` veya sayfalama.  
- **Sadece ihtiyaç duyulan kolonları çekin:** `load_only(Entity.col1, Entity.col2)` veya Core `select(Table.c.col1, ...)`.  
- **COUNT(*) yerine daha hafif alternatifler:** Var/yok kontrolü için `exists()` yeterli olabilir.

---

### 5. Production İçin Session Yaşam Döngüsü

- **Request-scoped Session:** Her HTTP isteği için yeni bir Session açın; işlem bitince mutlaka `close()` veya context manager ile kapatın.  
- **Global veya paylaşılan Session kullanmayın:** Thread-safety ve bellek sızıntısı riski.  
- **Transaction sınırı:** Bir istek genelde tek transaction (bir `commit` veya bir `rollback`).

Örnek (FastAPI/Flask benzeri):

```python
from contextlib import contextmanager

@contextmanager
def get_db_session():
    session = SessionLocal()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()

# İstek içinde:
with get_db_session() as session:
    user = session.get(User, user_id)
    ...
```

---

### 6. Hata Yönetimi ve Yeniden Deneme

- **DB bağlantı hataları:** Geçici ağ veya “too many connections” durumunda kısa backoff ile yeniden deneme yararlı olabilir.  
- **Deadlock / serialization hataları:** Transaction’ı tekrar deneyin (yeniden deneme sayısı sınırlı).  
- **Session.rollback():** Her exception path’inde Session’ı kapatmadan önce rollback çağırın; bir sonraki kullanımda “rollback required” hatalarını önler.

---

### 7. Loglama ve İzleme

- **echo:** Geliştirmede `echo=True` SQL’i gösterir; production’da genelde `echo=False`.  
- **Structured logging:** `logging` modülü ile SQLAlchemy engine loglarını uygun seviyede (WARNING/INFO) yakalayıp merkezi log sistemine gönderin.  
- **Yavaş sorgu izleme:** `engine.events` veya middleware ile sorgu süresini ölçüp eşik aşanları işaretleyebilirsiniz.

---

### 8. Veritabanı Sağlık Kontrolü (Health Check)

Liveness/readiness probe’larında DB’nin erişilebilir olduğunu doğrulayın:

```python
def db_health_check(engine) -> bool:
    try:
        with engine.connect() as conn:
            conn.execute(text("SELECT 1"))
        return True
    except Exception:
        return False
```

---

### 9. Ölçekleme ve Güvenlik Notları

- **Read replica:** Sadece okuma sorguları için ayrı bir engine (replica URL) kullanılabilir; yazma tek bir primary’de kalır.  
- **Bağlantı limiti:** Uygulama instance başına pool toplamı, DB’nin `max_connections` değerinin altında kalmalıdır.  
- **URL ve şifreler:** `sqlalchemy.url` ve şifreler ortam değişkeninden veya güvenli config’den okunmalı; kod içine sabit yazılmamalıdır.  
- **SQL injection:** ORM ve parametreli Core sorguları kullanın; kullanıcı girdisini raw SQL’e birleştirmeyin.

---

### 10. Özet – Performance & Production Kontrol Listesi

- [ ] Engine’de `pool_size`, `max_overflow`, `pool_recycle`, `pool_pre_ping` production’a uygun ayarlandı mı?  
- [ ] Session istek bazlı açılıp kapatılıyor mu?  
- [ ] N+1 önlemek için gerekli yerlerde `selectinload`/`joinedload` kullanılıyor mu?  
- [ ] Büyük veri setleri için bulk insert/update ve LIMIT kullanılıyor mu?  
- [ ] Kritik filtre/sıralama kolonlarında indeks var mı?  
- [ ] Hata durumunda `rollback` ve Session kapatma yapılıyor mu?  
- [ ] Health check endpoint’i DB bağlantısını test ediyor mu?  
- [ ] Veritabanı URL ve hassas bilgiler ortam değişkeninden mi okunuyor?  

Bu adımın sonunda, SQLAlchemy uygulamanızı hem **performanslı** hem de **production’da güvenle çalışacak** şekilde yapılandırmaya hazır olmalısınız.

---

### 11. Demo Scriptleri

Bu dizindeki örnekleri çalıştırmak için (proje kökünden):

```bash
cd "Adım 6 - Performance&Production"

# Pool yapılandırması ve health check
python demo_pool_and_health.py

# Request-scoped Session ve hata yönetimi
python demo_session_lifecycle.py

# Toplu ekleme: add_all vs Core insert
python demo_bulk_insert.py
```

- **database.py** – Production tarzı pool parametreleri ve `session_scope()` context manager.  
- **models.py** – Bulk demo için `Product` modeli.  
- **demo_pool_and_health.py** – Health check ve pool durumu.  
- **demo_session_lifecycle.py** – Başarılı/hatalı istekte Session yaşam döngüsü.  
- **demo_bulk_insert.py** – `add_all` ile ORM ve Core `insert()` ile toplu ekleme karşılaştırması.
