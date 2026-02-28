"""
Adım 2 – ORM CLI

Bu modül, Student–Course–Enrollment modelleri üzerinden çalışan
terminal tabanlı bir menü uygular.

Roller:
- Yönetici (admin) → Öğrenci, ders ve kayıtları yönetebilir.
- Öğrenci (student) → Kendi bilgilerini ve ders kayıtlarını görebilir,
  derslere kayıt olabilir / kaydını silebilir.
"""

from contextlib import contextmanager
from typing import Iterator, List, Optional

from sqlalchemy.orm import Session

from database import get_session
from models import Course, Enrollment, Student


@contextmanager
def session_scope() -> Iterator[Session]:
    """
    Kısa ömürlü Session yaşam döngüsünü yöneten context manager.
    """
    session = get_session()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()


# ---------------------------------------------------------------------------
# Yardımcı CRUD fonksiyonları
# ---------------------------------------------------------------------------

def create_student(session: Session, name: str, email: str) -> Student:
    student = Student(name=name, email=email)
    session.add(student)
    session.flush()
    session.refresh(student)
    return student


def list_students(session: Session) -> List[Student]:
    return session.query(Student).order_by(Student.id).all()


def get_student_by_id(session: Session, student_id: int) -> Optional[Student]:
    return session.get(Student, student_id)


def get_student_by_email(session: Session, email: str) -> Optional[Student]:
    return session.query(Student).filter(Student.email == email).one_or_none()


def delete_student(session: Session, student_id: int) -> bool:
    student = session.get(Student, student_id)
    if student is None:
        return False
    session.delete(student)
    return True


def create_course(session: Session, name: str, description: str) -> Course:
    course = Course(name=name, description=description)
    session.add(course)
    session.flush()
    session.refresh(course)
    return course


def list_courses(session: Session) -> List[Course]:
    return session.query(Course).order_by(Course.id).all()


def get_course_by_id(session: Session, course_id: int) -> Optional[Course]:
    return session.get(Course, course_id)


def delete_course(session: Session, course_id: int) -> bool:
    course = session.get(Course, course_id)
    if course is None:
        return False
    session.delete(course)
    return True


def enroll_student(
    session: Session,
    student_id: int,
    course_id: int,
) -> Optional[Enrollment]:
    student = session.get(Student, student_id)
    course = session.get(Course, course_id)
    if student is None or course is None:
        return None

    # Aynı öğrenci–ders çifti için tekrar kayıt olmasını engelle.
    existing = (
        session.query(Enrollment)
        .filter(
            Enrollment.student_id == student_id,
            Enrollment.course_id == course_id,
        )
        .one_or_none()
    )
    if existing:
        return existing

    enrollment = Enrollment(student_id=student_id, course_id=course_id)
    session.add(enrollment)
    session.flush()
    session.refresh(enrollment)
    return enrollment


def list_enrollments_for_student(session: Session, student_id: int) -> List[Enrollment]:
    return (
        session.query(Enrollment)
        .filter(Enrollment.student_id == student_id)
        .order_by(Enrollment.enrollment_date)
        .all()
    )


def list_enrollments_for_course(session: Session, course_id: int) -> List[Enrollment]:
    return (
        session.query(Enrollment)
        .filter(Enrollment.course_id == course_id)
        .order_by(Enrollment.enrollment_date)
        .all()
    )


def delete_enrollment(session: Session, enrollment_id: int) -> bool:
    enrollment = session.get(Enrollment, enrollment_id)
    if enrollment is None:
        return False
    session.delete(enrollment)
    return True


# ---------------------------------------------------------------------------
# Menü fonksiyonları
# ---------------------------------------------------------------------------

def print_main_menu() -> None:
    print("\nAdım 2 – ORM Akademi Sistemi")
    print("-" * 40)
    print("1) Yönetici olarak giriş yap")
    print("2) Öğrenci olarak giriş yap")
    print("0) Çıkış")


