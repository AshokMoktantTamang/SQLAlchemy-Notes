# Katmanlı Mimari (Layered Architecture) – SQLAlchemy ile

Bu doküman, **katmanlı mimari**yi ve SQLAlchemy’nin bu yapıda nereye oturduğunu detaylı açıklar.

---

## 1. Tanım ve Amaç

Katmanlı mimari, uygulamayı **yatay katmanlara** böler. Üst katman sadece **hemen alt katmanla** konuşur; alt katman üst katmanı bilmez. Veri akışı genelde tek yönlüdür: istek yukarıdan aşağı iner, cevap aşağıdan yukarı çıkar.

**Amaçlar:**

- Sorumlulukların net ayrılması  
- Değişikliklerin sınırlı yerde kalması (örn. veritabanı değişince sadece veri katmanı)  
- Testte katmanların ayrı ayrı veya mock’larla test edilebilmesi  

---

## 2. Tipik Dört Katman

### 2.1 Presentation (Sunum) Katmanı

- **Sorumluluk:** HTTP istekleri, CLI komutları, form/UI. Girdiyi alır, Service’e iletir, cevabı döner.  
- **SQLAlchemy ile ilişki:** Hiçbir şekilde Session, Engine veya sorgu kullanmaz. Sadece DTO veya domain nesneleri alıp döner.  
- **Örnek:** FastAPI route, Flask blueprint, Click CLI.

### 2.2 Application / Service Katmanı

- **Sorumluluk:** İş kuralları (business rules), use case akışı, transaction sınırının belirlenmesi.  
- **SQLAlchemy ile ilişki:** Session’ı açar/kapatır veya Unit of Work kullanır; Repository/DAO’yu çağırır. Session’ı Repository’lere verir; commit/rollback bu katmanda yapılır.  
- **Örnek:** `UserService.create_user()`, `OrderService.place_order()`.

### 2.3 Domain Katmanı

- **Sorumluluk:** Entity’ler, value object’ler, domain mantığı. “Kullanıcı nedir?”, “Sipariş hangi kurallara tabidir?”  
- **SQLAlchemy ile ilişki:** ORM modelleri (User, Order) burada tanımlanabilir veya ayrı bir “persistence model” katmanda tutulup domain’de sadece saf sınıflar kullanılabilir. Tercihe göre domain entity’leri aynı zamanda SQLAlchemy modeli olur.  
- **Örnek:** `User`, `Order`, `Product` sınıfları.

### 2.4 Data Access / Infrastructure Katmanı

- **Sorumluluk:** Veritabanına erişim. Sorguların yazılması, Session/Engine yönetimi, Repository veya DAO implementasyonları.  
- **SQLAlchemy ile ilişki:** Engine, SessionFactory, Repository/DAO sınıfları burada. Tüm `select`, `insert`, `update`, `delete` ve `session.commit()` bu katmanda veya bu katmanı kullanan Repository’de.  
- **Örnek:** `database.py`, `UserRepository`, `OrderDAO`.

---

## 3. Veri Akışı Örneği (Adım Adım)

1. **İstek** → Presentation: `POST /users` body ile gelir.  
2. **Controller** → Service’i çağırır: `user_service.create_user(name, email)`.  
3. **Service** → Session açar (veya UoW başlatır), Repository’ye Session verir: `user_repo.add(user)`.  
4. **Repository** → `session.add(user)`, Service `session.commit()` çağırır.  
5. **Service** → Oluşan entity’yi (veya DTO) döner.  
6. **Controller** → HTTP 201 ve body döner.  
7. **Session** → Service veya context manager Session’ı kapatır.  

Aynı use case içinde birden fazla Repository kullanılıyorsa hepsi **aynı Session**’ı paylaşır; tek transaction olur.

---

## 4. SQLAlchemy Bileşenlerinin Yeri

| Bileşen | Katman | Açıklama |
|---------|--------|----------|
| `create_engine` | Infrastructure | Uygulama başlangıcında bir kez; genelde `database.py` veya config. |
| `sessionmaker` | Infrastructure | Session factory; Repository’lere Session bu factory’den verilir. |
| `Session` yaşam döngüsü | Service veya Presentation (DI) | Request/use-case başına açılır, sonunda kapatılır; commit/rollback Service’te. |
| ORM modelleri (Base, Entity) | Domain veya Infrastructure | Projeye göre domain’de veya persistence katmanında. |
| Sorgular (select, insert, vb.) | Sadece Repository/DAO (Infrastructure) | Service ve Presentation’da doğrudan sorgu olmamalı. |

---

## 5. Klasör Yapısı Örneği

```text
proje/
├── api/
│   └── users.py          # Presentation: route'lar, request/response
├── application/
│   └── user_service.py   # Service: create_user, get_user, transaction
├── domain/
│   └── user.py           # User entity (isterseniz ORM modeli burada)
├── infrastructure/
│   ├── database.py       # engine, session_factory
│   └── repositories/
│       └── user_repository.py  # SQLAlchemy ile get_by_id, add, list
└── main.py               # Engine/Session/Repository/Service wiring
```

---

## 6. Dikkat Edilecek Noktalar

- **Üst katman alt katmanı bilir; alt üstü bilmez.** Presentation Service’i bilir, Service Repository’yi bilir; Repository Session’ı bilir. Ters bağımlılık olmamalı.  
- **Transaction sınırı** tek yerde (genelde Service) olmalı; Repository içinde commit yapılmamalı ki aynı transaction’da birden fazla repository kullanılabilsin.  
- **Cross-layer atlama:** Presentation’dan doğrudan Repository çağrılmaz; her zaman Service üzerinden gidilir.  

---

## 7. Özet

Katmanlı mimari, SQLAlchemy’yi **Data Access / Infrastructure** katmanına yerleştirir. Service katmanı Session ve Repository kullanır; Presentation ise sadece Service ile konuşur. Bu yapı, diğer desenlerin (Repository, Unit of Work, Service layer) üzerine kurulduğu temeldir.

**Ana README’ye dön:** [README.md](README.md)
