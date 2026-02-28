"""
Adım 2 – ORM Modelleri

Bu dosya, akademi senaryosu için üç temel ORM modelini tanımlar:

- Student  → `students` tablosu
- Course   → `courses` tablosu
- Enrollment → `enrollments` (öğrenci–ders ilişkisini taşıyan ara tablo)

`relationship()` nedir?
------------------------
`relationship`, SQLAlchemy ORM seviyesinde iki model sınıfı arasındaki
bağı ifade eder. Veritabanı tarafında bu bağ, genellikle `ForeignKey`
sütunları ile kurulur; ORM tarafında ise:

- `relationship("DiğerModel")` ile nesne üzerinden erişim sağlanır
- `back_populates` ile iki yönlü ilişki tanımlanır

Özetle:
- ForeignKey → veritabanı düzeyi ilişki
- relationship → Python nesneleri düzeyi ilişki

Bu dosyanın sonunda, kullanılan tüm `back_populates` ve `cascade`
değerlerinin ne anlama geldiği ayrıca özetlenmiştir.
"""

from sqlalchemy import Column, Integer, String, DateTime, ForeignKey
from sqlalchemy.orm import relationship
from datetime import datetime, timezone
from database import Base


class Student(Base):
    __tablename__ = "students"

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String(100), nullable=False)
    email = Column(String(100), unique=True, index=True)

    # Bir öğrencinin birçok derse kayıt olabilmesini temsil eder.
    # Bu ilişki, Enrollment ara tablosu üzerinden kurulan Many-to-Many ilişkinin "öğrenci tarafı"dır.
    enrollments = relationship(
        "Enrollment", 
        back_populates="student",
        cascade="all, delete-orphan",
    )

class Course(Base):
    __tablename__ = "courses"

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String(100), nullable=False)
    description = Column(String(255), nullable=False)

    # Bir derse birçok öğrencinin kayıt olabilmesini temsil eder.
    # Yine Enrollment tablosu üzerinden Many-to-Many ilişkinin "ders tarafı"dır.
    enrollments = relationship(
        "Enrollment",
        back_populates="course",
        cascade="all, delete-orphan",
    )

class Enrollment(Base):
    __tablename__ = "enrollments"

    id = Column(Integer, primary_key=True, index=True)

    # ForeignKey tanımları:
    # - student_id → students.id alanına bağlıdır (hangi öğrencinin kaydı?)
    # - course_id  → courses.id alanına bağlıdır (hangi derse kayıt?)
    # Bu iki foreign key sayesinde Enrollment, Many-to-Many ilişkiyi taşıyan "ara tablo" rolünü üstlenir.
    student_id = Column(Integer, ForeignKey("students.id"), nullable=False)
    course_id = Column(Integer, ForeignKey("courses.id"), nullable=False)
    enrollment_date = Column(DateTime, default=datetime.now(timezone.utc))

    # ORM seviyesinde, Enrollment → Student ilişki nesnesi.
    # Böylece enrollment.student üzerinden doğrudan Student nesnesine erişilebilir.
    student = relationship("Student", back_populates="enrollments")

    # ORM seviyesinde, Enrollment → Course ilişki nesnesi.
    # Böylece enrollment.course üzerinden doğrudan Course nesnesine erişilebilir.
    course = relationship("Course", back_populates="enrollments")


# -----------------------------------------------------------------------------
# relationship, back_populates ve cascade özet tablosu
# -----------------------------------------------------------------------------
#
# Student.enrollments:
#   relationship(
#       "Enrollment",
#       back_populates="student",
#       cascade="all, delete-orphan",
#   )
#   - back_populates="student":
#       Enrollment.student alanı ile çift yönlü ilişki kurar.
#       Yani:
#         student.enrollments  → öğrenciye ait Enrollment listesi
#         enrollment.student   → ilgili Student nesnesi
#   - cascade="all, delete-orphan":
#       Bir Student nesnesi Session'dan silindiğinde (veya ilişkiden koparıldığında),
#       ona bağlı Enrollment nesneleri de silinir. Bu, "öğrenci yoksa kaydı da yoktur"
#       kuralını ORM seviyesinde uygular.
#
# Course.enrollments:
#   relationship(
#       "Enrollment",
#       back_populates="course",
#       cascade="all, delete-orphan",
#   )
#   - back_populates="course":
#       Enrollment.course alanı ile çift yönlü ilişki kurar.
#       Yani:
#         course.enrollments  → derse ait Enrollment listesi
#         enrollment.course   → ilgili Course nesnesi
#   - cascade="all, delete-orphan":
#       Bir Course nesnesi silindiğinde, ona bağlı Enrollment kayıtları da
#       silinir; "ders yoksa ona ait kayıt da yoktur" kuralını uygular.
#
# Enrollment.student:
#   relationship("Student", back_populates="enrollments")
#   - back_populates:
#       Student.enrollments ile ters yönde bağlantı sağlar; ORM, iki tarafın
#       aynı ilişkiye ait olduğunu bilir ve identity map içinde tutarlı davranır.
#
# Enrollment.course:
#   relationship("Course", back_populates="enrollments")
#   - back_populates:
#       Course.enrollments ile aynı ilişkiyi iki yönden kullanmayı mümkün kılar.
#
# Genel olarak:
# - ForeignKey sütunları (student_id, course_id), ilişkiyi veritabanı tarafında
#   garanti altına alır.
# - relationship + back_populates, aynı ilişkiden hem "ana model" hem de
#   "ilişki modeli" perspektifinden, Python nesneleri ile çalışmayı sağlar.
# - cascade ayarları, parent nesne silindiğinde veya ilişkiden çıkarıldığında,
#   child nesnelerin ne olacağını belirleyen önemli bir tasarım kararıdır.
