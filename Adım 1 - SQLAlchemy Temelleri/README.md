## Adım 1 – SQLAlchemy Temelleri

Bu klasör, **SQLAlchemy ORM’i mimari düzeyde anlayarak** kullanmak isteyen geliştiriciler için hazırlanmıştır.  
Adım 0’daki veri tabanı ve SQL ön gereksinimlerini tamamladığınız varsayılarak, burada SQLAlchemy’nin katmanlı yapısı, temel bileşenleri ve çalışma akışı sistematik biçimde açıklanır.

Amaç:

- SQLAlchemy’yi yalnızca “kullanan” değil, **iç mimarisini anlayan** bir bakış açısı kazandırmak,  
- İleride ORM davranışını (performans, transaction, relationship’ler vb.) bilinçli yönetebilmenizi sağlamaktır.

---

### 1. SQLAlchemy’nin Katmanlı Mimarisi

SQLAlchemy, kabaca aşağıdaki katmanlardan oluşan bir mimariye sahiptir:

1. **DBAPI** (en alt, sürücü katmanı)  
2. **SQLAlchemy Core** (SQL üretim ve yürütme katmanı)  
3. **SQLAlchemy ORM** (Python sınıfları ile tablo eşleme katmanı)  

Genel akış, alt seviyeden üst seviyeye doğru şu şekilde okunabilir:

- **DBAPI**: Ham SQL’i veri tabanına ileten Python sürücüleridir (ör. `sqlite3`, `psycopg2`, `mysqlclient`).  
- **Core**: Python ifadelerinden SQL üreten ve yürüten altyapıdır; engine, connection, SQL Expression Language gibi bileşenleri içerir.  
- **ORM**: Python sınıflarını tablolara eşler; session, mapped class’lar, relationship’ler ve Unit of Work mantığını barındırır.  

ORM katmanı, Core’un üzerine kuruludur; yani ORM kullanırken de perde arkasında Core ve DBAPI birlikte çalışır.

---

### 2. DBAPI Katmanı

DBAPI (Database API), Python’un veri tabanı sürücüleri için tanımladığı standart arayüzdür.

Örnek DBAPI uygulamaları:

- `sqlite3` (SQLite)  
- `psycopg2` (PostgreSQL)  
- `mysqlclient` (MySQL)  

DBAPI’nin sorumlulukları:

- Veri tabanına bağlantı açmak,  
- Ham SQL metnini veri tabanına göndermek,  
- Sonuçları Python tarafına döndürmek.  

DBAPI:

- SQL üretmez,  
- ORM veya model bilgisi içermez,  
- Sadece verilen SQL’i çalıştırır.  

SQLAlchemy, bu katmanın üzerine ek bir soyutlama getirerek Core ve ORM katmanlarını inşa eder.

---

### 3. SQLAlchemy Core Katmanı

Core, SQLAlchemy’nin SQL üretim ve yürütme altyapısıdır. ORM dâhil tüm üst seviye katmanlar, Core üzerine kuruludur.

Core katmanının temel bileşenleri:

- **Engine**  
- **Connection**  
- **Transaction** (low-level)  
- **SQL Expression Language** (ifadelerden SQL üretimi)  
- **Table** ve şema tanımları  
- **Dialect** (veri tabanı türüne göre SQL farklarını yöneten katman)  

#### 3.1 Dialect

Farklı veri tabanları (SQLite, PostgreSQL, MySQL vb.) SQL sözdizimi ve özellikleri bakımından farklılık gösterir.  
Dialect bileşeni, bu farkları soyutlayarak:

- Aynı ORM/Core kodunun, farklı veri tabanları için uygun SQL üretmesini sağlar.  
- Örneğin, bir yerde `SERIAL`, başka bir yerde `INTEGER PRIMARY KEY` kullanılması gerektiğini kendisi yönetir.  

---

### 4. Engine – Bağlantı Fabrikası

Engine, SQLAlchemy’nin veri tabanına erişim kapısıdır.

Tanım:

> Engine, veri tabanı bağlantı havuzunu ve ilgili DBAPI sürücüsünü yöneten, SQL gönderip sonuç alan yapılandırma nesnesidir.

Örnek tanım:

```python
from sqlalchemy import create_engine

engine = create_engine("postgresql://user:pass@localhost/dbname")
```

Engine’in sorumlulukları:

