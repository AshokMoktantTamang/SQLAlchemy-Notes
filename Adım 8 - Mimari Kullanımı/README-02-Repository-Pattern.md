# Repository Pattern – SQLAlchemy ile

Bu doküman, **Repository pattern**’ı ve SQLAlchemy ile nasıl uygulandığını detaylı açıklar.

---

## 1. Tanım ve Amaç

Repository, **veri kaynağını (veritabanı, API, dosya) domain ve uygulama katmanından gizleyen** bir soyutlamadır. Uygulama, veriyi “koleksiyon” gibi kullanır: “şu id’li kullanıcıyı getir”, “bu kullanıcıyı ekle”, “şu koşula uyanları listele”. Veritabanı, SQL veya ORM detayı **Repository’nin arkasında** kalır.

**Amaçlar:**

- Domain ve Service katmanının Session, `select`, `flush` bilmemesi  
- Veri kaynağı değiştiğinde (farklı DB, farklı ORM) sadece Repository implementasyonunun değişmesi  
- Testte gerçek DB yerine **in-memory** veya **mock** Repository kullanılabilmesi  

---

## 2. Arayüz (Soyutlama)

Repository, bir **arayüz (interface)** veya **soyut sınıf** ile tanımlanır. Metotlar domain dilinde yazılır; parametre ve dönüş tipleri entity veya value object’tir.

**Örnek – UserRepository arayüzü:**

```text
UserRepository (soyut)
├── get_by_id(id: int) -> User | None
├── get_by_email(email: str) -> User | None
├── add(user: User) -> None
├── list(limit: int, offset: int) -> List[User]
├── remove(user: User) -> None
└── (opsiyonel) update(user: User) -> None
```

Service sadece bu arayüze bağımlıdır; “SQLAlchemy”, “Session” bilmez.

---

## 3. SQLAlchemy ile Implementasyon

### 3.1 Session’ı Kim Verir?

Repository **commit/rollback yapmaz**. Session’ı **dışarıdan** (constructor veya her metot çağrısında) alır. Böylece aynı Session ile birden fazla Repository kullanılabilir ve transaction **Service** veya **Unit of Work** tarafından yönetilir.

### 3.2 Tipik Metot Eşlemesi

| Repository metodu | SQLAlchemy karşılığı (kısa) |
|-------------------|-----------------------------|
| `get_by_id(id)` | `session.get(User, id)` veya `session.execute(select(User).where(User.id == id)).scalar_one_or_none()` |
| `add(user)` | `session.add(user)` |
| `list(limit, offset)` | `session.execute(select(User).limit(limit).offset(offset)).scalars().all()` |
| `remove(user)` | `session.delete(user)` |
| `update(user)` | Nesne zaten Session’da ise attribute atanır, sonra `session.flush()`; ayrı bir `update()` metodu da yazılabilir. |

### 3.3 Örnek Somut Sınıf (Pseudocode)

```text
SqlAlchemyUserRepository(UserRepository arayüzünü implement eder)
  - _session: Session  (constructor’da alınır)

  get_by_id(id):
    return self._session.get(User, id)

  add(user):
    self._session.add(user)

  list(limit, offset):
    result = self._session.execute(select(User).limit(limit).offset(offset))
    return result.scalars().all()

  remove(user):
    self._session.delete(user)
```

Commit/rollback bu sınıfta **yok**; Service veya UoW çağırır.

---

## 4. Generic Repository (Opsiyonel)

Çok sayıda entity için CRUD benzeriyse, **generic** bir Repository yazılabilir:

```text
GenericRepository[T] (TypeVar T)
  get_by_id(id) -> T | None
  add(entity: T) -> None
  list(...) -> List[T]
  remove(entity: T) -> None
```

Somut sınıf: `SqlAlchemyUserRepository(GenericRepository[User])` gibi. Özel sorgular (örn. `get_by_email`) alt sınıfta ek metot olarak eklenir.

---

## 5. Ne Zaman Repository Kullanılır?

- **Kullanın:** Orta/büyük proje, test öncelikli, domain’i altyapıdan ayırmak istiyorsanız.  
- **Hafif kullanın:** Küçük projede tek bir “repository benzeri” modül bile yeterli olabilir.  
- **Alternatif:** DAO aynı fikri farklı isimle uygular; ekip “DAO” diyorsa onu kullanabilirsiniz.  

---

## 6. Sık Yapılan Hatalar

- **Repository içinde commit:** Transaction sınırı Service’te olmalı; Repository sadece Session kullanır.  
- **Service’te Session/query:** Service Repository arayüzünü çağırır; Session’ı sadece “açıp Repository’lere vermek” için kullanır.  
- **Arayüzü atlayıp doğrudan somut Repository kullanmak:** Testte mock takamazsınız; mümkünse arayüz + somut implementasyon.  
- **Çok fazla özel metot:** Her sorgu için metot açmak yerine, `list(filters)` veya specification pattern gibi genel bir arayüz düşünülebilir.  

---

## 7. Unit of Work ile Birlikte Kullanım

Repository tek başına kullanılabilir; ancak **aynı use case’te birden fazla entity** güncelleniyorsa, tüm Repository’ler **aynı Session**’ı almalıdır. Bu Session’ı sağlayan ve commit/rollback’i yapan yapı **Unit of Work** (veya basitçe Service’in Session yönetimi) olur. Detay için [README-03-Unit-of-Work.md](README-03-Unit-of-Work.md) dosyasına bakın.

---

## 8. Özet

Repository, veri erişimini **arayüz arkasına** alır; SQLAlchemy Session ve sorgular sadece **somut Repository sınıfında** bulunur. Service ve domain katmanı sadece arayüzü bilir; testte mock/fake repository verilebilir. Commit/rollback Repository dışında (Service veya UoW) yapılır.

**Ana README’ye dön:** [README.md](README.md)
