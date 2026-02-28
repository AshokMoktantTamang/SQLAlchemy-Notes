# Dependency Injection ve SQLAlchemy

Bu doküman, **Dependency Injection (DI)** kullanarak SQLAlchemy **Session** ve **Repository/DAO** bağımlılıklarının nasıl yönetileceğini detaylı açıklar.

---

## 1. Tanım ve Amaç

Dependency Injection, bir sınıfın veya fonksiyonun ihtiyaç duyduğu **bağımlılıkları** (Session, Repository, config) **dışarıdan alması**dır. Kendisi “new” veya “get_instance” ile oluşturmaz. Böylece testte farklı (mock, fake) implementasyonlar verilebilir ve bağımlılıklar merkezi bir yerden (composition root) yönetilir.

**Amaçlar:**

- **Test:** Service testinde gerçek DB yerine mock Repository veya in-memory Session.  
- **Esneklik:** Session factory veya Repository implementasyonu değişince sadece “nerede oluşturulduğu” değişir; Service kodu aynı kalır.  
- **Açık bağımlılıklar:** Constructor’da görünen bağımlılıklar, sınıfın neye ihtiyaç duyduğunu net gösterir.  

---

## 2. Constructor Injection (Önerilen)

Service ve Repository bağımlılıklarını **constructor** ile alır.

**Örnek:**

- `UserService(user_repository: UserRepository)`  
- `SqlAlchemyUserRepository(session: Session)`  

Ana uygulama (main, composition root):

- Session factory oluşturur.  
- Her request’te Session açar, Repository’leri bu Session ile oluşturur, Service’e Repository’leri verir (veya Service’e Session factory verilip Service Session açar ve Repository’leri kendisi oluşturur).  
- Testte: Mock `UserRepository` veya in-memory implementasyon Service’e verilir.  

Repository’nin Session’ı dışarıdan alması da bir tür DI’dır; Session “inject” edilir.

---

## 3. Request-Scoped Session (Web)

Web uygulamasında **her HTTP isteği** için tek bir Session kullanılır. Bu Session’ın oluşturulması ve kapatılması **framework** tarafından (middleware, dependency) yapılır.

**Akış:**

1. İstek gelir → Middleware veya dependency Session açar.  
2. Session, Repository factory’e veya doğrudan Repository’lere verilir.  
3. Controller/Service bu Repository’leri kullanır (kendisi Session oluşturmaz).  
4. İstek biter → Session commit/rollback ve close edilir.  

**FastAPI örneği (kavramsal):**

- `get_db()` dependency: `async with session_factory() as session: yield session`.  
- Route: `def create_user(db: Session = Depends(get_db))`.  
- Service’e `db` (Session) veya bu Session ile oluşturulmuş Repository’ler verilir.  

Böylece Session yaşam döngüsü tek yerde (dependency) yönetilir; Controller/Service sadece “bana Session/Repository ver” der.

---

## 4. Composition Root

**Composition root**, tüm bağımlılıkların **bir araya getirildiği** yerdir. Uygulama giriş noktasına yakın (main.py, app startup).

- Engine ve SessionFactory burada oluşturulur.  
- Repository sınıfları (Session’a ihtiyaç duyarlar) request başına Session ile burada veya dependency içinde oluşturulur.  
- Service sınıfları Repository’leri constructor’da alır; composition root (veya DI container) Service’i Repository’lerle oluşturur.  
- Testte: Test composition root veya test fixture’ları mock/fake Repository ve Session kullanır.  

Böylece “gerçek” ve “test” wiring’i ayrılır; business kod aynı kalır.

---

## 5. DI Container Kullanmak Zorunlu mu?

Hayır. Basit projede:

- Factory fonksiyonları: `get_user_service()` → Session açar, Repository oluşturur, Service’i döner.  
- Manuel wiring: main’de `session = session_factory()`, `user_repo = UserRepository(session)`, `user_service = UserService(user_repo)`.  

Daha büyük projede **dependency injection container** (dependency_injector, FastAPI’nin Depends’i, vb.) kullanılabilir; ama “constructor’a bağımlılık ver” prensibi aynı kalır.

---

## 6. SQLAlchemy Özelinde Öneriler

- **Session:** Request/use-case bazlı oluşturulup Repository’lere verilir; global tek Session kullanılmaz.  
- **Repository/DAO:** Session’ı constructor’da alır; kendisi Session factory tutmaz (testte farklı Session verilebilsin).  
- **Service:** Repository arayüzüne (interface) bağımlı olsun; somut SQLAlchemy Repository’yi sadece composition root bilir.  
- **Engine:** Uygulama genelinde tek Engine (veya config’e göre bir tane); DI veya modül seviyesinde bir kez oluşturulur.  

---

## 7. Özet

Dependency Injection, Session ve Repository’nin **dışarıdan verilmesini** sağlar. Constructor injection tercih edilir; request-scoped Session web’de dependency/middleware ile yönetilir. Composition root’ta tüm wiring yapılır; testte mock/fake verilir. SQLAlchemy ile kullanımda Session’ı Repository’lere inject edin, commit/rollback’i Service veya UoW’de tutun.

**Ana README’ye dön:** [README.md](README.md)
