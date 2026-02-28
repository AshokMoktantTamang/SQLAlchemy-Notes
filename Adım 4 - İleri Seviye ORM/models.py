"""
Adım 4 – İleri Seviye ORM Modelleri

Bu dosya, ileri seviye örneklerde kullanılacak ortak modelleri içerir:

- AdvUser / AdvOrder          → loading stratejileri, hybrid property, advanced query
- AdvStudent / AdvCourse / AdvEnrollment → association proxy, association object
- Animal / Dog                → polymorphic mapping
- SoftUser                    → soft delete deseni
- TenantUser                  → multi-tenant deseni
"""

from datetime import datetime, timezone

from sqlalchemy import (
    Boolean,
    Column,
    DateTime,
    ForeignKey,
    Integer,
    String,
)
from sqlalchemy.ext.hybrid import hybrid_property
from sqlalchemy.orm import relationship

from database import Base


# ---------------------------------------------------------------------------
# 1. Gelişmiş loading + hybrid property için User / Order modeli
# ---------------------------------------------------------------------------


class AdvUser(Base):
    __tablename__ = "adv_users"

    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)

    # İlişkili siparişler; loading stratejilerini demo dosyalarında
    # `selectinload`, `joinedload`, `contains_eager` ile yöneteceğiz.
    orders = relationship("AdvOrder", back_populates="user")


class AdvOrder(Base):
    __tablename__ = "adv_orders"

    id = Column(Integer, primary_key=True)
    price = Column(Integer, nullable=False)
    tax = Column(Integer, nullable=False, default=0)

    user_id = Column(Integer, ForeignKey("adv_users.id"), nullable=False)
    user = relationship("AdvUser", back_populates="orders")

    # Hybrid property: hem Python tarafında hem SQL tarafında kullanılabilir.
    @hybrid_property
    def total(self) -> int:
        return self.price + self.tax

    @total.expression
    def total(cls):
        # SQL tarafında kullanılacak ifade
        return cls.price + cls.tax


# ---------------------------------------------------------------------------
# 2. Association object + association proxy için Student / Course / Enrollment
# ---------------------------------------------------------------------------


class AdvEnrollment(Base):
    __tablename__ = "adv_enrollments"

    id = Column(Integer, primary_key=True)
    student_id = Column(ForeignKey("adv_students.id"), nullable=False)
    course_id = Column(ForeignKey("adv_courses.id"), nullable=False)
    grade = Column(Integer, nullable=True)
    enrolled_at = Column(DateTime, default=datetime.now(timezone.utc))

    student = relationship("AdvStudent", back_populates="enrollments")
    course = relationship("AdvCourse", back_populates="enrollments")


class AdvStudent(Base):
    __tablename__ = "adv_students"

    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)

    # Tüm Enrollment kayıtları
    enrollments = relationship("AdvEnrollment", back_populates="student")

    # Association proxy örneğinde, bu model `association_proxy` ile
    # doğrudan courses listesine erişmek için kullanılacaktır.


class AdvCourse(Base):
    __tablename__ = "adv_courses"

    id = Column(Integer, primary_key=True)
    title = Column(String, nullable=False)

    enrollments = relationship("AdvEnrollment", back_populates="course")


# ---------------------------------------------------------------------------
# 3. Polymorphic mapping için Animal / Dog
# ---------------------------------------------------------------------------


class Animal(Base):
    __tablename__ = "adv_animals"

    id = Column(Integer, primary_key=True)
    type = Column(String, nullable=False)
    name = Column(String, nullable=False)

    __mapper_args__ = {
        "polymorphic_on": type,
        "polymorphic_identity": "animal",
    }


class Dog(Animal):
    __mapper_args__ = {
        "polymorphic_identity": "dog",
    }


# ---------------------------------------------------------------------------
# 4. Soft delete + multi-tenant için basit modeller
# ---------------------------------------------------------------------------


class SoftUser(Base):
    """
    Soft delete desenini göstermek için basit bir model.

    Kayıtlar fiziksel olarak silinmek yerine `deleted=True` işaretlenerek
    "silinmiş" kabul edilir.
    """

    __tablename__ = "adv_soft_users"

    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)
    deleted = Column(Boolean, default=False, nullable=False)


class TenantUser(Base):
    """
    Multi-tenant desenini göstermek için basit bir model.

    Her kayıt, `tenant_id` alanı ile bir kiracıya (tenant) ait olarak işaretlenir.
    Global sorgu filtreleri ile sadece ilgili tenant’ın verileri okunabilir.
    """

    __tablename__ = "adv_tenant_users"

    id = Column(Integer, primary_key=True)
    tenant_id = Column(Integer, nullable=False, index=True)
    name = Column(String, nullable=False)

