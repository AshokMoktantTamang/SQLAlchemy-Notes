"""
Adım 3 – Many-to-Many Demo

Bu script:
- Basit association table (Student / Course)
- Association object pattern (Enrollment)
üzerinden kayıt ekleme ve ilişki navigasyonunu gösterir.
"""

from database import Session, init_db
from models_many_to_many_basic import Course, Student
from models_many_to_many_enrollment import Course2, Enrollment, Student2


def seed_basic_association() -> None:
    """Basit association table Many-to-Many örneği için demo verileri üretir."""
    session = Session()
    try:
        s1 = Student(name="Ali")
        s2 = Student(name="Ayşe")

        c1 = Course(title="Python")
        c2 = Course(title="SQL")

        s1.courses.extend([c1, c2])
        s2.courses.append(c1)

        session.add_all([s1, s2])
        session.commit()
    finally:
        session.close()


def demo_basic_association() -> None:
    """Student–Course ilişkisini her iki yönden de ekrana yazar."""
    print("\n--- Basic Many-to-Many (association table) ---")
    session = Session()
    try:
        # Öğrenciler ve aldıkları dersler
        students = session.query(Student).all()
        for s in students:
            print(f"{s.name} aldığı dersler: {[c.title for c in s.courses]}")

        # Dersler ve bu dersi alan öğrenciler
        courses = session.query(Course).all()
        for c in courses:
            print(f"{c.title} dersini alanlar: {[s.name for s in c.students]}")
    finally:
        session.close()


def seed_association_object() -> None:
    """Association object (Enrollment) için örnek bir kayıt ekler."""
    session = Session()
    try:
        s = Student2(name="Mehmet")
        c = Course2(title="Veri Tabanları")

        e = Enrollment(grade=95)
        e.student = s
        e.course = c

        session.add(e)
        session.commit()
    finally:
        session.close()


def demo_association_object() -> None:
    """Enrollment üzerinden öğrenci–ders–not bilgisini gösterir."""
    print("\n--- Association Object Pattern (Enrollment) ---")
    session = Session()
    try:
        enrollments = session.query(Enrollment).all()
        for e in enrollments:
            # Burada relationship sayesinde direkt e.student ve e.course üzerinden nesnelere erişiyoruz.
            print(
                f"{e.student.name} → {e.course.title} (not: {e.grade}, tarih: {e.enrolled_at})"
            )
    finally:
        session.close()


if __name__ == "__main__":
    init_db()
    seed_basic_association()
    demo_basic_association()
    seed_association_object()
    demo_association_object()

