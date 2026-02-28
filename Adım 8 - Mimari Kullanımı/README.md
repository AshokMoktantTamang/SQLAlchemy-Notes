## Adım 8 – Mimari Kullanımı

Bu adım, SQLAlchemy’yi **sektörde yaygın kullanılan mimari yapılar** içinde nasıl konumlandıracağınızı anlatır. Her desen için **ayrı detaylı README** dosyası bulunur; bu dosya genel harita ve karar rehberi niteliğindedir.

---

### İçindekiler (Detaylı README’ler)

| # | Desen | Dosya | Özet |
|---|--------|--------|------|
| 1 | Katmanlı mimari | [README-01-Katmanli-Mimari.md](README-01-Katmanli-Mimari.md) | Presentation → Service → Data Access katmanları, SQLAlchemy’nin yeri |
| 2 | Repository pattern | [README-02-Repository-Pattern.md](README-02-Repository-Pattern.md) | Veri kaynağını gizleme, arayüz, SQLAlchemy implementasyonu |
| 3 | Unit of Work | [README-03-Unit-of-Work.md](README-03-Unit-of-Work.md) | Tek transaction’da çoklu değişiklik, Session yaşam döngüsü |
| 4 | Service layer | [README-04-Service-Layer.md](README-04-Service-Layer.md) | İş kuralları, use case, transaction sınırı |
| 5 | DAO | [README-05-DAO.md](README-05-DAO.md) | Data Access Object, Repository ile farkı, ne zaman kullanılır |
| 6 | Dependency Injection | [README-06-Dependency-Injection.md](README-06-Dependency-Injection.md) | Session ve Repository’nin DI ile verilmesi, test |
| 7 | Clean / Hexagonal | [README-07-Clean-Hexagonal.md](README-07-Clean-Hexagonal.md) | Ports & Adapters, SQLAlchemy adapter olarak |
| 8 | CQRS | [README-08-CQRS.md](README-08-CQRS.md) | Command / Query ayrımı, read/write ve SQLAlchemy |

---

### Neden Mimari?

- **Test edilebilirlik:** Veritabanı soyutlanınca unit testlerde mock/fake kullanılır; gerçek DB’ye ihtiyaç azalır.  
- **Değişime dayanıklılık:** ORM veya veritabanı değişse bile üst katmanlar (service, API) mümkün olduğunca az etkilenir.  
- **Sorumluluk ayrımı:** Her katman tek işe odaklanır (sunum, iş mantığı, veri erişimi); kod bulması ve değiştirmesi kolaylaşır.  
- **Takım çalışması:** Farklı ekipler farklı katmanlarda (API, domain, DB) paralel çalışabilir.  
- **Yeniden kullanım:** Service ve domain, farklı sunum katmanlarından (REST, CLI, job) aynı şekilde kullanılabilir.  

SQLAlchemy tek başına bir mimari dayatmaz; aşağıdaki desenlerle **birlikte** kullanılır.

---

### Hangi Deseni Ne Zaman Kullanmalı?

| Durum | Öneri |
|-------|--------|
| Küçük proje, hızlı prototip | Katmanlı mimari + doğrudan Session/Repository benzeri basit yapı yeterli. |
| Orta/büyük proje, test önemli | Repository + Service layer + Dependency Injection. |
| Aynı use case’te birden fazla entity güncelleniyor | Unit of Work (veya tek Session) ile tek transaction. |
| Domain’i altyapıdan tam ayırmak istiyorsunuz | Clean/Hexagonal: Port (arayüz) + SQLAlchemy adapter. |
| Ekip DAO terimine alışık | DAO pattern; Repository ile aynı fikri farklı isimle uygulayabilirsiniz. |
| Okuma ve yazma modelleri farklı (raporlama vs. işlem) | CQRS hafif uygulama: yazma Repository/UoW, okuma ayrı query/read model. |

---

### Desenler Arası İlişki (Özet)

- **Katmanlı mimari** çerçevedir; Repository, Service, DAO bu çerçeve içinde katmanlara yerleşir.  
- **Repository** veya **DAO** veri erişimini soyutlar; **Unit of Work** (veya tek Session) aynı transaction’da birden fazla repository/DAO kullanır.  
- **Service layer** iş kurallarını ve transaction sınırını yönetir; Repository/DAO’yu çağırır.  
- **Dependency Injection** Session ve Repository/DAO’yu dışarıdan verir; test ve esneklik sağlar.  
- **Clean/Hexagonal** domain’i dış dünyadan ayırır; Repository “port”, SQLAlchemy implementasyonu “adapter” olur.  
- **CQRS** okuma ve yazmayı ayırır; yazma tarafında yine Repository + Session kullanılabilir.  

---

### Önerilen Klasör Yapısı (Referans)

```text
proje/
├── api/                    # Presentation (FastAPI/Flask route'ları)
├── application/            # Service layer (use case'ler)
│   └── services/
├── domain/                 # Entity'ler, value object'ler, port arayüzleri
│   └── entities/
├── infrastructure/         # SQLAlchemy, Repository/DAO implementasyonları
│   ├── database.py        # Engine, Session factory
│   └── repositories/
└── main.py                 # Composition root, DI kurulumu
```

Detaylar ilgili pattern README’lerinde anlatılır.

---

### Kaçınılması Gerekenler (Anti-pattern)

- **Controller’da doğrudan Session/query:** Veri erişimi Service ve Repository/DAO’da olmalı.  
- **Global tek Session:** Request/use-case bazlı Session; thread-safe ve bellek açısından doğru kullanım için.  
- **Repository içinde commit:** Transaction sınırı Service veya UoW’de olmalı; aynı transaction’da birden fazla repository kullanılabilmeli.  
- **Service’te SQL veya ORM detayı:** Service sadece Repository/port arayüzünü bilmeli.  
- **Domain entity’lerinde Session/Engine referansı:** Domain altyapıdan bağımsız kalmalı.  

---

### Mimari Kontrol Listesi

- [ ] Katmanlar net mi? (Presentation → Service → Repository/DAO → Session/DB)  
- [ ] Veri erişimi Repository veya DAO ile soyutlandı mı?  
- [ ] Session/transaction sınırı nerede? (Service veya Unit of Work)  
- [ ] Repository/DAO Session’ı dışarıdan mı alıyor?  
- [ ] Service sadece Repository/port’a mı bağımlı? (SQLAlchemy’ye doğrudan değil)  
- [ ] Testte mock/fake repository kullanılabiliyor mu?  
- [ ] Dependency injection ile bağımlılıklar veriliyor mu?  

---

### Sonraki Adım

Her desenin detayı için yukarıdaki tablodaki ilgili **README-0X-…** dosyasını okuyun. Proje büyüklüğüne ve ekibin tercihine göre bir veya birkaç deseni birlikte uygulayabilirsiniz.
