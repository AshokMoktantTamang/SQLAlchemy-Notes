"""
Adım 3 – One-to-Many İlişki Örneği

Senaryo:
- Bir User'ın birden fazla Order'ı olabilir.

Amaç:
- ForeignKey ve relationship farkını göstermek
- `cascade="all, delete-orphan"` davranışını ortaya koymak
"""

from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.orm import relationship

from database import Base


class User(Base):
    __tablename__ = "rel3_users"

    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)

    # ORM seviyesi ilişki:
    # - user.orders -> bu kullanıcıya ait Order nesneleri listesi
    # - back_populates="user" -> Order.user alanı ile iki yönlü senkronizasyon
    # - cascade="all, delete-orphan" -> User silinince bağlı Order kayıtları da silinir
    orders = relationship(
        "Order",
        back_populates="user",
        cascade="all, delete-orphan",
    )


class Order(Base):
    __tablename__ = "rel3_orders"

    id = Column(Integer, primary_key=True)
    amount = Column(Integer, nullable=False)

    # DB seviyesi ilişki:
    # - order.user_id sütunu, rel3_users.id alanına referans verir
    user_id = Column(Integer, ForeignKey("rel3_users.id"), nullable=False)

    # ORM seviyesi ilişki:
    # - order.user -> ilgili User nesnesi
    user = relationship("User", back_populates="orders")

