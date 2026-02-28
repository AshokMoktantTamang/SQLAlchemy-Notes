"""
Adım 2 – ORM

Bu dosya, akademi senaryosu (Student–Course–Enrollment) için
tanımlanan modelleri ve veritabanı bağlantısını kullanarak
CLI menüsünü başlatan giriş noktasıdır.

Tüm etkileşim ve menü akışı `cli.py` içinde tanımlanmıştır.
"""

from database import Base, engine
from cli import run_cli


def init_db() -> None:
    """
    Mevcut modellerden (`Base`) yola çıkarak veritabanı tablolarını oluşturur.
    """
    Base.metadata.create_all(bind=engine)


if __name__ == "__main__":
    init_db()
    run_cli()

