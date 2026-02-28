"""
Adım 7 – Async SQLAlchemy Modelleri

Async demoları için basit kullanıcı modeli.
"""

from sqlalchemy import Column, Integer, String

from database_async import Base


class AsyncUser(Base):
    """Async Session demoları için basit kullanıcı."""

    __tablename__ = "async_users"

    id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)
    email = Column(String(200), unique=True)
