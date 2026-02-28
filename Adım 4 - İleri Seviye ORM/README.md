## Adım 4 – İleri Seviye SQLAlchemy ORM

Bu adım, SQLAlchemy ORM’i üretim düzeyinde yöneten, performans ve mimari kararları bilinçle alan seviye içindir.

Kapsadığı konular:

- Gelişmiş loading stratejileri (`selectinload`, `joinedload`, `contains_eager`)  
- Hybrid property ve SQL/Python birleşik hesaplamaları  
- Association proxy ve ilişki kısayolları  
- Polymorphic mapping (kalıtım / çok-biçimlilik)  
- Modern (2.x) query API: `select`, subquery, `exists`, CTE  
- Event sistemi (lifecycle hook’lar)  
- Soft delete ve global filtreler  
- Çok kiracılı (multi-tenant) mimari desenleri  
- Bulk operasyonlar ve Core ile birlikte çalışma  
- Async ORM kullanımı  

Bu bir “özellik listesi” değil; **mimari ustalık** için rehberdir.

---

### 1. Gelişmiş Loading Stratejileri

ORM ustalığı büyük ölçüde **hangi sorgunun ne zaman ve nasıl üretildiğini** kontrol edebilmekle ilgilidir.

#### 1.1 `joinedload` – JOIN ile Eager Loading

```python
from sqlalchemy.orm import joinedload

users = (
    session.query(User)
    .options(joinedload(User.orders))
    .all()
)
```

- Avantaj: Tek sorgu ile hem `User` hem `Order` kayıtları gelir.  
- Dezavantaj: Büyük veri setlerinde **row explosion** (satır patlaması) riski:
  - 1000 kullanıcı × kişi başı 100 sipariş → 100.000 satırlık JOIN sonucu.

#### 1.2 `selectinload` – Dengeli Eager Loading (Genelde Önerilen)

```python
from sqlalchemy.orm import selectinload

users = (
    session.query(User)
    .options(selectinload(User.orders))
    .all()
)
```

Çalışma mantığı:

1. İlk sorguda tüm kullanıcılar alınır.  
2. İkinci sorguda `orders` tablosu, `WHERE user_id IN (...)` filtresi ile tek seferde taranır.  

Sonuç:

- N+1 problemi yok.  
- Row explosion yok.  

#### 1.3 `contains_eager` – Manuel JOIN Kontrolü

Eğer JOIN’i kendiniz yazmak istiyor ama sonucu ORM ilişki alanlarına bağlamak istiyorsanız:

```python
from sqlalchemy.orm import contains_eager

q = (
    session.query(User)
    .join(User.orders)
    .options(contains_eager(User.orders))
)
users = q.all()
```

- Burada JOIN açıkça siz yazarsınız.  
- `contains_eager`, JOIN sonucunu `User.orders` alanına eşler; ek SELECT tetiklenmez.  

Bu, ileri seviye performans kontrolü sağlar.

---

### 2. Hybrid Property – Python + SQL Hesaplamaları

Hybrid property, aynı hesaplamayı:

- Python tarafında attribute gibi (`obj.total`),  
- SQL tarafında expression gibi (`Order.total > 100`)  

kullanmanıza olanak tanır.

```python
from sqlalchemy import Column, Integer
from sqlalchemy.ext.hybrid import hybrid_property

class Order(Base):
    __tablename__ = "orders"

    id = Column(Integer, primary_key=True)
    price = Column(Integer)
    tax = Column(Integer)

    @hybrid_property
    def total(self):
        return self.price + self.tax

    @total.expression
    def total(cls):
        return cls.price + cls.tax
```

Kullanım:

```python
order = session.get(Order, 1)
print(order.total)  # Python tarafı

high_value_orders = (
    session.query(Order)
    .filter(Order.total > 100)
    .all()           # SQL tarafı
)
```

ORM ustalığının önemli göstergelerinden biridir.

---

### 3. Association Proxy – İlişki Kısayolları

