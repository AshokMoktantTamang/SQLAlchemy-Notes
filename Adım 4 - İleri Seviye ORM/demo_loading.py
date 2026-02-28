"""
Adım 4 – Gelişmiş Loading Stratejileri Demo

Bu script, AdvUser / AdvOrder modelleri üzerinde:
- joinedload
- selectinload
- contains_eager
örneklerini gösterir.
"""

from sqlalchemy.orm import contains_eager, joinedload, selectinload

from database import Session, init_db
from models import AdvOrder, AdvUser


def seed_data() -> None:
    """AdvUser / AdvOrder için basit örnek veriler oluşturur."""
    session = Session()
    try:
        ali = AdvUser(name="Ali")
        ayse = AdvUser(name="Ayşe")

        ali.orders.extend(
            [
                AdvOrder(price=100, tax=10),
                AdvOrder(price=200, tax=20),
            ]
        )
        ayse.orders.append(AdvOrder(price=150, tax=15))

        session.add_all([ali, ayse])
        session.commit()
    finally:
        session.close()


def demo_joinedload() -> None:
    """joinedload ile tek sorguda JOIN kullanarak eager loading örneği."""
    print("\n--- joinedload demo ---")
    session = Session()
    try:
        users = (
            session.query(AdvUser)
            .options(joinedload(AdvUser.orders))
            .all()
        )
        for u in users:
            print(u.name, "→", [o.total for o in u.orders])
    finally:
        session.close()


def demo_selectinload() -> None:
    """selectinload ile 2 sorguda, N+1 olmadan eager loading örneği."""
    print("\n--- selectinload demo ---")
    session = Session()
    try:
        users = (
            session.query(AdvUser)
            .options(selectinload(AdvUser.orders))
            .all()
        )
        for u in users:
            print(u.name, "→", [o.total for o in u.orders])
    finally:
        session.close()


def demo_contains_eager() -> None:
    """
    contains_eager ile manuel JOIN + eager loading.

    JOIN ifadesini biz yazıyoruz; contains_eager, sonuç setini AdvUser.orders
    ilişkisine map ediyor, ek SELECT tetiklenmiyor.
    """
    print("\n--- contains_eager demo ---")
    session = Session()
    try:
        q = (
            session.query(AdvUser)
            .join(AdvUser.orders)
            .options(contains_eager(AdvUser.orders))
        )
        users = q.all()
        for u in users:
            print(u.name, "→", [o.total for o in u.orders])
    finally:
        session.close()


if __name__ == "__main__":
    init_db()
    seed_data()
    demo_joinedload()
    demo_selectinload()
    demo_contains_eager()

