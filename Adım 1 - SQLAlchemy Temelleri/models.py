"""
Adım 1 – SQLAlchemy Temelleri

Bu modül, `database.Base` sınıfını kullanarak veritabanı tablolarına
karşılık gelen ORM modellerini (mapped class) tanımlar.

Şu aşamada tek bir basit model bulunmaktadır:
- `User` → `users` tablosunu temsil eder.

İlerleyen adımlarda ilişki örnekleri eklendiğinde, aynı yapıya yeni modeller de
eklenebilir (ör. `Order`, `Product` vb.).
"""

from sqlalchemy import Column, Integer, String

from database import Base


class User(Base):
    """
    `users` tablosunu temsil eden temel kullanıcı modeli.

    Bu sınıf:
    - `Base`'ten miras alarak tablo şemasını SQLAlchemy metadata'sına kaydeder.
    - Sütun tanımları ile tablo yapısını belirler.
    - ORM üzerinden SELECT/INSERT/UPDATE/DELETE işlemlerinde kullanılacak
      Python nesnesinin şeklini tarif eder.
    """

    __tablename__ = "users"

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String, index=True)
    email = Column(String, unique=True, index=True)
    password = Column(String)

    def __repr__(self) -> str:
        # Hata ayıklama ve log çıktılarında anlamlı bir temsil sağlar.
        return f"User(id={self.id!r}, name={self.name!r}, email={self.email!r})"