"""
Adım 6 – Performance & Production Modelleri

Demo scriptleri için basit modeller:
- Product: bulk insert ve indeks örneği
"""

from sqlalchemy import Column, Integer, String

from database import Base


class Product(Base):
    """
    Toplu ekleme ve indeks demoları için basit ürün modeli.
    """

    __tablename__ = "perf_products"

    id = Column(Integer, primary_key=True)
    name = Column(String(200), nullable=False, index=True)
    sku = Column(String(50), unique=True, index=True)
    quantity = Column(Integer, default=0)
