"""
Adım 1 – SQLAlchemy Temelleri

Bu dosya, `database.py` ve `models.py` içinde tanımlanan bileşenlerin
birlikte nasıl çalıştığını interaktif bir komut satırı menüsü üzerinden
göstermek için hazırlanmış örnek bir uygulamadır.

Menüde sunulan temel işlemler:
1. Kullanıcı oluştur (CREATE)
2. Tüm kullanıcıları listele (LIST)
3. Kullanıcıyı ID ile getir (GET)
4. Kullanıcıyı güncelle (UPDATE)
5. Kullanıcıyı sil (DELETE)
0. Çıkış

Bu senaryo, README'de anlatılan mimari akışı:
- Engine / Session / Model katmanlarını,
- Session yaşam döngüsünü,
- Temel CRUD işlemlerini
uygulamalı olarak göstermek için tasarlanmıştır.
Gerçek projelerde bu kod genellikle bir framework (FastAPI, Flask vb.)
veya servis katmanı içine taşınır.
"""

from contextlib import contextmanager
from typing import Iterator, List, Optional

from sqlalchemy.orm import Session

from database import Base, engine, get_session
from models import User


def init_db() -> None:
    """
    Base.metadata bilgisini kullanarak veritabanında gerekli tabloları oluşturur.

    - `Base` → Tüm modellerin ortak üst sınıfıdır.
    - `Base.metadata.create_all(engine)` → Tanımlı tüm tabloları, yoksa oluşturur.
    """
    Base.metadata.create_all(bind=engine)


@contextmanager
def session_scope() -> Iterator[Session]:
    """
    Kısa ömürlü bir Session yaşam döngüsünü yöneten context manager.

    Bu desen:
    - Her kullanımda yeni bir Session açar.
    - İşlemler bitince COMMIT eder.
    - Hata durumunda ROLLBACK yapar.
    - En sonunda Session'ı kapatır.

    Readme'de anlatılan "Session = transaction + değişiklik takibi" fikrinin
    pratik karşılığıdır.

    Buradaki `get_session()` fonksiyonu, `database.py` içindeki
    `SessionLocal` factory'sini kullanarak her çağrıda **yeni bir Session
    örneği** üretir. Yani:

    - `SessionLocal` → yapılandırılmış session factory
    - `get_session()` → bu factory'den somut Session nesnesi döndürür
    """
    # `get_session()` çağrısı, SessionLocal factory'sinden yeni bir Session
    # örneği üretir. Bu Session, context manager bloğu süresince geçerlidir.
    session = get_session()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()


def create_user(session: Session, name: str, email: str, password: str) -> User:
    """
    Verilen alanlara sahip yeni bir `User` nesnesi oluşturur ve veritabanına yazar.

    - Nesne önce Session'a eklenir.
    - Flush/commit sırasında uygun INSERT SQL'i üretilir ve DB'ye gönderilir.
    """
    user = User(name=name, email=email, password=password)
    session.add(user)
    # commit, session_scope içinde yönetildiği için burada ayrıca commit çağrılmaz.
    session.flush()  # id gibi alanların doldurulması için isteğe bağlı flush.
    session.refresh(user)
    return user


def list_users(session: Session) -> List[User]:
    """
    Tüm kullanıcı kayıtlarını döndürür.

    Bu fonksiyon, ORM üzerinden SELECT sorgusunun nasıl yazılacağını gösterir.
    """
    return session.query(User).order_by(User.id).all()


def get_user_by_id(session: Session, user_id: int) -> Optional[User]:
    """
    Verilen id değerine sahip kullanıcıyı döndürür.
    Kullanıcı bulunamazsa None döner.
    """
    return session.get(User, user_id)


def update_user(
    session: Session,
    user_id: int,
    name: Optional[str] = None,
    email: Optional[str] = None,
    password: Optional[str] = None,
) -> Optional[User]:
    """
    Verilen id değerine sahip kullanıcıyı günceller.

    - İlgili kullanıcı bulunamazsa None döner.
    - Parametrelerden None olmayanlar güncellenir.
    """
    user = session.get(User, user_id)
    if user is None:
        return None

    if name is not None and name != "":
        user.name = name
    if email is not None and email != "":
        user.email = email
    if password is not None and password != "":
        user.password = password

    # Değişiklikler, context manager içindeki commit sırasında veritabanına yansıtılır.
    return user