- Bağlantı havuzunu (connection pool) yönetmek,  
- Uygun dialect’i kullanarak SQL ifadelerini uygun formata çevirmek,  
- DBAPI üzerinden veri tabanına SQL göndermek ve sonuçları almak.  

Engine:

- ORM’in üzerinde çalıştığı temel katmandır.  
- Transaction’ı ORM düzeyinde yönetmez; bu sorumluluk çoğu senaryoda Session tarafından üstlenilir.  

---

### 5. Connection – Düşük Seviye Bağlantı

Connection, Engine’den elde edilen gerçek bağlantı nesnesidir ve özellikle Core seviyesinde kullanılır:

```python
with engine.connect() as conn:
    result = conn.execute(...)
```

ORM kullanılırken çoğu zaman doğrudan `Connection` nesnesi ile çalışılmaz; bunun yerine Session üzerinden daha üst seviye bir soyutlama kullanılır.  
Ancak altyapı düzeyinde tüm ORM işlemleri de eninde sonunda bir bağlantı nesnesi üzerinden veri tabanına ulaşır.

---

### 6. ORM Katmanı ve Temel Bileşenleri

ORM (Object-Relational Mapper), Python sınıfları ile veri tabanı tablolarını eşleştirir.

Temel sorumlulukları:

- Python sınıfı ↔ tablo eşlemesi (mapping),  
- Nesnelerin yaşam döngüsünü (object lifecycle) yönetmek,  
- Değişiklikleri takip etmek ve uygun SQL’i üretmek,  
- İlişkileri (`relationship`) nesne düzeyinde ifade edebilmek.  

Başlıca bileşenler:

- **Mapped Class (Model)**  
- **Mapper**  
- **Session**  
- **Identity Map**  
- **Unit of Work**  
- **Relationship** tanımları  

#### 6.1 Mapped Class (Model)

Mapped class, bir tabloyu temsil eden Python sınıfıdır:

```python
from sqlalchemy.orm import declarative_base

Base = declarative_base()

class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True)
    name = Column(String(100))
```

Bu sınıf:

- `users` tablosunu temsil eder,  
- Alanları (attributes), sütunlara (`Column`) karşılık gelir,  
- İlişkiler (`relationship`) de bu sınıf üzerinde tanımlanır.  

#### 6.2 Mapper

Mapper, bir sınıfın hangi tablo ile eşleşeceğini ve hangi attribute’un hangi sütuna karşılık geldiğini bilir.  
Mapper:

- Primary key bilgisini,  
- Sütun–özellik eşlemesini,  
- İlişki tanımlarını  

içeren meta veriyi yönetir.

---

### 7. Session – Transaction ve Durum Yönetimi

Session, ORM katmanının merkezindeki bileşendir.

Tanım:

> Session, ORM nesnelerinin durumunu (state) takip eden, değişiklikleri toplayan ve transaction sınırları içinde veri tabanına yansıtan birimdir.

Başlıca görevleri:

- Nesneleri takip etmek (eklenen, değişen, silinen kayıtlar),  
- Objelerin yaşam döngüsünü (transient, pending, persistent, detached, deleted) yönetmek,  
- Transaction yönetimini sağlamak (COMMIT/ROLLBACK),  
- Uygun zamanda SQL üretip veri tabanına göndermek (flush).  

Session, **Unit of Work** ve **Identity Map** kavramları ile birlikte çalışır.

#### 7.1 Identity Map

Identity Map, Session içindeki her bir veri tabanı satırının, tek bir Python nesnesi ile temsil edilmesini sağlar.

Örneğin:

```python
u1 = session.get(User, 1)
u2 = session.get(User, 1)
```

`u1` ve `u2` aynı session içinde aynı nesneyi işaret eder.  
Bu sayede:

- Tekrarlı nesne oluşturma engellenir,  
- Tutarlılık korunur,  
- Değişiklik takibi sadeleşir.  

#### 7.2 Unit of Work

Unit of Work, Session’ın değişiklikleri toplu hâlde işleme mantığıdır.

- Hangi nesneler eklendi?  
- Hangileri güncellendi?  
- Hangileri silindi?  

Bu bilgiler Session içinde toplanır.  
`session.commit()` çağrıldığında:

1. Değişiklikler analiz edilir.  
2. Gerekli INSERT/UPDATE/DELETE komutları üretilir.  
3. Bu komutlar uygun sırayla veri tabanına gönderilir.  

