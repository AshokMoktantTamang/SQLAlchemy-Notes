"""
Adım 4 – Hybrid Property Demo

Bu script, AdvOrder modelindeki `total` hybrid property'nin:
- Python tarafında attribute gibi
- SQL tarafında filtre ifadesi gibi
nasıl kullanılacağını gösterir.
"""

from database import Session, init_db
from models import AdvOrder, AdvUser


def seed_data() -> None:
    session = Session()
    try:
        u = AdvUser(name="Hybrid Kullanıcısı")
        u.orders.extend(
            [
                AdvOrder(price=50, tax=5),    # total = 55
                AdvOrder(price=120, tax=10),  # total = 130
            ]
        )
        session.add(u)
        session.commit()
    finally:
        session.close()


def demo_hybrid_usage() -> None:
    print("\n--- Hybrid property demo ---")
    session = Session()
    try:
        # Python tarafında kullanım
        order = session.query(AdvOrder).first()
        print(f"İlk sipariş total (Python tarafı): {order.total}")

        # SQL tarafında kullanım: total > 100 olan siparişler
        high_value_orders = (
            session.query(AdvOrder)
            .filter(AdvOrder.total > 100)
            .all()
        )
        print("total > 100 olan siparişler:")
        for o in high_value_orders:
            print(f"  id={o.id}, price={o.price}, tax={o.tax}, total={o.total}")
    finally:
        session.close()


if __name__ == "__main__":
    init_db()
    seed_data()
    demo_hybrid_usage()

