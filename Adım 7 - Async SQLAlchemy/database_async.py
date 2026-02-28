"""
Adım 7 – Async SQLAlchemy

Async engine ve AsyncSession yapılandırması.
SQLite + aiosqlite (pip install aiosqlite gerekir).
"""

from sqlalchemy.ext.asyncio import (
    AsyncSession,
    async_sessionmaker,
    create_async_engine,
)
from sqlalchemy.orm import declarative_base

# Demo: SQLite async. Production'da: postgresql+asyncpg://...
DATABASE_URL = "sqlite+aiosqlite:///async_demo.db"

engine = create_async_engine(
    DATABASE_URL,
    echo=False,
)

AsyncSessionLocal = async_sessionmaker(
    bind=engine,
    class_=AsyncSession,
    expire_on_commit=False,
    autoflush=False,
    autocommit=False,
)

Base = declarative_base()


async def init_db() -> None:
    """Tabloları oluşturur (async engine üzerinde run_sync ile)."""
    async with engine.begin() as conn:
        await conn.run_sync(Base.metadata.create_all)
