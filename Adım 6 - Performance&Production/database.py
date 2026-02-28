"""
Adım 6 – Performance & Production

Production tarzı Engine ve Session yapılandırması:
- Connection pool parametreleri (pool_size, max_overflow, pool_recycle, pool_pre_ping)
- Session factory (request-scoped kullanım için uygun)
- Ortam değişkeninden URL okuma örneği (opsiyonel)
"""

import os
from contextlib import contextmanager
from typing import Iterator

from sqlalchemy import create_engine
from sqlalchemy.orm import Session, declarative_base, sessionmaker

# Production'da URL ortam değişkeninden okunmalı; yoksa demo için SQLite
DATABASE_URL = os.environ.get(
    "DATABASE_URL",
    "sqlite:///perf_production.db",
)

# SQLite pool_recycle/pool_pre_ping bazı sürümlerde farklı davranabilir;
# PostgreSQL/MySQL için tüm parametreler anlamlıdır.
_connect_args = {}
if DATABASE_URL.startswith("sqlite"):
    _connect_args["check_same_thread"] = False

engine = create_engine(
    DATABASE_URL,
    echo=os.environ.get("SQL_ECHO", "false").lower() == "true",
    future=True,
    pool_size=5,
    max_overflow=10,
    pool_timeout=30,
    pool_recycle=1800,
    pool_pre_ping=not DATABASE_URL.startswith("sqlite"),
    connect_args=_connect_args,
)

SessionLocal = sessionmaker(
    bind=engine,
    autoflush=False,
    autocommit=False,
    expire_on_commit=False,
    future=True,
)

Base = declarative_base()


def get_session() -> Session:
    """Yeni bir Session örneği döndürür. Caller session'ı kapatmalıdır."""
    return SessionLocal()


@contextmanager
def session_scope() -> Iterator[Session]:
    """
    Request-scoped Session örneği.
    commit/rollback ve close otomatik yönetilir.
    """
    session = SessionLocal()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()


def init_db() -> None:
    """Tüm modellerden tabloları oluşturur."""
    Base.metadata.create_all(bind=engine)