Ara model üzerinden dolanmak yerine, direkt ilişkiye erişim için kullanılır.

Örneğin `Student` → `Enrollment` → `Course` zincirinde:

```python
from sqlalchemy.ext.associationproxy import association_proxy

class Student(Base):
    __tablename__ = "students"
    id = Column(Integer, primary_key=True)
    name = Column(String)

    enrollments = relationship("Enrollment", back_populates="student")
    courses = association_proxy("enrollments", "course")


class Enrollment(Base):
    __tablename__ = "enrollments"
    id = Column(Integer, primary_key=True)
    student_id = Column(ForeignKey("students.id"))
    course_id = Column(ForeignKey("courses.id"))

    student = relationship("Student", back_populates="enrollments")
    course = relationship("Course")
```

Artık:

```python
student = session.get(Student, 1)
print(student.courses)  # Enrollment üzerinden dolanmadan Course listesi
```

---

### 4. Polymorphic Mapping (Kalıtım / Çok-Biçimlilik)

Tek tabloda farklı alt tipler saklamak için kullanılabilir.

```python
class Animal(Base):
    __tablename__ = "animals"

    id = Column(Integer, primary_key=True)
    type = Column(String)

    __mapper_args__ = {
        "polymorphic_on": type,
        "polymorphic_identity": "animal",
    }


class Dog(Animal):
    __mapper_args__ = {
        "polymorphic_identity": "dog",
    }
```

Kullanım:

```python
session.add(Dog(type="dog"))
session.commit()

animals = session.query(Animal).all()
for a in animals:
    print(type(a), a.type)  # <class 'Dog'>, "dog" olabilir
```

Bu yaklaşım, domain’inizde kalıtım hiyerarşisi varsa ve veritabanında tek tablo ile temsil etmek istiyorsanız kullanışlıdır.

---

### 5. Modern Query API (2.x Stili) – `select`, Subquery, `exists`, CTE

#### 5.1 Temel `select`

```python
from sqlalchemy import select

stmt = select(User).where(User.name == "Ali")
result = session.execute(stmt)
users = result.scalars().all()
```

#### 5.2 JOIN ile filtre

```python
stmt = (
    select(User)
    .join(User.orders)
    .where(Order.amount > 100)
)
users = session.execute(stmt).scalars().all()
```

#### 5.3 Subquery örneği

```python
from sqlalchemy import func

subq = (
    select(Order.user_id)
    .group_by(Order.user_id)
    .having(func.count(Order.id) > 5)
).subquery()

stmt = select(User).where(User.id.in_(subq))
power_users = session.execute(stmt).scalars().all()
```

#### 5.4 `exists` örneği

```python
from sqlalchemy import exists

stmt = select(User).where(
    exists().where(Order.user_id == User.id)
)
users_with_orders = session.execute(stmt).scalars().all()
```

Bu yapılar, ORM ile ileri seviye sorgu tasarımında temel araçlardır.

---

### 6. Event Sistemi (Lifecycle Hook’lar)

SQLAlchemy, çeşitli noktalara “hook” eklemenize izin veren bir event sistemi sunar.

Örneğin insert öncesi isim formatlamak:

```python
from sqlalchemy import event

@event.listens_for(User, "before_insert")
def before_insert_user(mapper, connection, target):
    # target → eklenecek User nesnesi
    target.name = target.name.strip().upper()
```

Event sistemi ile:

- Audit/logging,  
- Otomatik alan doldurma (ör. slug, timestamp),  
- Güvenlik kontrolleri  

gibi işlemler merkezi ve tutarlı şekilde uygulanabilir.

---

### 7. Soft Delete Pattern

Gerçek sistemlerde sıkça, kayıtlar fiziksel olarak silinmez; **soft delete** uygulanır.

Basit bir desen:

```python
class BaseModel(Base):
    __abstract__ = True
    id = Column(Integer, primary_key=True)
    deleted = Column(Boolean, default=False, nullable=False)


class User(BaseModel):
    __tablename__ = "users"
    name = Column(String)
```

