## Adım 2 – SQLAlchemy ORM Rehberi

Bu klasör, SQLAlchemy’yi sadece kullanmak değil, **mimari ve davranışsal olarak anlamak** isteyenler için hazırlanmıştır.  
Adım 0 (ön gereksinimler) ve Adım 1 (mimari ve temel kullanım) sonrasında, burada odak **ORM zihniyeti ve doğru kullanım pratikleri** olacaktır.

Aşağıdaki sorulara sistematik yanıt verir:

- ORM gerçekte nedir, neyi çözer, neyi çözmez?  
- Doğru model tasarımı nasıl yapılır?  
- Relationship’ler nasıl kurgulanmalı ve yönetilmelidir?  
- Sorgu yazarken nasıl düşünülmeli (select, query, loading stratejileri)?  
- Production ortamında Session, ORM ve performans nasıl yönetilmelidir?  
- En sık yapılan hatalar nelerdir ve nasıl kaçınılır?  

---

### 1. ORM Nedir? (Gerçek Tanım)

ORM (Object Relational Mapper), basitçe:

> Python nesne dünyası ile ilişkisel tablo dünyası arasında **iki yönlü çeviri** yapan bir sistemdir.

Bu çeviri şu eşleştirmelere dayanır:

| Python kavramı | Veritabanı kavramı |
| -------------- | ------------------ |
| Class          | Table              |
| Object         | Row                |
| Attribute      | Column             |
| Relationship   | Foreign key        |
| Session        | Transaction bağlamı |

Önemli nokta:

- ORM, SQL’i “yok etmez”; SQL’i **soyutlar**.  
- Gerektiğinde SQL’e dönüp ne üretildiğini ve neden üretildiğini anlayabilmek hâlen kritiktir.

---

### 2. ORM ile Düşünme Biçimi

SQL odaklı düşünme:

```sql
SELECT * FROM users WHERE id = 1;
```

ORM odaklı düşünme:

```python
user = session.get(User, 1)
```

ORM kullanırken:

- Tablo yerine model sınıfını (`User`),  
- Satır yerine nesneyi (`user`),  
- Foreign key yerine relationship’i (`user.orders`)  

düşünürsünüz.  
Ancak bu soyutlama, hangi sorguların üretildiğini takip etmeyi ve gerektiğinde optimize etmeyi gereksiz kılmaz.

---

### 3. Doğru Model Tasarımı İçin Prensipler

ORM kullanımında en kritik adım, **model tasarımıdır**. Yanlış tasarlanmış modeller, hem SQL tarafında hem de kod tarafında karmaşıklık ve performans sorunlarına yol açar.

#### 3.1 Her model tek bir varlığı temsil etmeli

- Bir model sınıfı, tek bir iş kavramını (entity) temsil etmelidir.  
- Örneğin, `User`, `Order`, `Profile` ayrı modeller olmalıdır; hepsini bir arada toplayan “her şeyi yapan” bir sınıf tasarım hatasıdır.

#### 3.2 Foreign key her zaman “çok” tarafında olmalı

One-to-Many ilişkilerde:

- “Bir” taraf → tipik olarak parent tablo (ör. `User`)  
- “Çok” taraf → child tablo (ör. `Order`)  

Foreign key, child tabloda yer alır:

```python
user_id = Column(ForeignKey("users.id"))
```

#### 3.3 Benzersiz alanları (unique) net tanımlayın

- E-posta, kullanıcı adı gibi alanlar çoğu sistemde benzersizdir.  
- Hem veri tabanı hem ORM tarafında açıkça belirtilmelidir:

```python
email = Column(String, unique=True, index=True)
```

#### 3.4 Zaman damgaları (created_at vb.) ekleyin

Production sistemlerde oluşturulma tarihi genellikle gereklidir:

```python
from datetime import datetime
from sqlalchemy import DateTime

created_at = Column(DateTime, default=datetime.utcnow)
```

#### 3.5 Nullable kurallarını bilinçli yönetin

- Varsayılan `nullable=True`’dir; bu, alanın boş geçilebileceği anlamına gelir.  
- İş kurallarınızda zorunlu olan alanlar için `nullable=False` kullanın.  
- “Boş değer” ile “bilinmeyen (NULL)” arasındaki farkı tasarımda netleştirin.

---

### 4. Relationship Tasarımı (ORM Seviyesi)

İlişkiler iki katmanda ifade edilir:

1. Veri tabanı düzeyi: `ForeignKey`  
2. ORM düzeyi: `relationship()`  

Her ikisi de doğru tanımlanmalıdır.

#### 4.1 One-to-Many için temel örnek

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

- `user_id` → veri tabanı düzeyinde bağlantıyı sağlayan foreign key’dir.  
- `orders` ve `user` alanları → ORM düzeyinde, ilişkiyi nesne üzerinden kullanmayı sağlar.  
- `cascade="all, delete-orphan"` → parent silindiğinde child kayıtların nasıl davranacağını belirler.

#### 4.2 Cascade’in Önemi

Örneğin bir `User` silindiğinde:

- İlgili `Order` kayıtlarının durumu ne olacak?  
- Silinecek mi, referans mı kalacak, yoksa işlem engellenecek mi?  

Bu davranışın **önceden ve açıkça** tanımlanması gerekir.  
`cascade="all, delete-orphan"` ifadesi, çoğu One-to-Many senaryosunda tercih edilen bir davranıştır; ancak her durum için uygun olmayabilir, tasarım kararıdır.

---

