# SQLAlchemy Notları

Bu depo, **SQLAlchemy** ile Python’da veritabanı uygulamaları geliştirmek isteyenler için adım adım hazırlanmış notlar ve örnek kodları içerir. Temel ORM kavramlarından production mimarisine kadar tüm konular tek bir yapı altında toplanmıştır.

---

## Bu Dosyanın Amacı

- **Projenin ne olduğunu** kısaca tanıtmak  
- **İçindekiler listesi** ile tüm adımlara tek yerden erişim sağlamak  
- Hangi adımda ne anlatıldığını özetleyerek **okuma sırası** ve **yol haritası** sunmak  

Her adımın kendi klasöründe ayrı bir **README** ve gerektiğinde **çalışan demo scriptleri** bulunur. Bu ana README, tüm adımların listesi ve kısa açıklamalarını içerir.

---

## İçindekiler

| # | Adım | Klasör | İçerik özeti |
|---|------|--------|----------------|
| **0** | Ön Gereksinimler | [Adım 0 - Ön Gereksinimler](Adım%200%20-%20Ön%20Gereksinimler/) | Veritabanı ve SQL temelleri, CRUD, JOIN, ilişki türleri; SQLAlchemy öncesi zihinsel altyapı. |
| **1** | SQLAlchemy Temelleri | [Adım 1 - SQLAlchemy Temelleri](Adım%201%20-%20SQLAlchemy%20Temelleri/) | Engine, Session, Base; katmanlı mimari (DBAPI, Core, ORM); temel CRUD ve `create_all`. |
| **2** | ORM | [Adım 2 - ORM](Adım%202%20-%20ORM/) | Model tanımı, ilişkiler (ForeignKey, relationship); Student–Course–Enrollment örneği; CLI menü uygulaması. |
| **3** | Relationship Yönetimi | [Adım 3 - Relationship Yönetimi](Adım%203%20-%20Relationship%20Yönetimi/) | One-to-Many, Many-to-Many; association table ve association object; lazy loading, N+1, selectinload. |
| **4** | İleri Seviye ORM | [Adım 4 - İleri Seviye ORM](Adım%204%20-%20İleri%20Seviye%20ORM/) | joinedload, selectinload, contains_eager; hybrid property; polymorphic mapping; event’ler; soft delete ve multi-tenant. |
| **5** | Migration Yönetimi | [Adım 5 - Migration Yönetimi](Adım%205%20-%20Migration%20Yönetimi/) | Alembic kurulumu, ilk migration, upgrade/downgrade; production için migration kuralları; demo_app örneği. |
| **6** | Performance & Production | [Adım 6 - Performance&Production](Adım%206%20-%20Performance%26Production/) | Connection pool, bulk insert, Session yaşam döngüsü; health check; production kontrol listesi. |
| **7** | Async SQLAlchemy | [Adım 7 - Async SQLAlchemy](Adım%207%20-%20Async%20SQLAlchemy/) | create_async_engine, AsyncSession; aiosqlite/asyncpg; lazy loading kısıtı; FastAPI ile kullanım. |
| **8** | Mimari Kullanımı | [Adım 8 - Mimari Kullanımı](Adım%208%20-%20Mimari%20Kullanımı/) | Katmanlı mimari, Repository, Unit of Work, Service layer, DAO, DI, Clean/Hexagonal, CQRS; her desen için ayrı README. |

---

## Önerilen Okuma Sırası

1. **Adım 0** – Veritabanı ve SQL bilginiz zayıfsa önce buradan başlayın.  
2. **Adım 1** – SQLAlchemy’ye giriş; Engine, Session ve Base.  
3. **Adım 2** – ORM modelleri ve basit ilişkiler; menülü örnek uygulama.  
4. **Adım 3** – İlişki türleri ve loading stratejileri (N+1 çözümü).  
5. **Adım 4** – İleri sorgular, hybrid, polymorphic, event’ler.  
6. **Adım 5** – Şema değişikliklerini migration ile yönetme.  
7. **Adım 6** – Production’a hazırlık ve performans.  
8. **Adım 7** – Async (FastAPI vb.) ile SQLAlchemy.  
9. **Adım 8** – Mimari desenler (Repository, Service, DI vb.).  

İhtiyacınıza göre belirli bir adıma doğrudan da gidebilirsiniz; her klasördeki README o adımın içeriğini açıklar.

---

## Demo ve Çalıştırma

Çoğu adımda `main.py` veya `demo_*.py` dosyaları vardır. Çalıştırmak için ilgili klasöre girip Python ile script’i çalıştırmanız yeterlidir. Gereksinimler:

- Python 3.x  
- `sqlalchemy`  
- Adım 5 için `alembic`  
- Adım 6 için ek bağımlılık yok (SQLite)  
- Adım 7 için `aiosqlite` ve `greenlet`  

Tüm çalıştırılabilir dosyaların test edilmiş özeti için proje kökündeki [CALISTIRMA_RAPORU.md](CALISTIRMA_RAPORU.md) dosyasına bakabilirsiniz.

---

## Kısa Özet

Bu depo, SQLAlchemy’yi **sıfırdan production mimarisine** kadar adım adım işler. Her adım kendi README’si ve gerektiğinde örnek kodlarıyla bağımsız okunabilir; ana README ise tüm yapıyı ve içindekileri tek sayfada sunar.
