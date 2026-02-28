# Service Layer (Application Layer) – SQLAlchemy ile

Bu doküman, **Service katmanı**nın (Application layer) rolünü ve SQLAlchemy Session/Repository ile nasıl çalıştığını detaylı açıklar.

---

## 1. Tanım ve Amaç

Service katmanı, **iş kurallarını (business rules)** ve **use case’leri** uygular. Sunum katmanı (API, CLI) “ne yapılacağını” söyler; Service “nasıl yapılacağını” (kurallar, adımlar, transaction) belirler. Veritabanına **nasıl** yazıldığını bilmez; sadece Repository veya DAO arayüzüne “bunu getir”, “bunu kaydet” der.

**Amaçlar:**

- İş mantığının tek yerde toplanması (controller’da dağılmaması)  
- Transaction sınırının net tanımlanması  
- Farklı sunum katmanlarından (REST, CLI, job) aynı use case’in kullanılabilmesi  

---

## 2. Sorumluluklar

| Sorumluluk | Açıklama |
|------------|----------|
| **Transaction sınırı** | Session’ı açar/kapatır; use case sonunda commit veya rollback. |
| **İş kuralları** | Örn. “Stok yeterse sipariş oluştur”, “E-posta benzersiz olmalı”. |
| **Use case orkestrasyonu** | Hangi Repository’nin hangi sırayla çağrılacağı. |
| **Domain event’ler** | (Opsiyonel) İşlem sonrası event’leri tetiklemek. |

Service **veritabanı detayı** (SQL, Session internals, connection) bilmez; sadece Repository/DAO arayüzünü kullanır.

---

## 3. SQLAlchemy ile İlişki

- **Session’ı kim açar?** Service (veya Service’in kullandığı Unit of Work). Session factory constructor’da veya DI ile verilir.  
- **Repository’lere Session:** Service, Session’ı oluşturur ve Repository’lere verir; Repository’ler commit/rollback yapmaz.  
- **Commit/rollback:** Use case başarılıysa Service `session.commit()` çağırır; exception’da `session.rollback()` ve ardından Session kapatılır.  
- **Session kapatma:** Context manager veya try/finally ile her durumda `close()`.  

Service içinde **doğrudan** `session.execute(select(...))` veya `session.add()` olmamalı; tüm veri erişimi Repository/DAO üzerinden olmalı.

---

## 4. Tipik Akış (Adım Adım)

1. Controller/CLI, Service metodunu çağırır: `user_service.create_user(name, email)`.  
2. Service, Session açar (veya UoW başlatır).  
3. Service, Repository’leri bu Session ile oluşturur: `user_repo = UserRepository(session)`.  
4. İş kuralı: Örn. “Bu e-posta zaten var mı?” → `user_repo.get_by_email(email)`; varsa exception veya hata dönüşü.  
5. Domain nesnesi oluşturulur: `user = User(name=name, email=email)`.  
6. Repository’ye eklenir: `user_repo.add(user)`.  
7. Service `session.commit()` çağırır.  
8. Session kapatılır (context manager çıkışında).  
9. Service, sonucu (entity veya DTO) döner.  

Hata olursa 7. adımda commit yerine rollback, sonra close.

---

## 5. Bir Use Case’te Birden Fazla Repository

Örnek: “Sipariş oluştur” use case’i hem Order hem Product (stok güncelleme) ile çalışır. Service:

- Aynı Session’ı `OrderRepository` ve `ProductRepository`’ye verir.  
- Önce stok kontrolü, sonra sipariş ekleme, stok düşme; hepsi aynı Session’da.  
- Tek `commit()` ile hepsi kalıcı olur.  

Bu sayede Unit of Work davranışı korunur; Service orkestrasyonu ve transaction sınırını yönetir.

---

## 6. Service’te Olmaması Gerekenler

- **SQL veya ORM sorguları:** Sorgular Repository/DAO’da.  
- **Session detayı:** Service sadece “Session aç/kapat/commit/rollback” bilir; `session.execute`, `session.get` gibi kullanım Service’te değil Repository’de.  
- **HTTP/request detayı:** Mümkünse Service’e sadece domain parametreleri (id, name, vb.) geçilir; request/response nesnesi Service’e verilmez.  
- **Commit’i Repository’de yapmak:** Commit/rollback her zaman Service (veya UoW) tarafında.  

---

## 7. İnce veya Kalın Service

- **İnce Service:** Sadece Repository çağrıları ve transaction; iş kuralı az.  
- **Kalın Service:** Çok sayıda kural, validasyon, hesaplama Service’te. Domain logic’i domain sınıflarına taşındıkça Service incelir.  

Her iki durumda da “veri erişimi” Repository’de kalır; Service sadece ne zaman hangi repository’nin çağrılacağını ve commit/rollback’i yönetir.

---

## 8. Özet

Service katmanı, use case’leri ve iş kurallarını uygular; Session’ı açar/kapatır ve commit/rollback yapar. Veri erişimini Repository/DAO’ya bırakır; SQLAlchemy Session’ı Repository’lere verir ama kendisi sorgu yazmaz. Bu sayede iş mantığı tek yerde toplanır ve testte Repository mock’lanabilir.

**Ana README’ye dön:** [README.md](README.md)
