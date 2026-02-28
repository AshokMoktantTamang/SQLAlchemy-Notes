## Adım 1 – Session ve Engine Pooling

Bu doküman, SQLAlchemy’de sık sorulan aşağıdaki sorulara odaklanır:

- Session nedir, neyi yönetir?  
- Engine ve connection pool nedir, nasıl çalışır?  
- Hangi parametreler performansı etkiler?  
- Ne zaman birden fazla engine’e ihtiyaç duyulur?  

Amaç, özellikle üretim ortamına hazırlık yaparken Session ve Engine ayarlarını bilinçli şekilde yapabilmenizi sağlamaktır.

---

### 1. Session Nedir?

Session, ORM katmanının merkezindeki bileşendir.

Özet tanım:

> Session, ORM nesnelerinin durumunu takip eden, değişiklikleri toplayan ve transaction sınırları içinde veri tabanına yansıtan birimdir.

Başlıca sorumlulukları:

- ORM nesnelerinin yaşam döngüsünü yönetmek (transient, pending, persistent, detached, deleted).  
- Eklenen, güncellenen ve silinen nesneleri takip etmek (Unit of Work).  
- Transaction yönetimi yapmak (BEGIN/COMMIT/ROLLBACK).  
- Gerekli noktalarda SQL üreterek Engine üzerinden veri tabanına göndermek (flush).  

Pratikte:

- Web uygulamalarında genellikle **istek başına (request-scoped)** bir Session kullanılır.  
- Uzun süre açık kalan, global Session’lar veri tutarlılığı ve bellek kullanımı açısından risklidir.  

---

### 2. Engine ve Connection Pool Nedir?

Engine:

> Veri tabanı ile konuşmak için kullanılan, bağlantı havuzunu ve Dialect’i yöneten merkezi bileşendir.

Örnek:

```python
from sqlalchemy import create_engine

engine = create_engine(
    "postgresql+psycopg2://user:pass@localhost:5432/dbname",
    echo=False,
    future=True,
)
```

Engine’in sorumlulukları:

- DBAPI sürücüsü üzerinden gerçek bağlantıları yönetmek.  
- Bağlantı havuzu (connection pool) oluşturmak ve kullanmak.  
- Core/ORM tarafından üretilen SQL ifadelerini veri tabanına iletmek.  

Connection pool:

> Engine tarafından yönetilen, yeniden kullanılabilir veritabanı bağlantıları kümesidir.

Bağlantı havuzu sayesinde:

- Her sorgu için sıfırdan bağlantı aç/kapat yapılmaz.  
- Mevcut bağlantılar havuzdan alınarak performans artırılır.  

---

### 3. Engine / Pooling Parametreleri ve Performans

`create_engine` fonksiyonu, bağlantı havuzunu ve davranışlarını kontrol etmek için çeşitli parametreler alır.

Önemli parametreler:

#### 3.1 pool_size

```python
engine = create_engine(..., pool_size=5)
```

- Aynı anda açık tutulacak bağlantı sayısının temel sınırıdır.  
- Varsayılan değer veri tabanı türüne göre değişebilir.  
- Çok düşük tutulursa, yoğun trafikte beklemeler (queueing) artabilir.  
- Gereğinden yüksek tutulursa, veri tabanı sunucusunda gereksiz bağlantı yükü oluşabilir.

#### 3.2 max_overflow

```python
engine = create_engine(..., pool_size=5, max_overflow=10)
```

- pool_size sınırına ulaşıldığında, ek olarak açılabilecek “geçici” bağlantı sayısını belirler.  
- Toplam bağlantı üst sınırı kabaca `pool_size + max_overflow` olarak düşünülebilir.  

#### 3.3 pool_timeout

```python
engine = create_engine(..., pool_timeout=30)
```

- Havuzdan uygun bir bağlantı alınamazsa, ne kadar süre bekleneceğini saniye cinsinden belirler.  
- Bu süre dolduğunda hata fırlatılır.  

#### 3.4 pool_recycle

```python
engine = create_engine(..., pool_recycle=1800)
```

- Belirli bir saniye süresinden daha eski olan bağlantıların yeniden kullanılmadan önce kapatılıp tekrar açılmasını sağlar.  
- “Idle timeout” ile bağlantı kopmaları yaşanan ortamlarda (özellikle bazı bulut/veri tabanı yapılandırmalarında) yararlıdır.  

#### 3.5 pool_pre_ping

```python
engine = create_engine(..., pool_pre_ping=True)
```

- Havuzdan alınan bağlantının hâlâ geçerli olup olmadığını hafif bir “ping” ile test eder.  
- Uzun süre kullanılmayan bağlantıların sunucu tarafından düşürüldüğü ortamlarda, “stale connection” hatalarını azaltır.  

---