def print_admin_menu() -> None:
    print("\n[Admin Menüsü]")
    print("1) Öğrenci oluştur")
    print("2) Öğrencileri listele")
    print("3) Öğrenciyi sil")
    print("4) Ders oluştur")
    print("5) Dersleri listele")
    print("6) Dersi sil")
    print("7) Öğrenciyi derse kaydet")
    print("8) Belirli öğrencinin ders kayıtlarını listele")
    print("9) Belirli dersin öğrencilerini listele")
    print("10) Kayıt (Enrollment) sil")
    print("0) Ana menüye dön")


def print_student_menu(student: Student) -> None:
    print(f"\n[Öğrenci Menüsü] - {student.name} ({student.email})")
    print("1) Kayıtlı olduğum dersleri listele")
    print("2) Tüm dersleri listele")
    print("3) Yeni bir derse kayıt ol")
    print("4) Bir ders kaydımı sil")
    print("0) Ana menüye dön")


def admin_flow() -> None:
    while True:
        print_admin_menu()
        choice = input("Seçiminiz: ").strip()

        if choice == "0":
            break

        elif choice == "1":
            name = input("Öğrenci adı: ").strip()
            email = input("Öğrenci e-posta: ").strip()
            with session_scope() as session:
                try:
                    student = create_student(session, name=name, email=email)
                    print(f"Oluşturulan öğrenci: {student.id} - {student.name} ({student.email})")
                except Exception as exc:
                    print(f"Öğrenci oluşturulurken hata: {exc}")

        elif choice == "2":
            with session_scope() as session:
                students = list_students(session)
                if not students:
                    print("Kayıtlı öğrenci yok.")
                else:
                    print("Öğrenciler:")
                    for s in students:
                        print(f" - {s.id}: {s.name} ({s.email})")

        elif choice == "3":
            try:
                sid = int(input("Silinecek öğrenci ID: ").strip())
            except ValueError:
                print("Geçerli bir ID giriniz.")
                continue
            with session_scope() as session:
                if delete_student(session, sid):
                    print("Öğrenci silindi.")
                else:
                    print("Öğrenci bulunamadı.")

        elif choice == "4":
            name = input("Ders adı: ").strip()
            desc = input("Ders açıklaması: ").strip()
            with session_scope() as session:
                try:
                    course = create_course(session, name=name, description=desc)
                    print(f"Oluşturulan ders: {course.id} - {course.name}")
                except Exception as exc:
                    print(f"Ders oluşturulurken hata: {exc}")

        elif choice == "5":
            with session_scope() as session:
                courses = list_courses(session)
                if not courses:
                    print("Kayıtlı ders yok.")
                else:
                    print("Dersler:")
                    for c in courses:
                        print(f" - {c.id}: {c.name} ({c.description})")

        elif choice == "6":
            try:
                cid = int(input("Silinecek ders ID: ").strip())
            except ValueError:
                print("Geçerli bir ID giriniz.")
                continue
            with session_scope() as session:
                if delete_course(session, cid):
                    print("Ders silindi.")
                else:
                    print("Ders bulunamadı.")

        elif choice == "7":
            try:
                sid = int(input("Öğrenci ID: ").strip())
                cid = int(input("Ders ID: ").strip())
            except ValueError:
                print("Geçerli ID değerleri giriniz.")
                continue
            with session_scope() as session:
                enrollment = enroll_student(session, student_id=sid, course_id=cid)
                if enrollment is None:
                    print("Öğrenci veya ders bulunamadı.")
                else:
                    print("Kayıt oluşturuldu veya zaten mevcuttu.")

        elif choice == "8":
            try:
                sid = int(input("Öğrenci ID: ").strip())
            except ValueError:
                print("Geçerli bir ID giriniz.")
                continue
            with session_scope() as session:
                enrollments = list_enrollments_for_student(session, sid)
                if not enrollments:
                    print("Bu öğrenci için kayıt bulunamadı.")
                else:
                    print("Öğrencinin ders kayıtları:")
                    for e in enrollments:
                        print(f" - Enrollment {e.id}: Course {e.course_id} (tarih: {e.enrollment_date})")

        elif choice == "9":
            try:
                cid = int(input("Ders ID: ").strip())
            except ValueError:
                print("Geçerli bir ID giriniz.")
                continue
            with session_scope() as session:
                enrollments = list_enrollments_for_course(session, cid)
                if not enrollments:
                    print("Bu ders için öğrenci kaydı yok.")
                else:
                    print("Derse kayıtlı öğrenciler:")
                    for e in enrollments:
                        print(f" - Enrollment {e.id}: Student {e.student_id} (tarih: {e.enrollment_date})")

        elif choice == "10":
            try:
                eid = int(input("Silinecek kayıt (Enrollment) ID: ").strip())
            except ValueError:
                print("Geçerli bir ID giriniz.")
                continue
            with session_scope() as session:
                if delete_enrollment(session, eid):
                    print("Kayıt silindi.")
                else:
                    print("Kayıt bulunamadı.")

        else:
            print("Geçersiz seçim.")


