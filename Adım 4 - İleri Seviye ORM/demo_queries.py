"""
Adım 4 – Modern Query API Demo

Bu script, AdvUser / AdvOrder modelleri üzerinde:
- select
- join
- subquery
- exists
gibi ileri seviye sorgu örneklerini gösterir.
"""

from sqlalchemy import exists, func, select

from database import Session, init_db
from models import AdvOrder, AdvUser


def seed_data() -> None:
    session = Session()
    try:
        u1 = AdvUser(name="Ali")
        u2 = AdvUser(name="Ayşe")

        u1.orders.extend(
            [
                AdvOrder(price=100, tax=10),
                AdvOrder(price=120, tax=12),
                AdvOrder(price=130, tax=13),
            ]
        )
        u2.orders.append(AdvOrder(price=50, tax=5))

        session.add_all([u1, u2])
        session.commit()
    finally:
        session.close()


def demo_basic_select() -> None:
    print("\n--- select(User).where(...) demo ---")
    session = Session()
    try:
        stmt = select(AdvUser).where(AdvUser.name == "Ali")
        result = session.execute(stmt)
        users = result.scalars().all()
        for u in users:
            print(f"Bulunan kullanıcı: {u.id} - {u.name}")
    finally:
        session.close()


def demo_join_filter() -> None:
    print("\n--- select(User).join(Order).where(Order.total > 200) demo ---")
    session = Session()
    try:
        stmt = (
            select(AdvUser)
            .join(AdvUser.orders)
            .where(AdvOrder.total > 200)
        )
        users = session.execute(stmt).scalars().all()
        for u in users:
            print(f"Toplamı 200'den büyük siparişi olan kullanıcı: {u.name}")
    finally:
        session.close()


def demo_subquery() -> None:
    print("\n--- Subquery demo: 2'den fazla siparişi olan kullanıcılar ---")
    session = Session()
    try:
        subq = (
            select(AdvOrder.user_id)
            .group_by(AdvOrder.user_id)
            .having(func.count(AdvOrder.id) > 2)
            .subquery()
        )

        stmt = select(AdvUser).where(AdvUser.id.in_(subq))
        users = session.execute(stmt).scalars().all()
        for u in users:
            print(f"2'den fazla siparişi olan kullanıcı: {u.name}")
    finally:
        session.close()


def demo_exists() -> None:
    print("\n--- exists() demo: en az bir siparişi olan kullanıcılar ---")
    session = Session()
    try:
        stmt = select(AdvUser).where(
            exists().where(AdvOrder.user_id == AdvUser.id)
        )
        users = session.execute(stmt).scalars().all()
        for u in users:
            print(f"En az bir siparişi olan kullanıcı: {u.name}")
    finally:
        session.close()


if __name__ == "__main__":
    init_db()
    seed_data()
    demo_basic_select()
    demo_join_filter()
    demo_subquery()
    demo_exists()

