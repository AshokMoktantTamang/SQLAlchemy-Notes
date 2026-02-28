"""
Adım 6 – Bulk Insert Demo

Tek tek add() yerine add_all() ile toplu ekleme ve
Core insert() ile daha da hızlı toplu ekleme örneği.
"""

import time

from sqlalchemy import insert

from database import init_db, session_scope
from models import Product


"""
Adım 6 – Bulk Insert Demo

Tek tek add() yerine add_all() ile toplu ekleme ve
Core insert() ile daha da hızlı toplu ekleme örneği.
"""

import time
import uuid

from sqlalchemy import insert

from database import init_db, session_scope
from models import Product


def bulk_add_all(count: int = 500, prefix: str = "") -> float:
    """add_all ile toplu ekleme; süreyi saniye olarak döndürür."""
    with session_scope() as session:
        start = time.perf_counter()
        session.add_all(
            [
                Product(
                    name=f"Ürün {prefix}{i}",
                    sku=f"SKU-{prefix}{i:06d}",
                    quantity=i % 100,
                )
                for i in range(count)
            ]
        )
        elapsed = time.perf_counter() - start
    return elapsed


def bulk_core_insert(count: int = 500, prefix: str = "") -> float:
    """Core insert() ile toplu ekleme; ORM nesnesi oluşturmadan."""
    from database import engine

    data = [
        {"name": f"Ürün Core {prefix}{i}", "sku": f"CORE-{prefix}{i:06d}", "quantity": i % 100}
        for i in range(count)
    ]
    start = time.perf_counter()
    with engine.connect() as conn:
        conn.execute(insert(Product.__table__), data)
        conn.commit()
    return time.perf_counter() - start


if __name__ == "__main__":
    init_db()
    print("--- Bulk Insert Demo ---\n")

    # Her çalıştırmada benzersiz prefix (tekrar çalıştırılabilir demo)
    prefix = uuid.uuid4().hex[:6] + "-"
    n = 300

    t1 = bulk_add_all(n, prefix)
    print(f"add_all({n} kayıt): {t1:.3f} saniye")

    t2 = bulk_core_insert(n, prefix)
    print(f"Core insert({n} kayıt): {t2:.3f} saniye")

    with session_scope() as session:
        total = session.query(Product).count()
    print(f"\nToplam Product kaydı: {total}")
    print("\nBitti.")