Bu yaklaşım:

- Gereksiz SQL üretimini azaltır,  
- Transaction mantığı ile uyumlu, kontrollü bir yazma süreci sağlar.  

#### 7.3 Flush ve Commit İlişkisi

Flush:

- Session’daki bekleyen değişikliklerin SQL’e dönüştürülerek veri tabanına gönderilmesidir.  
- Transaction’ı sonlandırmaz.  

Commit:

- Gerekirse otomatik olarak flush işlemini tetikler,  
- Ardından transaction’ı sonlandırır.  

Bu ayrım, gelişmiş senaryolarda (örneğin, transaction’ı açık tutarak kademeli sorgular yapmak istediğinizde) önemlidir.

---

### 8. Relationship Mimarisi ve Yükleme Stratejileri

`relationship()` tanımları:

- Tablolar arasındaki foreign key bağlantılarına dayanır,  
- Nesneler arasındaki yönlü ilişkileri ifade eder (ör. `user.orders`).  

ORM, bu ilişkileri kullanarak:

- Lazy loading (gerektiğinde veri çekme),  
- Eager loading (baştan JOIN ile veri çekme),  

gibi stratejilerle sorgu davranışını yönetir.

Örneğin:

- Varsayılan lazy yükleme, ilk erişimde ek SELECT sorgusu üretir.  
- `joinedload` veya `selectinload` gibi seçenekler ile ilişkinin baştan tek veya az sayıda sorgu ile alınması sağlanabilir.  

Bu konu, performans optimizasyonu ve N+1 problemi bağlamında, Adım 1’in ilerleyen bölümlerinde detaylandırılacaktır.

---

### 9. Core ve ORM Arasındaki Fark

Özetlersek:

- **Core**:  
  - SQL ifadelerine çok yakın bir soyutlama sunar.  
  - `Connection` ve ham ifadeler (`text()`, `select()`) üzerinden çalışır.  
  - Nesne yaşam döngüsü takibi yapmaz.  

- **ORM**:  
  - Python sınıfları ve nesneleriyle çalışır.  
  - Session üzerinden state takibi, Identity Map ve Unit of Work uygular.  
  - İlişkileri nesne düzeyinde yönetir.  

Her iki katman da aynı Engine ve Dialect altyapısını paylaşır; farklılık, soyutlama seviyesi ve sorumluluktur.

---

### 10. Genel Akış – ORM Senaryosu

Basit bir örnek üzerinden, tüm katmanların birlikte nasıl çalıştığını özetleyebiliriz:

```python
user = User(name="Ali")
session.add(user)
session.commit()
```

İçeride olanlar:

1. `User` nesnesi oluşturulur (transient state).  
2. `session.add(user)` ile Session’a eklenir (pending state).  
3. `session.commit()` çağrıldığında:  
   - Session, Unit of Work ile değişiklikleri analiz eder.  
   - Core üzerinden uygun INSERT SQL’i üretilir.  
   - Engine, bu SQL’i ilgili Dialect ve DBAPI kullanarak veri tabanına gönderir.  
   - Veri tabanı kaydı oluşturur ve gerekli yanıtı döner.  
   - Transaction commit edilir; nesne artık persistent state’e geçmiştir.  

---

### 11. Bu Klasörün Devamında Neler Var?

`Adım 1 – SQLAlchemy Temelleri` klasöründe, bu README’de özetlenen mimari bileşenler, aşağıdaki başlıklar hâlinde detaylandırılacaktır (örnek liste, gerçek dosya yapısına göre güncellenebilir):

- Engine ve Dialect kullanımı  
- Session yaşam döngüsü ve nesne durumları (transient, pending, persistent, detached, deleted)  
- Unit of Work ve Identity Map’in pratik etkileri  
- Relationship türleri ve yükleme stratejileri (lazy, joined, selectin)  
- Core vs ORM kullanım senaryoları  
- Basit bir mini proje üzerinden uçtan uca akış  

Bu README, SQLAlchemy mimarisinin “büyük resmini” ve bileşenlerin rolünü kavramsal düzeyde konumlandırmayı amaçlar.  
Ayrıntılı kullanım ve kod örnekleri, Adım 1 altındaki diğer dosyalarda adım adım ele alınacaktır.