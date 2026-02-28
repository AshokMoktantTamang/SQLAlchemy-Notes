"""
Adım 5 – Migration Örneği (v2)

İkinci sürüm:
- `User` tablosuna yeni bir `email` alanı eklenmiştir.
- Bu değişiklik için Alembic migration dosyası üretilecek.
"""

from sqlalchemy import Column, Integer, String

from .database import Base


class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)

    # Yeni eklenen kolon:
    # - NULL olabilir (mevcut kayıtlarda problem çıkmasın diye)
    # - Benzersizdir ve indexlidir (gerçekçi bir senaryo için)
    email = Column(String(200), unique=True, index=True, nullable=True)

