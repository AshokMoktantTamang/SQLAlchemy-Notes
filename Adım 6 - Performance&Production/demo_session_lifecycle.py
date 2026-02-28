"""
Adım 6 – Session Yaşam Döngüsü (Request-Scoped) Demo

Production'da her istek için ayrı Session açıp kapatma desenini gösterir.
Hata durumunda rollback ve close garantisi.
"""

import uuid

from database import init_db, session_scope
from models import Product


def simulate_request_success() -> None:
    """Başarılı istek: commit ile biter."""
    # Her çalıştırmada benzersiz SKU (tekrar çalıştırılabilir demo)
    sku = f"REQ-{uuid.uuid4().hex[:8]}"
    print("İstek 1 (başarılı): Session açıldı.")
    with session_scope() as session:
        p = Product(name="Request Ürün", sku=sku, quantity=10)
        session.add(p)
    print("İstek 1: Session kapatıldı, commit yapıldı.\n")
    return sku


def simulate_request_failure(sku: str) -> None:
    """Hatalı istek: aynı SKU tekrar eklenmeye çalışılır → rollback, close."""
    print("İstek 2 (hata simülasyonu): Session açıldı.")
    try:
        with session_scope() as session:
            session.add(Product(name="X", sku=sku, quantity=0))
            # Aynı sku zaten var; unique constraint hatası
    except Exception as e:
        print(f"İstek 2: Hata yakalandı: {type(e).__name__}")
        print("Session rollback ve close otomatik yapıldı.\n")


if __name__ == "__main__":
    print("--- Session Yaşam Döngüsü (Request-Scoped) Demo ---\n")

    init_db()

    sku = simulate_request_success()
    simulate_request_failure(sku)

    print("Bitti.")
