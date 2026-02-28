# DAO (Data Access Object) – SQLAlchemy ile

Bu doküman, **DAO** pattern’ını, **Repository** ile farkını ve SQLAlchemy ile nasıl kullanıldığını detaylı açıklar.

---

## 1. Tanım ve Amaç

DAO (Data Access Object), veritabanı erişimini **kaynak/tablo bazlı** soyutlayan bir katmandır. “User tablosu için erişim”, “Order tablosu için erişim” gibi düşünülür. Metotlar genelde CRUD ve “find_by_…” tarzı sorgulardır.

**Amaçlar:**

- Veri erişim kodunun tek yerde toplanması  
- Üst katmanın (Service) SQL ve veritabanı detayından habersiz olması  
- Tablo/veri modeli değişince sadece ilgili DAO’nun güncellenmesi  

---

## 2. Repository ile Fark (Pratikte)

| Açıdan | Repository | DAO |
|--------|------------|-----|
| **Odak** | Domain “koleksiyonu”; aggregate/entity merkezli | Veri kaynağı/tablo merkezli |
| **Dil** | “Kullanıcıyı getir”, “Siparişi ekle” (domain dili) | “User kaydı getir”, “Order ekle” (veri dili) |
| **Kullanım** | DDD (Domain-Driven Design) ortamlarında yaygın | Geleneksel Java/enterprise projelerinde yaygın |
| **Pratik** | Çoğu projede ikisi de aynı şeyi yapar: veri erişimini soyutlamak. İsimlendirme ve ekip alışkanlığına göre seçilir. |

Bazı ekipler “Repository” der, bazıları “DAO”; SQLAlchemy tarafında ikisi de Session alır, sorgu yazar, commit yapmaz.

---

## 3. Tipik DAO Arayüzü

```text
UserDAO
├── get(id) -> User | None
├── find_by_email(email) -> User | None
├── insert(user) -> None
├── update(user) -> None
├── delete(user) -> None
└── find_all(limit, offset) -> List[User]
```

“insert/update/delete” isimleri veritabanı ağırlıklı; Repository’de genelde “add”, “remove” tercih edilir. DAO’da tablo/kolon düşüncesi daha belirgin olabilir.

---

## 4. SQLAlchemy ile Implementasyon

- DAO, **Session**’ı constructor’da veya metot parametresi olarak alır.  
- `get(id)` → `session.get(User, id)`.  
- `insert(user)` → `session.add(user)`.  
- `update(user)` → Entity zaten Session’da ise attribute ataması yeterli; ayrı bir “detach/attach” senaryosu varsa `session.merge(user)` veya benzeri kullanılabilir.  
- `delete(user)` → `session.delete(user)`.  
- `find_all`, `find_by_...` → `session.execute(select(User)...).scalars().all()` veya `scalar_one_or_none()`.  
- **Commit/rollback** DAO’da yapılmaz; Service veya Unit of Work yapar.  

---

## 5. Ne Zaman DAO Tercih Edilir?

- Ekip “DAO” terimine alışıksa ve dokümantasyonda/mevcut koddaki isimlendirme DAO ise.  
- Proje daha “veri merkezli” (reporting, CRUD ağırlıklı) ve domain modeli hafifse.  
- Java/Spring geçmişinden gelen ekiplerde DAO sık görülür; Python’da da aynı mantık uygulanabilir.  

Repository ile aynı mimari faydayı sağlar; fark büyük oranda semantik ve isimlendirmedir.

---

## 6. Generic DAO (Opsiyonel)

Tüm entity’ler için ortak CRUD varsa:

```text
GenericDAO[T]
  get(id) -> T | None
  insert(entity: T) -> None
  update(entity: T) -> None
  delete(entity: T) -> None
  find_all(limit, offset) -> List[T]
```

Somut: `UserDAO(GenericDAO[User])`, özel sorgular (`find_by_email`) alt sınıfta eklenir.

---

## 7. DAO ve Repository Birlikte Kullanılır mı?

Genelde **ya** Repository **ya** DAO kullanılır; ikisi aynı amaca hizmet eder. Nadiren “DAO = veri erişimi, Repository = domain koleksiyonu” diye iki katman tanımlanır; bu durumda Repository, DAO’yu kullanabilir. Çoğu projede tek soyutlama (Repository veya DAO) yeterlidir.

---

## 8. Özet

DAO, veri erişimini tablo/kaynak bazlı soyutlar; Session’ı dışarıdan alır, commit/rollback yapmaz. SQLAlchemy ile implementasyon, Repository ile büyük ölçüde aynıdır; fark isimlendirme ve odak (veri vs. domain) ile ilgilidir. Ekip “DAO” diyorsa bu pattern’ı kullanın; mimari fayda Repository ile aynıdır.

**Ana README’ye dön:** [README.md](README.md)
