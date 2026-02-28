# Clean Architecture / Hexagonal (Ports & Adapters) – SQLAlchemy ile

Bu doküman, **Clean Architecture** ve **Hexagonal (Ports & Adapters)** mimaride SQLAlchemy’nin **adapter** olarak nasıl konumlandırıldığını detaylı açıklar.

---

## 1. Tanım ve Amaç

- **Clean Architecture:** Domain ve uygulama mantığı **merkezde**; dış dünya (veritabanı, API, UI) **dış halkalarda**. İç halkalar dış halkalara bağımlı olmaz; bağımlılık **içe doğru** akar.  
- **Hexagonal (Ports & Adapters):** Uygulama “hexagon” gibi düşünülür; dışarıyla iletişim **port** (arayüz) üzerinden yapılır. Her port’a bağlanan **adapter** (veritabanı adapter’ı, HTTP adapter’ı) altyapı detayını uygular.  

**Ortak amaç:** Domain ve use case’lerin veritabanı, framework veya UI’dan **bağımsız** olması. Değişen sadece adapter’lar olur.

---

## 2. Port (Arayüz)

**Port**, uygulamanın dış dünyayla konuşmak için koyduğu **soyut arayüz**dür. Veri tarafında örnek: “Kullanıcı deposu” port’u.

- **İsim:** Örn. `UserRepositoryPort` veya `IUserRepository`.  
- **Metotlar:** `get_by_id`, `save`, `list`, `remove` gibi domain/uygulama dilinde.  
- **Önemli:** Port’ta SQLAlchemy, Session, `select`, `insert` **hiç geçmez**. Sadece domain tipleri (User, List[User]) ve basit tipler (id, limit, offset) vardır.  
- **Yeri:** Domain veya application katmanı (iç hexagon).  

Use case (application) sadece bu port’a bağımlıdır; “UserRepositoryPort’u kullanırım” der, kimin implement ettiğini bilmez.

---

## 3. Adapter (SQLAlchemy ile Implementasyon)

**Adapter**, port’u **somut** olarak gerçekleştirir. Veritabanı adapter’ı:

- Port arayüzünü implement eder (örn. `SqlAlchemyUserRepository(UserRepositoryPort)`).  
- **Session** veya Session factory alır (constructor’da).  
- `get_by_id` → `session.get(User, id)` veya `session.execute(select(User)...)`.  
- `save` → `session.add(user)` ve gerekirse `flush`.  
- Commit/rollback **adapter’da değil**; use case veya application service’te.  
- **Yeri:** Infrastructure (dış katman).  

Böylece “veritabanı erişimi” tamamen adapter’da; domain ve use case SQLAlchemy’yi hiç görmez.

---

## 4. Bağımlılık Yönü

- **Domain / Use case** → Port’a (arayüz) bağımlı.  
- **Adapter** → Port’u implement eder; aynı zamanda SQLAlchemy’ye (ve Engine/Session’a) bağımlı.  
- **Composition root** (main, startup): Port’a **hangi adapter’ın** bağlanacağını seçer; use case’e concrete adapter verilir (dependency injection).  

Testte: Port’a **mock** veya **in-memory** adapter bağlanır; gerçek SQLAlchemy kullanılmaz.

---

## 5. Klasör Yapısı Örneği

```text
proje/
├── domain/
│   ├── entities/
│   │   └── user.py
│   └── ports/
│       └── user_repository_port.py   # Arayüz; SQLAlchemy yok
├── application/
│   └── use_cases/
│       └── create_user.py             # Port'u kullanır; adapter bilmez
├── infrastructure/
│   └── adapters/
│       └── persistence/
│           └── sqlalchemy_user_repository.py  # Port'u implement eder, Session kullanır
├── database.py                         # Engine, SessionFactory (infrastructure)
└── main.py                             # Port → Adapter bağlantısı (DI)
```

---

## 6. SQLAlchemy Modelleri Nerede?

İki yaygın tercih:

- **Infrastructure’da:** ORM modelleri (SQLAlchemy `Base`, kolonlar) sadece adapter/infrastructure’da tanımlanır. Domain’de “saf” `User` sınıfı (ORM’siz) olur; adapter domain User’ı ORM entity’ye veya tersine map’ler.  
- **Domain’de tek model:** Domain entity aynı zamanda ORM modeli (SQLAlchemy sütunları domain sınıfında). Bu durumda domain, SQLAlchemy’ye “hafif” bağımlı olur; birçok projede pratik nedenlerle kabul edilir.  

Tam bağımsızlık istiyorsanız domain’de sadece saf sınıflar, adapter’da ORM modelleri ve mapping yapılır.

---

## 7. Özet

Clean/Hexagonal mimaride **port** = veri erişimi arayüzü (domain/application tarafında); **adapter** = SQLAlchemy ile bu arayüzün implementasyonu (infrastructure’da). Use case sadece port’u bilir; Session ve sorgular adapter’da kalır. Dependency injection ile runtime’da port’a gerçek veya test adapter’ı bağlanır.

**Ana README’ye dön:** [README.md](README.md)
