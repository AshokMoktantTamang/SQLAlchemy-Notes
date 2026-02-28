"""
Adım 3 – Many-to-Many (Association Object Pattern)

Senaryo:
- Student ↔ Course ilişkisi var.
- Ara tabloda ek alanlar da tutulmak isteniyor (ör. grade, enrollment_date).

Bu örnekte:
- Enrollment ayrı bir model sınıfıdır.
- Ek alanlar (ör. grade) doğrudan Enrollment üzerinde yer alır.
"""

from datetime import datetime, timezone

from sqlalchemy import Column, DateTime, ForeignKey, Integer, String
from sqlalchemy.orm import relationship

from database import Base


class Enrollment(Base):
    __tablename__ = "rel3_enrollments"

    id = Column(Integer, primary_key=True)
    student_id = Column(ForeignKey("rel3_students2.id"), nullable=False)
    course_id = Column(ForeignKey("rel3_courses2.id"), nullable=False)
    grade = Column(Integer, nullable=True)
    enrolled_at = Column(DateTime, default=datetime.now(timezone.utc))

    student = relationship("Student2", back_populates="enrollments")
    course = relationship("Course2", back_populates="enrollments")


class Student2(Base):
    __tablename__ = "rel3_students2"

    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)

    # Student2.enrollments -> bu öğrencinin tüm kayıtları
    enrollments = relationship("Enrollment", back_populates="student")


class Course2(Base):
    __tablename__ = "rel3_courses2"

    id = Column(Integer, primary_key=True)
    title = Column(String, nullable=False)

    # Course2.enrollments -> bu derse ait tüm kayıtlar
    enrollments = relationship("Enrollment", back_populates="course")

