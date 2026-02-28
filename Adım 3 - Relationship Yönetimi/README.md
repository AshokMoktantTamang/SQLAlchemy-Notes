## Adım 3 – Relationship Yönetimi

Bu adımda SQLAlchemy’nin en kritik ve en sık yanlış kullanılan alanı olan **relationship yönetimini** mimari seviyede ele alıyoruz.

İçerik, aşağıdaki sorulara kapsamlı yanıt verecek şekilde yapılandırılmıştır:

- `relationship()` gerçekte ne yapar?  
- `ForeignKey` ile `relationship` arasındaki fark nedir?  
- One-to-Many ve Many-to-Many ilişkiler doğru nasıl kurulur?  
- `cascade` seçenekleri ne işe yarar, ne zaman kullanılır?  
- Lazy loading türleri (select, joined, selectin, raise) ve etkileri nelerdir?  
- N+1 problemi nedir, nasıl tespit edilir ve çözülür?  
- `back_populates` ve `backref` arasındaki fark nedir?  
- Association table vs association object pattern ne zaman tercih edilmelidir?  
- Production ortamında relationship yönetimi için en iyi pratikler nelerdir?  

---

### 1. `ForeignKey` ve `relationship()` Arasındaki Fark

İki temel katmanı ayırmak önemlidir:

- **`ForeignKey` (veritabanı seviyesi)**  
  - Tablo sütunları arasında ilişki kuran DDL (şema) öğesidir.  
  - Görevi: Veri bütünlüğünü sağlamak; örneğin `orders.user_id` sadece mevcut bir `users.id` değerine işaret edebilir.

- **`relationship()` (ORM seviyesi)**  
  - Python sınıfları (model nesneleri) arasındaki ilişkiyi ifade eder.  
  - Görevi: Navigasyon ve yükleme davranışı; örneğin `user.orders` veya `order.user` gibi erişimler sağlar.

Örnek:

```python
user_id = Column(ForeignKey("users.id"))
```

Bu tanım, veritabanı tarafında foreign key bağlantısını kurar.  
Ancak aşağıdaki tanım olmadan ORM tarafında `user.orders` gibi bir özellik oluşmaz:

```python
orders = relationship("Order")
```

Özet:

- `ForeignKey` → Veritabanı bağlantısını ve bütünlüğünü ifade eder.  
- `relationship` → ORM tarafında bu bağlantıyı nesneler üzerinden dolaşılabilir hale getirir.  
  - Yeni sütun oluşturmaz, veritabanı kuralı üretmez; var olan `ForeignKey` tanımlarına dayanır.

---

### 2. One-to-Many İlişki – Doğru Kurulum

En yaygın ilişki türü One-to-Many’dir. Örnek olarak, bir kullanıcının birden fazla siparişi olduğunu düşünelim.

```python
class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True)
    name = Column(String)

    orders = relationship(
        "Order",
        back_populates="user",
        cascade="all, delete-orphan",
    )


class Order(Base):
    __tablename__ = "orders"

    id = Column(Integer, primary_key=True)
    amount = Column(Integer)

    user_id = Column(Integer, ForeignKey("users.id"))

    user = relationship("User", back_populates="orders")
```

Burada:

- `user_id` sütunu, veritabanı seviyesinde `orders` → `users` bağlantısını sağlar (`ForeignKey`).  
- `User.orders` ve `Order.user` alanları, ORM seviyesinde iki yönlü ilişki sağlar (`relationship`).  
- `back_populates`, bu iki alanın aynı ilişkiye ait olduğunu ve birbirini güncellediğini belirtir.  
- `cascade="all, delete-orphan"`, bir `User` silindiğinde ona bağlı `Order` nesnelerinin ne olacağını belirler (aşağıda detaylandırılır).

---

### 3. `back_populates` vs `backref`

#### `back_populates`

Açık, iki taraflı tanım gerektirir:

```python
orders = relationship("Order", back_populates="user")
user = relationship("User", back_populates="orders")
```

- Avantajları:
  - Büyük projelerde ilişki yönlerini ve isimlerini açıkça görmek daha kolaydır.  
  - İlişkilerin bakımı ve yeniden düzenlenmesi daha kontrollüdür.

#### `backref`

Kısa yol tanımıdır:

```python
orders = relationship("Order", backref="user")
```

- Bu tek satır, hem `User.orders` hem de `Order.user` için descriptor oluşturur.  
- Küçük projelerde kullanışlı olabilir, fakat büyük projelerde ilişkiyi takip etmek zorlaşabilir.

