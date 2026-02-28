"""
Adım 5 – Migration Örneği (v1)

İlk sürüm:
- Tek bir `User` tablosu var.
- Sadece `id` ve `name` alanlarını içeriyor.

Bu sürüm, Alembic ile oluşturacağımız ilk migration'a temel olacaktır.
"""

from sqlalchemy import Column, Integer, String

from .database import Base


class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)

