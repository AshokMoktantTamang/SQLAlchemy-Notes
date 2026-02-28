"""
Adım 3 – Many-to-Many (Basit Association Table)

Senaryo:
- Bir Student birçok Course alabilir.
- Bir Course birçok Student tarafından alınabilir.

Bu örnekte:
- Sadece ilişki bilgisi tutulur (ek alan yoktur).
- Ara tablo bağımsız bir model sınıfı değil, `Table` nesnesidir.
"""

from sqlalchemy import Column, ForeignKey, Integer, String, Table
from sqlalchemy.orm import relationship

from database import Base


student_course = Table(
    "rel3_student_course",
    Base.metadata,
    Column("student_id", ForeignKey("rel3_students.id"), primary_key=True),
    Column("course_id", ForeignKey("rel3_courses.id"), primary_key=True),
)


class Student(Base):
    __tablename__ = "rel3_students"

    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)

    # Student.courses -> bu öğrencinin aldığı dersler
    courses = relationship(
        "Course",
        secondary=student_course,
        back_populates="students",
    )


class Course(Base):
    __tablename__ = "rel3_courses"

    id = Column(Integer, primary_key=True)
    title = Column(String, nullable=False)

    # Course.students -> bu dersi alan öğrenciler
    students = relationship(
        "Student",
        secondary=student_course,
        back_populates="courses",
    )