Genel tavsiye:

- Öğretici / küçük örnekler için `backref` kabul edilebilir.  
- Production kodda, özellikle birçok model ve ilişki olduğunda, **`back_populates` tercih edilmesi** tavsiye edilir.

---

### 4. `cascade` Seçenekleri

`cascade` parametresi, parent–child ilişkisi içinde ORM’in **hangi işlemleri child nesnelere de uygulayacağını** belirler.

Örnek:

```python
orders = relationship(
    "Order",
    back_populates="user",
    cascade="all, delete-orphan",
)
```

Bu ifade, aşağıdakileri içerir:

- `save-update`  
- `merge`  
- `delete`  
- `delete-orphan`  

#### `delete-orphan` Nedir?

`delete-orphan` sayesinde:

- Parent (ör. `User`) silindiğinde, ona bağlı child (`Order`) nesneleri de silinir.  
- Veya child, parent’in koleksiyonundan çıkarıldığında (`user.orders.remove(order)`), ilgili child kaydı da veritabanından silinir.

Bu davranış:

- “Parent yoksa ona ait child kayıt da olmamalı” kuralının ORM seviyesindeki karşılığıdır.  
- Kullanılmadığında, parent silinince child kayıtlar “orphan” (sahipsiz) olarak kalabilir; bu da veri tutarlılığı açısından sorun yaratabilir.

`cascade` ayarları, her ilişki için ayrı ayrı, iş kuralına göre değerlendirilmelidir; tek bir “her zaman doğru” varsayılan yoktur.

---

### 5. Lazy Loading Türleri

`relationship` için `lazy` parametresi, ilişkili nesnelerin **ne zaman ve nasıl yükleneceğini** belirler.

Başlıca türler:

#### `lazy="select"` (varsayılan)

- İlişkiye ilk erişildiğinde ayrı bir SELECT sorgusu çalıştırılır.

```python
user = session.get(User, 1)
orders = user.orders  # Bu satırda ek bir SELECT tetiklenir.
```

#### `lazy="joined"`

- Parent nesne sorgulanırken, JOIN ile birlikte child kayıtlar da çekilir.

```python
orders = relationship("Order", lazy="joined")
```

- Avantaj: Tek sorgu ile hem parent hem child kayıtlar gelir.  
- Dezavantaj: Gereksiz JOIN’ler, büyük veri setlerinde maliyetli olabilir.

#### `lazy="selectin"` (modern ve genellikle önerilen)

- İki aşamalı yükleme yapar:
  1. İlk sorguda parent nesneleri çeker.  
  2. İkinci sorguda, `IN (...)` filtrelemesi ile tüm ilgili child kayıtları tek seferde çeker.  

Bu sayede:

- N+1 problemi önlenir,  
- Büyük JOIN’lerden kaçınılır,  
- Genellikle dengeli bir performans profili sağlar.

```python
orders = relationship("Order", lazy="selectin")
```

#### `lazy="raise"`

- Lazy load’a izin vermez; ilişkiye erişildiğinde henüz yüklenmemişse istisna atar.  
- Özellikle istenmeyen lazy davranışlarını yakalamak ve zorunlu eager loading sağlamak için kullanılır.

---

### 6. N+1 Problemi

Senaryo:

```python
users = session.query(User).all()

for u in users:
    print(u.orders)
```

- İlk satır: Tüm kullanıcılar için 1 adet sorgu.  
- Döngü içinde: Her kullanıcı için ilişkili siparişleri almak adına 1 sorgu (lazy select).  
- Toplam: **1 (users) + N (orders)** sorgu → N+1 problemi.

#### Çözüm: Eager Loading (ör. `selectinload`)

```python
from sqlalchemy.orm import selectinload

users = (
    session.query(User)
    .options(selectinload(User.orders))
    .all()
)
```

- Bu yaklaşımda:
  - 1 sorgu → kullanıcılar,  
  - 1 sorgu → `WHERE user_id IN (...)` ile tüm ilgili `orders`.  
- Toplam 2 sorgu ile N+1 problemi ortadan kalkar.

Benzer şekilde, `joinedload` da bazı durumlarda tercih edilebilir; hangisinin uygun olduğu veri hacmi ve erişim desenine göre değerlendirilmelidir.

---

### 7. Many-to-Many İlişkiler

Many-to-Many ilişkiler için iki temel yaklaşım vardır:

#### 7.1 Basit Association Table

Ek alan gerekmiyorsa (sadece ilişki bilgisi yeterliyse) kullanılabilir.