### 4. Session ve Engine Ayarlarının Etkileşimi

Session:

- Engine’e bağlı olarak çalışır (`sessionmaker(bind=engine, ...)`).  
- Her Session, gerektiğinde Engine’den bir veya daha fazla bağlantı alır.  

Performans açısından:

- **Engine / pooling ayarları** bağlantı seviyesindeki davranışı (kaç bağlantı, ne kadar süre açık, yeniden kullanım vb.) etkiler.  
- **Session ayarları** (autoflush, autocommit, expire_on_commit vb.) SQL üretimi ve transaction davranışını etkiler.  

Örnek:

- Çok kısa süren, sık istek alan bir API için:
  - `pool_size` ve `max_overflow` değerleri beklenen eşzamanlı istek sayısına göre ayarlanmalıdır.  
  - Session’lar kısa ömürlü, istek bazlı olmalı; her istekte açılıp iş bitince kapatılmalıdır.  

---

### 5. Ne Zaman Birden Fazla Engine Gerekir?

Çoğu uygulama için **tek bir Engine** yeterlidir. Ancak bazı durumlarda birden fazla Engine kullanılabilir:

1. **Birden fazla veri tabanı** kullanılıyorsa  
   - Örneğin: Operasyonel veriler PostgreSQL’de, raporlama verileri başka bir veri tabanında tutuluyorsa.  
   - Her veri tabanı için ayrı `engine_X`, `SessionLocal_X` tanımlanabilir.  

2. **Farklı yetkilerle bağlantı açılması gerekiyorsa**  
   - Örneğin: Sadece okuma yapan bir kullanıcı ile yalnızca raporlama sorguları çalıştırmak için.  
   - Yazma/okuma ayrımı yapmak isteyen gelişmiş mimarilerde (read replica kullanımı vb.).  

3. **Çok farklı bağlantı ayarlarına ihtiyaç duyan modüller**  
   - Nadir bir durumdur; genellikle iyi bir pooling ayarı ile tek Engine yeterlidir.  

Genel tavsiye:

- Tek uygulama – tek operasyonel veri tabanı senaryosunda **tek Engine** kullanmak çoğu zaman doğrudur.  
- Birden fazla Engine, çoğunlukla birden fazla veri tabanı veya çok özel erişim politikaları olduğunda anlamlıdır.

---

### 6. Session Kullanımında Dikkat Edilmesi Gerekenler

1. **Session’ı kısa ömürlü tutun**  
   - Özellikle web uygulamalarında, her istek için ayrı bir Session açıp iş bittikten sonra kapatmak en sağlıklı yaklaşımdır.  

2. **Global, paylaşılmış Session kullanmayın**  
   - Tek bir Session’ı tüm uygulama genelinde paylaşmak, bellek ve tutarlılık problemlerine yol açar.  
   - Session thread-safe değildir; her thread/process kendi Session’ını kullanmalıdır.  

3. **Autocommit ve autoflush ayarlarını bilin**  
   - `autocommit=False` (önerilen): Değişikliklerin net şekilde commit ile yönetilmesini sağlar.  
   - `autoflush=False` (öğrenme aşamasında tercih edilebilir): Flush davranışını daha kontrollü yönetmenize izin verir; ancak bazı sorgularda otomatik flush’ın beklendiğini unutmayın.  

4. **Transaction sınırlarını net belirleyin**  
   - Bir iş birimi (örneğin tek HTTP isteği) genellikle tek transaction olarak ele alınmalıdır.  
   - Bu, hem ACID prensipleri hem de hata yönetimi açısından pratiktir.  

---

### 7. Performans Üzerindeki Etkiyi Özetlemek

**Engine / Pooling ayarları**:

- Çok küçük pool:
  - Bağlantı kuyruğu ve timeout hataları görülebilir.  
- Çok büyük pool:
  - Veri tabanı sunucusunda gereksiz bağlantı yükü oluşabilir.  
- Uygun `pool_recycle` ve `pool_pre_ping`:
  - Uzun ömürlü bağlantı sorunlarını (bağlantı düşmesi, idle timeout) azaltır.  

**Session kullanım şekli**:

- Uzun süre açık kalan Session:
  - Bellekte gereksiz nesne birikimi.  
  - Veri tabanı ile senkronizasyon sorunları.  
- Kısa ömürlü, iş birimi bazlı Session:
  - Daha öngörülebilir transaction yönetimi.  
  - Daha temiz bellek kullanımı.  

Doğru yapılandırma:

- Trafik düzeyi, veri tabanı kapasitesi ve uygulama mimarisi birlikte değerlendirilerek yapılmalıdır.  
Bu dokümanın amacı, hangi parametrenin neyi etkilediğini kavramanızı sağlamaktır; somut değerler, her proje için ayrı ayrı belirlenmelidir.