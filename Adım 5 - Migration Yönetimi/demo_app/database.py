"""
Adım 5 – Migration Yönetimi (Alembic Örneği)

Bu dosya, örnek migration senaryosu için kullanılacak
SQLAlchemy `engine`, `SessionLocal` ve `Base` tanımlarını içerir.

Bu mini uygulama:
- `models_v1.py` → ilk şema (sadece User tablosu)
- `models_v2.py` → User tablosuna email kolonu eklenmiş hali
üzerinden Alembic migration akışını anlatmak için tasarlanmıştır.
"""

from sqlalchemy import create_engine
from sqlalchemy.orm import declarative_base, sessionmaker

DATABASE_URL = "sqlite:///migration_demo.db"

engine = create_engine(DATABASE_URL, echo=True, future=True)

SessionLocal = sessionmaker(bind=engine, autoflush=False, autocommit=False, future=True)

Base = declarative_base()


def get_session():
    """Örnek kodlarda kullanılmak üzere yeni bir Session döndürür."""
    return SessionLocal()

