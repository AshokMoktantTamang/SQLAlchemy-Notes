"""
Adım 4 – Polymorphic Mapping Demo

Bu script, Animal / Dog modelleri ile:
- Tek tabloda (adv_animals) farklı tiplerin (animal, dog)
nasıl saklandığını
- ORM tarafında nasıl farklı sınıf örnekleri döndüğünü
gösterir.
"""

from database import Session, init_db
from models import Animal, Dog


def seed_data() -> None:
    session = Session()
    try:
        session.add_all(
            [
                Animal(type="animal", name="Generic"),
                Dog(type="dog", name="Karabaş"),
            ]
        )
        session.commit()
    finally:
        session.close()


def demo_polymorphic() -> None:
    print("\n--- Polymorphic mapping demo ---")
    session = Session()
    try:
        animals = session.query(Animal).all()
        for a in animals:
            print(f"DB row → Python nesnesi: type(a)={type(a)}, a.type={a.type}, a.name={a.name}")
    finally:
        session.close()


if __name__ == "__main__":
    init_db()
    seed_data()
    demo_polymorphic()

