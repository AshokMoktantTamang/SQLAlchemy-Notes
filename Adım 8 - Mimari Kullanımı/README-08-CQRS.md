# CQRS (Command Query Responsibility Segregation) – SQLAlchemy ile

Bu doküman, **CQRS** kavramını ve SQLAlchemy’nin **yazma (command)** ile **okuma (query)** tarafında nasıl kullanılabileceğini detaylı açıklar.

---

## 1. Tanım ve Amaç

CQRS, **yazma** ve **okuma** sorumluluklarını ayırır. Yazma tarafında domain modeli, aggregate’ler ve “olaylar” güncellenir; okuma tarafında raporlama, listeleme ve ekranlar için **ayrı modeller** veya **doğrudan sorgular** kullanılabilir. İki taraf farklı modellere, farklı veri şekillerine ve hatta farklı veri kaynaklarına (örn. read replica) sahip olabilir.

**Amaçlar:**

- Okuma ve yazma ihtiyaçlarının farklı optimize edilmesi  
- Yazma tarafında domain kurallarının korunması, okuma tarafında basit ve hızlı sorgular  
- Ölçeklemede read replica veya ayrı read store kullanımı  

---

## 2. Yazma Tarafı (Command)

- **Kullanılan yapı:** Domain entity’ler, Repository/Unit of Work, Session.  
- **SQLAlchemy rolü:** Session ile INSERT/UPDATE/DELETE; Repository veya adapter üzerinden.  
- **Akış:** Command gelir → Use case → Repository’ler (aynı Session) → commit.  
- **Model:** Genelde “normalize” domain/ORM modeli; iş kuralları bu tarafta.  

Bu taraf, önceki adımlarda anlattığımız Repository + Service + Unit of Work yapısıyla aynıdır. SQLAlchemy Session ve ORM tam burada kullanılır.

---

## 3. Okuma Tarafı (Query)

- **Kullanılan yapı:** Doğrudan sorgular, DTO’lar, bazen ayrı “query service” veya “read model”.  
- **SQLAlchemy rolü:** `select`, `text()`, VIEW’lar; bazen aynı Engine, bazen **read-only** veya **read replica** Engine.  
- **Model:** Sorguya özel DTO veya “read model”; JOIN’li, denormalize edilmiş tablolar veya VIEW’lar kullanılabilir.  
- **Commit:** Okuma tarafında commit yok; sadece read.  

Yazma tarafındaki ORM entity’leri kullanmak zorunda değilsiniz; rapor için ayrı bir `select(...).mappings()` veya DTO dolduran sorgu yazılabilir.

---

## 4. Hafif CQRS (Pragmatik)

Tam CQRS (ayrı event store, event sourcing) zorunlu değildir. **Hafif CQRS** yeterli olabilir:

- **Command:** Mevcut Repository + Session + commit; domain kuralları Service’te.  
- **Query:** Ayrı “query service” veya doğrudan read-only sorgular; bazen aynı SessionFactory’den farklı bir Session, bazen read replica’ya bağlı ikinci bir Engine.  
- **Veri:** Aynı veritabanı; sadece kullanım şekli (yazma vs. okuma) ve bazen farklı Engine (replica) ayrılır.  

SQLAlchemy’de: yazma için Engine + Session + Repository; okuma için aynı Engine’den `select`/`text` veya ikinci Engine (replica) ile sadece SELECT.

---

## 5. İki Engine (Read Replica)

Yüksek okuma yükünde:

- **Primary Engine:** Yazma (ve bazen okuma).  
- **Replica Engine:** Sadece okuma; connection string read replica’yı işaret eder.  
- Query service veya read use case’leri Replica Engine’den Session/connection alır; Command tarafı Primary kullanır.  
- Replication gecikmesi nedeniyle “son yazılanı hemen oku” gerekiyorsa o sorgu Primary’den yapılabilir.  

SQLAlchemy’de iki `create_engine` (ve gerekirse iki sessionmaker); DI veya config ile hangi use case’in hangi Engine’i kullanacağı belirlenir.

---

## 6. Ne Zaman CQRS?

- **Hafif CQRS:** Okuma ve yazma use case’leri zaten farklı (farklı endpoint’ler, farklı servisler); sadece “okuma tarafında ayrı sorgu/read model” kullanmak.  
- **Tam CQRS:** Ayrı read store (ör. denormalize tablolar, cache), event’lerle güncelleme; karmaşıklık artar.  
- **Gerekmedikçe** tam CQRS’e geçmeyin; önce “yazma = Repository + Session, okuma = ayrı sorgu katmanı” ile başlayın.  

---

## 7. Özet

CQRS, yazma (command) ve okuma (query) sorumluluklarını ayırır. SQLAlchemy ile **yazma** tarafında Repository + Unit of Work + Session kullanılır; **okuma** tarafında ayrı sorgular, DTO’lar ve isteğe bağlı read replica Engine kullanılabilir. Hafif CQRS çoğu projede yeterlidir; tam CQRS ve event sourcing ayrı bir mimari karardır.

**Ana README’ye dön:** [README.md](README.md)