### 5. ORM Kullanımında Sık Yapılan Hatalar

#### 5.1 Global (paylaşılan) Session kullanmak

Yanlış:

```python
session = Session()
# Tüm uygulama boyunca aynı nesneyi kullanmak
```

Sonuç:

- Concurrency problemleri,  
- Bellekte biriken nesneler,  
- Öngörülemez transaction sınırları.  

Doğru yaklaşım:

- Her iş birimi / istek için ayrı Session üretmek ve iş bitince kapatmak.

#### 5.2 Lazy loading’i kontrolsüz kullanmak (N+1 problemi)

Varsayılan lazy yükleme ile:

- Bir liste sorgusu sonrası, her ilişki erişiminde ek sorgular üretilebilir.  
- Bu durum, sıkça **N+1** problemi olarak karşımıza çıkar.  

Önlem:

- Uygun durumlarda `joinedload`, `selectinload` gibi eager loading stratejilerini kullanmak.  

#### 5.3 Büyük veri setlerinde `.all()` kullanmak

```python
users = session.query(User).all()
```

- Tabloda milyonlarca kayıt varsa, bu çağrı hem bellek hem performans açısından sorun yaratır.  

Çözüm:

- Sayfalama (pagination) kullanmak (`limit`, `offset`, ya da `yield_per` gibi çözümler).  

#### 5.4 Gereğinden sık commit yapmak

- Her küçük işlemde commit çağrısı, transaction yönetimi ve performans açısından verimsizdir.  
- Mantıklı iş birimleri oluşturup, bunları tek transaction içinde ele almak daha sağlıklıdır.

#### 5.5 Detached object durumunu yanlış yönetmek

- Session kapandıktan sonra ilişki alanlarına (lazy load edilecek property’lere) erişmeye çalışmak, hata üretir.  
- Nesnelerin hangi Session’a bağlı olduğunu, ne zaman ayrıldığını (detached) bilmek önemlidir.

---

### 6. Sorgu Yazma Mantığı (Modern SQLAlchemy)

Modern (2.x) SQLAlchemy stilinde, sorgular genellikle `select()` üzerinden yazılır:

```python
from sqlalchemy import select

stmt = select(User).where(User.name == "Ali")
result = session.execute(stmt)
users = result.scalars().all()
```

Bu yaklaşım:

- SQL mantığını daha açık gösterir,  
- Core ve ORM arasında tutarlı bir stil sağlar.  

Eski stil `session.query(User)` hâlen kullanılabilir, ancak yeni projelerde `select()` tabanlı stil önerilir.

---

### 7. ORM Performansına Dair Düşünme Rehberi

Performans sorunlarını analiz ederken şu sorulara odaklanmak faydalıdır:

1. Kaç farklı SQL sorgusu üretiliyor?  
2. Gereksiz tekrarlanan sorgular var mı (N+1)?  
3. İlişkiler için lazy yerine uygun eager loading stratejisi kullanılabilir mi?  
4. İlgili alanlarda index tanımlı mı?  
5. Büyük veri setlerinde uygun sayfalama veya filtreleme var mı?  

Bu sorular, hem kod hem şema tarafında iyileştirme alanlarını tespit etmeye yardımcı olur.

---

### 8. Production İçin ORM Kontrol Listesi

Bir model/şema production için değerlendiriliyorsa aşağıdaki noktalar gözden geçirilmelidir:

- [ ] Uygun bir primary key tanımlı mı?  
- [ ] Foreign key’ler doğru tabloları işaret ediyor mu?  
- [ ] Gerekli alanlarda index var mı?  
- [ ] Unique olması gereken alanlar (ör. e-posta) unique olarak tanımlandı mı?  
- [ ] Zaman damgaları (ör. `created_at`) ihtiyaçlara uygun mu?  
- [ ] Cascade kuralları tasarım kararı olarak düşünülüp netleştirildi mi?  
- [ ] Nullable ayarları iş kurallarına uygun mu?  

---

### 9. ORM’i “Gerçekten Anladığınızı” Gösteren Göstergeler

Kendinize şu soruları sorabilirsiniz:

- Üretilen sorgu sayısını ve türünü takip edip, gerektiğinde optimize edebiliyor musunuz?  
- İlişki yükleme stratejilerini (lazy, joined, selectin) bilinçli şekilde seçebiliyor musunuz?  
- Session yaşam döngüsünü (oluşum, kullanım, commit/rollback, kapanış) rahatlıkla açıklayabiliyor musunuz?  

Bu sorulara cevaplarınız netleştiğinde, artık sadece ORM “kullanmıyor”, ORM “tasarlıyor” durumda olursunuz.

---

### 10. İleri Adımlar İçin Önerilen Çalışmalar

ORM pratiğini derinleştirmek için şu tür çalışmalar yapılabilir:

1. Basit bir “akademi sistemi” (öğrenci–ders–eğitmen) mini projesi kurmak.  
2. Bilinçli olarak N+1 problemi üreten bir senaryo yazıp, sonra `selectinload`/`joinedload` ile çözmek.  
3. Toplu ekleme (bulk insert) ve performans karşılaştırmaları yapmak.  
4. Transaction hatalarını simüle edip, rollback davranışını gözlemlemek.  
5. Async SQLAlchemy (async engine + async session) ile benzer mimariyi tekrar etmek.  

Bu klasördeki sonraki dosyalar, yukarıdaki başlıkları örnekler ve küçük senaryolar üzerinden adım adım detaylandırmak üzere yapılandırılabilir.

