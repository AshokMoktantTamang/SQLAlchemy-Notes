## Adım 5 – Migration Yönetimi (Alembic ile)

Bu adım, SQLAlchemy tabanlı bir projede **veritabanı şemasını üretim ortamında güvenli ve kontrollü şekilde evrimleştirmek** için migration yönetimine odaklanır.

Amaç:

- ORM modelleri değiştiğinde, veritabanı şemasını nasıl adım adım güncelleyeceğinizi göstermek  
- Alembic’i SQLAlchemy ile nasıl entegre edeceğinizi açıklamak  
- Production için güvenli migration pratiklerini özetlemek  

---

### 1. Migration Nedir?

Migration, veritabanı şemasının **versiyon kontrollü** olarak değiştirilmesidir.

Örneğin:

- Yeni tablo ekleme  
- Kolon ekleme / silme / değiştirme  
- Index ekleme  
- Constraint değiştirme  
- İlişki yapısını güncelleme  

gibi değişiklikler, migration dosyaları üzerinden yönetilir.

Önemli ayrım:

- Geliştirme aşamasında: `Base.metadata.create_all()` hızlı başlamak için kullanılabilir.  
- Production’da: **yalnızca migration araçları** ile schema değişikliği yapılmalıdır; `create_all()` production’da tabloyu yok sayarak yeniden oluşturmaya kalkabilir.

---

### 2. SQLAlchemy + Alembic İlişkisi

SQLAlchemy:

- Runtime’da ORM modellerini ve `Base.metadata` bilgilerini yönetir.

Alembic:

- Bu metadata’yı okur (`target_metadata`),  
- Mevcut veritabanı şeması ile karşılaştırır,  
- Farkları migration dosyaları olarak üretir,  
- `upgrade` / `downgrade` fonksiyonları üzerinden schema’yı ileri/geri taşır,  
- Veritabanında `alembic_version` tablosu ile hangi versiyonun uygulandığını takip eder.

Özet:

- **ORM** = Şu anki model tanımı  
- **Alembic** = Model tanımındaki değişiklikleri şemaya taşıyan “geçmiş kaydı” ve uygulayıcı

---

### 3. Alembic Kurulum Adımları

#### 3.1 Kurulum

```bash
pip install alembic
```

#### 3.2 Projeye Alembic Başlatma

Proje kök dizininde:

```bash
alembic init alembic
```

Bu komut aşağıdaki yapıyı oluşturur:

```text
alembic/
    env.py
    script.py.mako
    versions/
alembic.ini
```

#### 3.3 `alembic.ini` Ayarları

`alembic.ini` içinde veritabanı bağlantısını belirtin:

```ini
sqlalchemy.url = sqlite:///app.db
```

Gerçek projede bu değer genellikle ortam değişkenlerinden veya ayrı bir config dosyasından okunur.

#### 3.4 `env.py` İçinde `Base.metadata` Bağlama

`env.py` dosyasında, SQLAlchemy modellerinizin `Base.metadata` bilgisini Alembic’e tanıtmanız gerekir:

```python
# env.py içinden bir kesit

from myapp.database import Base  # Projenizdeki Base tanımı

target_metadata = Base.metadata
```

Bu adım **kritiktir**; Alembic, otomatik migration (autogenerate) için tablo ve kolon bilgilerini buradan okur.

---

### 4. İlk Migration Oluşturma

Modelleriniz tanımlı ve `env.py` içinde `target_metadata` ayarlıysa, ilk migration’ı otomatik üretebilirsiniz:

```bash
alembic revision --autogenerate -m "initial schema"
```

Bu komut:

- Mevcut veritabanı şemasını (eğer varsa) ve `Base.metadata` bilgisini karşılaştırır,  
- Farklara göre `alembic/versions/` altında bir Python migration dosyası oluşturur.

Örnek bir migration dosyası (özet):

```python
from alembic import op
import sqlalchemy as sa

revision = "1234_initial_schema"
down_revision = None


def upgrade():
    op.create_table(
        "users",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("name", sa.String(length=100), nullable=False),
    )


def downgrade():
    op.drop_table("users")
```

---

### 5. Migration Uygulama (Upgrade / Downgrade)

#### 5.1 Son Versiyona Yükseltme

```bash
alembic upgrade head
```

- Tüm henüz uygulanmamış migration’lar sırayla çalıştırılır.  
- Veritabanındaki `alembic_version` tablosu güncellenir.

#### 5.2 Belirli Versiyona Geri Dönme

Migration geçmişini görmek:

```bash
alembic history
```

Çıkışta göreceğiniz bir `revision` ID’sine (ör. `1234_initial_schema`) geri dönmek için:

```bash
alembic downgrade 1234_initial_schema
```

Son versiyondan bir önceki sürüme dönmek:

```bash
alembic downgrade -1
```

---

### 6. Model Değiştiğinde Migration Üretimi

Örnek senaryo:

```python
class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)
    # Yeni eklenen kolon:
    email = Column(String(200), unique=True)
```

Model değişikliğinden sonra:

```bash
alembic revision --autogenerate -m "add email to user"
alembic upgrade head
```

Alembic:

- `User` modeline eklenen `email` kolonunu fark eder,  
- Uygun `op.add_column(...)` komutunu içeren bir migration dosyası üretir,  
- `upgrade` fonksiyonuyla kolonu ekler, `downgrade` fonksiyonuyla kolonu kaldırır (genellikle `op.drop_column(...)`).

---

### 7. Autogenerate Sınırlamaları ve Manuel Düzenleme

Autogenerate güçlüdür ama **her şeyi otomatik yapmaz**:

- Kolon ismi değişikliği (rename)  
- Bazı complex constraint ve index değişiklikleri  
- Bazı custom type veya function tanımları  

gibi durumlarda migration dosyasını manuel düzenlemeniz gerekir.

Örneğin kolon rename:

```python
def upgrade():
    op.alter_column("users", "old_name", new_column_name="new_name")
```

Autogenerate’ın ürettiği şablonu inceleyip, gerektiğinde `op.*` fonksiyonlarını kendiniz uyarlamanız beklenir.

---

### 8. Production İçin Migration Kuralları

1. **Production veritabanını asla drop etme.**  
   - `drop_all()` veya yanlış `create_all()` kullanımı ciddi veri kayıplarına yol açar.

2. **Her schema değişikliği için migration üret.**  
   - Model dosyasını değiştirdikten sonra mutlaka ilgili migration’ı oluşturun ve commit edin.

3. **Migration dosyalarını versiyon kontrolüne dahil et.**  
   - `alembic/versions/*.py` dosyaları repo’da tutulmalıdır.

4. **`downgrade()` fonksiyonlarını boş bırakma.**  
   - En azından kritik migration’lar için geri dönüş senaryosu tanımlamaya çalışın.

5. **Manual SQL gerekiyorsa açıkça yaz.**  
   - Örneğin büyük tabloya index eklerken özel SQL kullanmak istiyorsanız, migration dosyasına yorum ve açıklama ekleyin.

---

### 9. Zero-Downtime Migration Stratejileri (Özet)

Büyük sistemlerde, şema değişikliklerinin uygulama çalışırken kesinti yaratmaması isteriz.

Örnek problem:

- NOT NULL ve default değeri olmayan bir kolon eklemek,  
- Çok büyük bir tabloya index eklemek.

Önerilen yaklaşım:

1. **Nullable kolon ekle:**

   ```python
   op.add_column("users", sa.Column("new_col", sa.String(), nullable=True))
   ```

2. **Backfill (data migration):**  
   - Uygulama çalışırken, arka planda batch olarak `new_col` için uygun değerleri doldur.

3. **Constraint ekle:**  

   ```python
   op.alter_column("users", "new_col", nullable=False)
   ```

Index için:

- Mümkünse **concurrently** veya veritabanının sunduğu çevrim içi index oluşturma seçeneklerini kullan.  
- Çok büyük tablolarda index işlemlerini yoğun olmayan zaman dilimlerinde planla.

Bu seviyedeki detaylar, genellikle DBA ve backend mimarı işbirliği ile ele alınır.

---

### 10. Branching Migration ve Merge

Ekip çalışmasında, iki farklı geliştirici farklı branch’lerde migration üretebilir. Sonuç:

- İki farklı “head” oluşur.  

Bu durumda Alembic, merge migration’ı gerektirir:

```bash
alembic merge -m "merge heads" <revision_id_1> <revision_id_2>
```

Merge migration:

- Yalnızca migration grafını birleştirir (çoğu zaman schema değişikliği içermez).  
- Sonrasında tüm migration zinciri tek bir head altında devam eder.

---

### 11. Migration Durumunu İzleme

Şu an veritabanı hangi versiyonda?

```bash
alembic current
```

Migration geçmişini listelemek:

```bash
alembic history
```

Belirli bir migration dosyasına gitmek için:

```bash
alembic upgrade <revision_id>
alembic downgrade <revision_id>
```

Bu komutlar, deployment süreçlerine (CI/CD pipeline) entegre edilerek otomatik migration uygulaması yapılabilir.

---

### 12. Özet – ORM + Migration Birlikte Nasıl Düşünülmeli?

- ORM modelleri (`Base` ve `mapped class`’lar), **uygulamanın ideal veri modelini** tanımlar.  
- Migration aracı (Alembic), bu modellerdeki değişikliklerin **zaman içindeki evrimini** veritabanına uygular.  
- Geliştirme aşamasında:
  - Hızlı prototip için `create_all()` kabul edilebilir.  
- Production aşamasında:
  - `create_all()` yalnızca ilk setup’ta (boş veritabanında) ve kontrollü olarak kullanılmalı.  
  - Sonraki tüm değişiklikler **migration** üzerinden yönetilmelidir.

Migration ustalığı ölçütü:

- `env.py` ve `alembic.ini` yapılarını anlayıp gerektiğinde özelleştirebilmek.  
- Autogenerate’i nasıl ve ne zaman kullanacağını bilmek.  
- `op.*` API’si ile manuel migration yazabilmek.  
- Branch çatışmalarında merge migration üretebilmek.  
- Zero-downtime gerektiren değişiklikler için kademeli migration stratejileri tasarlayabilmek.

Bu adımın sonunda, SQLAlchemy ile çalışan bir uygulamada schema değişikliklerini rastgele değil, **tasarlanmış, izlenebilir ve geri alınabilir** migration’lar üzerinden yönetmeye hazır olmalısınız.

