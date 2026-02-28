# Unit of Work Pattern – SQLAlchemy ile

Bu doküman, **Unit of Work (UoW)** pattern’ını ve SQLAlchemy **Session** ile ilişkisini detaylı açıklar.

---

## 1. Tanım ve Amaç

Unit of Work, **tek bir iş biriminde (use case, request) yapılan tüm veritabanı değişikliklerini** tek bir **transaction** içinde toplar. Ya hepsi **commit** olur, ya hata durumunda hepsi **rollback** olur. Ayrıca “bir Session’ı başlat, tüm repository’lere ver, iş bitince tek commit/rollback” mantığını merkezileştirir.

**Amaçlar:**

- Tutarlılık: İş birimi atomik; kısmi yazma olmaz.  
- Session yaşam süresinin net tanımlanması: Request/use-case başına bir Session.  
- Birden fazla Repository’nin aynı transaction’da çalışması.  

---

## 2. SQLAlchemy Session = Unit of Work

SQLAlchemy’de **Session** zaten Unit of Work davranışına sahiptir:

- `session.add()`, `session.delete()`, attribute değişiklikleri **bellekte** toplanır.  
- `session.flush()` ile SQL üretilir ama transaction hâlâ açık kalır.  
- `session.commit()` ile tüm değişiklikler kalıcı olur.  
- `session.rollback()` ile hepsi iptal edilir.  

Yani “Unit of Work” deseni, bu Session’ı **kimin ne zaman açıp kapatacağını** ve **hangi nesnelere (Repository’lere) verileceğini** netleştirir.

---

## 3. Kim Session’ı Yönetir?

Genelde **Service katmanı** veya açık bir **Unit of Work** sınıfı:

- Use case başında: Session açılır (veya UoW başlatılır).  
- Aynı Session, kullanılacak tüm Repository’lere verilir.  
- Use case sonunda: `commit()` veya hata durumunda `rollback()`.  
- Her durumda: `close()`.  

Repository’ler Session’ı **dışarıdan** alır; kendileri açmaz/kapatmaz.

---

## 4. İki Yaklaşım

### 4.1 Session’ı Doğrudan Service’te Yönetmek

Service, Session factory (sessionmaker) alır. Her use case metodunda:

```text
async def create_order(...):
    async with session_factory() as session:
        user_repo = UserRepository(session)
        order_repo = OrderRepository(session)
        # ... iş mantığı, repo.add(...) vb.
        await session.commit()
```

Session context manager ile kapanır; exception’da rollback yapılır. Bu da pratikte bir “Unit of Work” kullanımıdır.

### 4.2 Açık Unit of Work Sınıfı

Bazı projelerde `UnitOfWork` adında bir sınıf olur:

- `start()` veya `__enter__`: Session açar, Repository’leri (bu Session ile) oluşturur.  
- `commit()`: Session.commit()  
- `rollback()`: Session.rollback()  
- `close()`: Session.close()  

Service, `UnitOfWork`’ü kullanır; Repository’lere UnitOfWork üzerinden erişir. Avantaj: tek noktadan Session ve Repository’lerin yaşam döngüsü kontrol edilir.

---

## 5. Repository’ler Aynı Session’ı Paylaşmalı

Önemli kural: **Aynı use case içinde kullanılan tüm Repository’ler aynı Session instance’ını almalıdır.** Aksi halde farklı Session’lar farklı transaction’larda olur; tek atomik commit elde edilemez.

- Service veya UoW: **bir** Session oluşturur.  
- Bu Session, `UserRepository(session)`, `OrderRepository(session)` şeklinde verilir.  
- Hepsi aynı transaction’da çalışır; tek `commit()` hepsini yazar.  

---

## 6. Hata Yönetimi

- Use case içinde **herhangi bir yerde** exception fırlarsa, Session **rollback** edilmeli ve ardından **close** edilmeli.  
- Context manager (`with session_factory() as session`) kullanıyorsanız, exception path’te de `finally` veya context’in çıkışında close çağrıldığından emin olun.  
- Repository içinde **asla** commit/rollback yapılmamalı; sadece Session kullanılır.  

---

## 7. Özet

Unit of Work, “tek iş birimi = tek transaction” kuralını ve Session’ın tek merkezden (Service veya UoW sınıfı) yönetilmesini ifade eder. SQLAlchemy Session bu rolü zaten sağlar; siz sadece Session’ı **nerede açıp kapatacağınızı** ve **hangi Repository’lere vereceğinizi** netleştirirsiniz. Tüm Repository’ler aynı Session’ı paylaşır; commit/rollback tek yerde yapılır.

**Ana README’ye dön:** [README.md](README.md)