def delete_user(session: Session, user_id: int) -> bool:
    """
    Verilen id değerine sahip kullanıcıyı siler.

    - Kullanıcı bulunursa siler ve True döner.
    - Bulunamazsa False döner.
    """
    user = session.get(User, user_id)
    if user is None:
        return False
    session.delete(user)
    return True


def print_menu() -> None:
    """
    Komut satırı menüsünü ekrana yazdırır.
    """
    print("\nSQLAlchemy User Yönetim Menüsü")
    print("-" * 40)
    print("1) Kullanıcı oluştur (CREATE)")
    print("2) Kullanıcıları listele (LIST)")
    print("3) Kullanıcıyı ID ile getir (GET)")
    print("4) Kullanıcıyı güncelle (UPDATE)")
    print("5) Kullanıcıyı sil (DELETE)")
    print("0) Çıkış")


def run_cli() -> None:
    """
    Basit bir komut satırı arayüzü ile CRUD işlemlerini adım adım gösterir.
    """
    init_db()
    print("Veritabanı şeması oluşturuldu (varsa güncel hali korundu).")

    while True:
        print_menu()
        choice = input("Seçiminiz: ").strip()

        if choice == "0":
            print("Çıkılıyor...")
            break

        elif choice == "1":
            # CREATE
            name = input("İsim: ").strip()
            email = input("E-posta: ").strip()
            password = input("Şifre: ").strip()

            with session_scope() as session:
                try:
                    user = create_user(session, name=name, email=email, password=password)
                    print(f"Oluşturulan kullanıcı: {user}")
                except Exception as exc:
                    print(f"Kullanıcı oluşturulurken hata oluştu: {exc}")

        elif choice == "2":
            # LIST
            with session_scope() as session:
                users = list_users(session)
                if not users:
                    print("Kayıtlı kullanıcı bulunamadı.")
                else:
                    print("Kayıtlı kullanıcılar:")
                    for u in users:
                        print(f" - {u}")

        elif choice == "3":
            # GET
            try:
                user_id = int(input("Kullanıcı ID: ").strip())
            except ValueError:
                print("Geçerli bir tam sayı ID giriniz.")
                continue

            with session_scope() as session:
                user = get_user_by_id(session, user_id)
                if user is None:
                    print("Kullanıcı bulunamadı.")
                else:
                    print(f"Bulunan kullanıcı: {user}")

        elif choice == "4":
            # UPDATE
            try:
                user_id = int(input("Güncellenecek kullanıcı ID: ").strip())
            except ValueError:
                print("Geçerli bir tam sayı ID giriniz.")
                continue

            new_name = input("Yeni isim (boş bırakırsanız değişmez): ").strip()
            new_email = input("Yeni e-posta (boş bırakırsanız değişmez): ").strip()
            new_password = input("Yeni şifre (boş bırakırsanız değişmez): ").strip()

            with session_scope() as session:
                user = update_user(
                    session,
                    user_id=user_id,
                    name=new_name or None,
                    email=new_email or None,
                    password=new_password or None,
                )
                if user is None:
                    print("Kullanıcı bulunamadı, güncelleme yapılmadı.")
                else:
                    print(f"Güncellenen kullanıcı: {user}")

        elif choice == "5":
            # DELETE
            try:
                user_id = int(input("Silinecek kullanıcı ID: ").strip())
            except ValueError:
                print("Geçerli bir tam sayı ID giriniz.")
                continue

            with session_scope() as session:
                success = delete_user(session, user_id)
                if not success:
                    print("Kullanıcı bulunamadı, silme işlemi yapılmadı.")
                else:
                    print("Kullanıcı silindi.")

        else:
            print("Geçersiz seçim. Lütfen menüdeki seçeneklerden birini kullanın.")


if __name__ == "__main__":
    run_cli()