```python
association_table = Table(
    "enrollments",
    Base.metadata,
    Column("student_id", ForeignKey("students.id")),
    Column("course_id", ForeignKey("courses.id")),
)


class Student(Base):
    __tablename__ = "students"

    id = Column(Integer, primary_key=True)
    name = Column(String)

    courses = relationship(
        "Course",
        secondary=association_table,
        back_populates="students",
    )


class Course(Base):
    __tablename__ = "courses"

    id = Column(Integer, primary_key=True)
    name = Column(String)

    students = relationship(
        "Student",
        secondary=association_table,
        back_populates="courses",
    )
```

Bu yaklaşımda:

- Ara tablo bağımsız bir model sınıfına sahip değildir.  
- Ek sütun (ör. not, tarih, durum) ihtiyacı yoksa yeterlidir.

#### 7.2 Association Object Pattern (Tavsiye Edilen Esnek Yaklaşım)

Ek alanlar gerektiğinde, ara tablo için ayrı bir model sınıfı tanımlanır:

```python
class Enrollment(Base):
    __tablename__ = "enrollments"

    id = Column(Integer, primary_key=True)
    student_id = Column(ForeignKey("students.id"))
    course_id = Column(ForeignKey("courses.id"))
    grade = Column(Integer)  # Ek alan
```

Avantajları:

- Ek alanlar (not, tarih, durum vb.) rahatça eklenebilir.  
- İlişkiyi temsil eden kavram (örn. Enrollment) nesne olarak yönetilebilir.  

Bu desen, production ortamında Many-to-Many ilişkiler için genellikle daha sürdürülebilir bir yaklaşımdır.

---

### 8. Relationship İç Mekanizması – Yüksek Seviye Bakış

`relationship()` çağrıldığında SQLAlchemy:

- Model sınıfı üzerine bir descriptor ekler.  
- Attribute erişimini (ör. `user.orders`) override eder.  
- Lazy/eager loading stratejisine göre uygun loader fonksiyonunu bağlar.  
- Mapper metadata’sına JOIN koşulları ve ilişki bilgilerini ekler.

Sonuç olarak:

- `user.orders` basit bir liste alanı değildir;  
- İhtiyaç halinde SQL tetikleyebilen, cache’lenmiş sonuçlar döndürebilen bir proxy/görünüm işlevi görür.

---

### 9. Identity Map ve Relationship Etkileşimi

Session, Identity Map sayesinde:

- Aynı satıra karşılık gelen nesnenin Session içinde yalnızca bir kez oluşturulmasını garanti eder.

Örneğin:

```python
u1 = session.get(User, 1)
u2 = session.get(User, 1)
```

- `u1` ve `u2` aynı nesnedir.  

Relationship’ler de bu mekanizma ile entegredir:

- `user.orders` içinde yer alan nesneler, Session içindeki aynı `Order` nesneleridir.  
- Bu sayede:
  - Tutarlılık korunur,  
  - Gereksiz nesne üretimi engellenir,  
  - Değişiklik takibi daha sağlıklı yapılır.

---

### 10. Production İçin Relationship Yönetimi Checklist’i

Her ilişki için şu soruları sormak faydalıdır:

- Foreign key doğru tabloda mı tanımlı?  
- `back_populates` veya `backref` doğru ve tutarlı mı kullanılmış?  
- `cascade` ayarları iş kurallarına uygun mu?  
- Lazy/eager loading stratejisi bilinçli mi seçilmiş?  
- N+1 riski var mı, testlerde izleniyor mu?  
- İlişkide kullanılan foreign key alanları üzerinde uygun index’ler var mı?  

Genel tavsiyeler:

- Varsayılan `lazy="select"` davranışını bilin, fakat büyük listelerde eagerly load seçeneklerini (özellikle `selectinload`) değerlendirin.  
- Global, uzun ömürlü Session kullanmayın; request/iş birimi başına Session yaklaşımını sürdürün.  
- Relationship sayısını ve karmaşıklığını, gerçek ihtiyaçlarla orantılı olacak şekilde tutun; gereksiz çok yönlü ilişkiler yerine net sorumluluk alan modeller tasarlayın.

Bu adımı sindirdikten sonra, bir sonraki pratik adım, ilişki yoğun bir mini projede (örneğin akademi sistemi) bilinçli olarak N+1 problemi üretmek, sorgu sayısını ölçmek ve `selectinload` / `joinedload` gibi stratejilerle bu problemi çözmektir.