Silme yerine:

```python
user.deleted = True
session.commit()
```

Tüm sorgular için global filtre de eklenebilir (örneğin event veya custom query sınıfları ile), böylece:

```python
session.query(User)  # deleted=False varsayılanı ile çalışır
```

Geri alma, log tutma ve hukuki gereklilikler açısından soft delete production’da çok yaygındır.

---

### 8. Multi-Tenant Pattern (Çok Kiracılı Mimari)

Her kayıt için kiracı/tenant bilgisi tutulur:

```python
class TenantScoped(Base):
    __abstract__ = True
    tenant_id = Column(Integer, index=True, nullable=False)
```

Tüm modeller bu sınıftan türetilebilir.  
Ardından:

- Global filter ile her sorguya otomatik `tenant_id = current_tenant` koşulu eklenebilir.  
- Bu, event sistemi veya custom `Session` / `Query` sınıflarıyla uygulanabilir.

---

### 9. Bulk Operasyonlar ve Core ile Birlikte Kullanım

ORM, tekil nesneler için idealdir; ancak çok büyük toplu işlemlerde (ör. yüz binlerce satır) doğrudan Core veya bulk API’ler kullanılabilir:

```python
session.bulk_save_objects(
    [User(name=f"user_{i}") for i in range(100000)]
)
session.commit()
```

Veya Core ile:

```python
from sqlalchemy import insert

stmt = insert(User).values([{"name": f"user_{i}"} for i in range(100000)])
session.execute(stmt)
session.commit()
```

Bu, ORM’in esnek katmanlı yapısının bir avantajıdır: Gerektiğinde daha düşük seviyeye inebilirsiniz.

---

### 10. Async ORM

Modern web uygulamalarında, özellikle FastAPI gibi async framework’lerde **async engine** ve **AsyncSession** kullanımı önem kazanır.

Basit örnek:

```python
from sqlalchemy.ext.asyncio import create_async_engine, AsyncSession
from sqlalchemy.orm import sessionmaker

engine = create_async_engine(
    "postgresql+asyncpg://user:pass@localhost/dbname",
    echo=False,
)

AsyncSessionLocal = sessionmaker(
    bind=engine,
    class_=AsyncSession,
    expire_on_commit=False,
)


async def get_user(user_id: int) -> User:
    async with AsyncSessionLocal() as session:
        result = await session.execute(
            select(User).where(User.id == user_id)
        )
        return result.scalar_one_or_none()
```

Async ORM:

- I/O-bound işlerde kaynak kullanımını iyileştirir.  
- Ancak Session, transaction ve relationship kavramları temelde aynıdır; sadece `await` ve async context kullanılır.

---

### 11. İleri Seviye ORM Ustalık Ölçütü

Bu adımın hedefi, aşağıdakileri **rahatlıkla** yapabilir hale gelmektir:

- N+1 problemini tespit edip `selectinload` / `joinedload` / `contains_eager` ile çözebilmek.  
- Hybrid property yazarak hem Python hem SQL tarafında aynı mantığı kullanabilmek.  
- Many-to-Many için association object pattern’ı uygun şekilde kurabilmek.  
- `select`, subquery, `exists`, CTE gibi yapıları ORM ile doğal biçimde kullanabilmek.  
- Session lifecycle’ını, Unit of Work mantığını ve Identity Map’i açıklayabilmek.  
- Event sistemi ile lifecycle hook’lar ekleyebilmek.  
- Soft delete ve multi-tenant gibi yaygın mimari desenleri ORM ile entegre edebilmek.  

Adım 4’teki örnekler ve açıklamalar, bu hedefe yönelik olarak derinlemesine pratik ve kavramsal temel sunmayı amaçlar. Gerçek projelerde, bu tekniklerin her birini tek seferde değil, **ihtiyaç ortaya çıktıkça ve ölçümle (profiling, query log, explain plan) destekleyerek** kullanmak en iyi yaklaşımdır.

