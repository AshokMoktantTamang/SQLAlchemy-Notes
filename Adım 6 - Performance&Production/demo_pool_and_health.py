"""
Adım 6 – Connection Pool ve Health Check Demo

- Engine pool parametrelerinin kullanımı
- Basit veritabanı sağlık kontrolü (health check)
"""

from sqlalchemy import text

from database import engine, init_db


def db_health_check() -> bool:
    """
    Veritabanı bağlantısının canlı olduğunu kontrol eder.
    Liveness/readiness probe'larında kullanılabilir.
    """
    try:
        with engine.connect() as conn:
            conn.execute(text("SELECT 1"))
        return True
    except Exception as e:
        print(f"Health check FAILED: {e}")
        return False


def show_pool_status() -> None:
    """Pool durumunu gösterir (QueuePool kullanılıyorsa)."""
    pool = engine.pool
    print("\n--- Pool bilgisi ---")
    print(f"Pool sınıfı: {type(pool).__name__}")
    for attr in ("size", "checkedout", "overflow"):
        val = getattr(pool, attr, None)
        if callable(val):
            val = val()
        print(f"{attr}: {val}")


if __name__ == "__main__":
    init_db()
    print("Veritabanı şeması oluşturuldu.")

    ok = db_health_check()
    print(f"Health check: {'OK' if ok else 'FAILED'}")

    show_pool_status()
    print("\nBitti.")