def student_flow() -> None:
    email = input("E-posta adresiniz: ").strip()
    if not email:
        print("E-posta zorunludur.")
        return

    with session_scope() as session:
        student = get_student_by_email(session, email=email)
        if student is None:
            create = input("Bu e-posta ile öğrenci bulunamadı. Yeni öğrenci oluşturulsun mu? (e/h): ").strip().lower()
            if create == "e":
                name = input("İsim: ").strip()
                student = create_student(session, name=name, email=email)
                print(f"Oluşturulan öğrenci: {student.id} - {student.name} ({student.email})")
            else:
                print("İşlem iptal edildi.")
                return

    # Öğrenciyi bulduk/oluşturduk; yeni bir session scope içinde menüyü gösterelim.
    while True:
        with session_scope() as session:
            # En güncel hali için her döngüde student nesnesini yeniden çekelim.
            current = get_student_by_email(session, email=email)
            if current is None:
                print("Öğrenci artık mevcut değil. Ana menüye dönülüyor.")
                return

            print_student_menu(current)
            choice = input("Seçiminiz: ").strip()

            if choice == "0":
                break

            elif choice == "1":
                enrollments = list_enrollments_for_student(session, current.id)
                if not enrollments:
                    print("Herhangi bir derse kayıtlı değilsiniz.")
                else:
                    print("Kayıtlı olduğunuz dersler:")
                    for e in enrollments:
                        # e.course relationship'i üzerinden derse erişilebilir.
                        print(f" - {e.course.id}: {e.course.name} (tarih: {e.enrollment_date})")

            elif choice == "2":
                courses = list_courses(session)
                if not courses:
                    print("Henüz tanımlı ders yok.")
                else:
                    print("Tüm dersler:")
                    for c in courses:
                        print(f" - {c.id}: {c.name} ({c.description})")

            elif choice == "3":
                try:
                    cid = int(input("Kayıt olmak istediğiniz ders ID: ").strip())
                except ValueError:
                    print("Geçerli bir ID giriniz.")
                    continue
                enrollment = enroll_student(session, student_id=current.id, course_id=cid)
                if enrollment is None:
                    print("Ders bulunamadı veya başka bir hata oluştu.")
                else:
                    print("Derse kaydınız oluşturuldu veya zaten mevcuttu.")

            elif choice == "4":
                try:
                    eid = int(input("Silmek istediğiniz kayıt (Enrollment) ID: ").strip())
                except ValueError:
                    print("Geçerli bir ID giriniz.")
                    continue
                if delete_enrollment(session, eid):
                    print("Kayıt silindi.")
                else:
                    print("Kayıt bulunamadı.")

            else:
                print("Geçersiz seçim.")


def run_cli() -> None:
    """
    Ana CLI döngüsü:
    - Kullanıcıdan rol seçmesini ister (admin / student).
    - Seçime göre ilgili akışı (`admin_flow` / `student_flow`) çalıştırır.
    """
    while True:
        print_main_menu()
        choice = input("Seçiminiz: ").strip()

        if choice == "0":
            print("Çıkılıyor...")
            break
        elif choice == "1":
            admin_flow()
        elif choice == "2":
            student_flow()
        else:
            print("Geçersiz seçim.")

