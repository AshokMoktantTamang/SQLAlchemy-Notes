"""
Adım 3 – One-to-Many Demo

Bu script:
- User / Order modelleri (One-to-Many) üzerinden
- Kayıt ekleme
- Lazy loading
- N+1 problemi ve selectinload çözümünü
örnekler.
"""

from sqlalchemy.orm import selectinload

from database import Session, init_db
from models_one_to_many import Order, User


def seed_data() -> None:
    """User / Order için örnek veriler oluşturur."""
    session = Session()
    try:
        # Basit örnek veriler
        ali = User(name="Ali")
        ayse = User(name="Ayşe")

        ali.orders.append(Order(amount=100))
        ali.orders.append(Order(amount=200))

        ayse.orders.append(Order(amount=150))

        session.add_all([ali, ayse])
        session.commit()
    finally:
        session.close()


def demo_lazy_loading() -> None:
    """Tek bir kullanıcı için lazy loading davranışını gösterir."""
    print("\n--- Lazy loading demo ---")
    session = Session()
    try:
        user = session.query(User).first()
        print(f"Kullanıcı: {user.name}")
        # Burada, orders erişiminde ikinci bir SELECT tetiklenir (lazy="select").
        print(f"Siparişler: {user.orders}")
    finally:
        session.close()


def demo_n_plus_one() -> None:
    """N+1 problemini (her user için ek SELECT) üretir."""
    print("\n--- N+1 demo (kaç sorgu çalıştığını echo=True ile izle) ---")
    session = Session()
    try:
        users = session.query(User).all()
        for u in users:
            # Her erişimde ayrı SELECT tetiklenir.
            print(u.name, "→", [o.amount for o in u.orders])
    finally:
        session.close()


def demo_selectinload() -> None:
    """selectinload ile N+1 probleminin nasıl çözüldüğünü gösterir."""
    print("\n--- selectinload demo (N+1 çözümü) ---")
    session = Session()
    try:
        users = (
            session.query(User)
            .options(selectinload(User.orders))
            .all()
        )
        for u in users:
            # Burada ek sorgu tetiklenmez; orders zaten yüklenmiştir.
            print(u.name, "→", [o.amount for o in u.orders])
    finally:
        session.close()


if __name__ == "__main__":
    init_db()
    seed_data()
    demo_lazy_loading()
    demo_n_plus_one()
    demo_selectinload()

