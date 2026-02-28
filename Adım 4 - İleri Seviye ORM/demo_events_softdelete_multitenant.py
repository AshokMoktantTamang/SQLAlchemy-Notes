"""
Adım 4 – Event, Soft Delete ve Multi-Tenant Demo

Bu script:
- Event sistemi ile before_insert örneği (isim formatlama)
- Soft delete alanını kullanma
- TenantUser üzerinde tenant_id ile veri ayırma
örneklerini gösterir.
"""

from sqlalchemy import event, select

from database import Session, init_db
from models import SoftUser, TenantUser


@event.listens_for(SoftUser, "before_insert")
def before_insert_soft_user(mapper, connection, target: SoftUser) -> None:
    """
    SoftUser eklenmeden önce isim alanını normalize eden örnek event.

    Bu örnekte:
    - Baştaki/sondaki boşluklar kırpılır.
    - İsim büyük harfe çevrilir.
    """
    target.name = target.name.strip().upper()


def seed_soft_users() -> None:
    session = Session()
    try:
        session.add_all(
            [
                SoftUser(name=" ali "),
                SoftUser(name=" ayşe "),
            ]
        )
        session.commit()
    finally:
        session.close()


def demo_soft_delete() -> None:
    print("\n--- Soft delete demo ---")
    session = Session()
    try:
        users = session.execute(select(SoftUser)).scalars().all()
        print("Tüm kullanıcılar (silinmemiş + silinmiş):")
        for u in users:
            print(f"  id={u.id}, name={u.name}, deleted={u.deleted}")

        # Bir kullanıcıyı "sil" (soft delete)
        user = users[0]
        user.deleted = True
        session.commit()

        # Silinmemiş kullanıcıları filtreleyelim
        active_users = (
            session.query(SoftUser)
            .filter(SoftUser.deleted.is_(False))
            .all()
        )
        print("Silinmemiş kullanıcılar:")
        for u in active_users:
            print(f"  id={u.id}, name={u.name}, deleted={u.deleted}")
    finally:
        session.close()


def seed_tenant_users() -> None:
    session = Session()
    try:
        session.add_all(
            [
                TenantUser(tenant_id=1, name="Ali - Tenant 1"),
                TenantUser(tenant_id=1, name="Ayşe - Tenant 1"),
                TenantUser(tenant_id=2, name="Mehmet - Tenant 2"),
            ]
        )
        session.commit()
    finally:
        session.close()


def demo_multi_tenant() -> None:
    print("\n--- Multi-tenant demo ---")
    session = Session()
    try:
        # Tenant 1 için kullanıcılar
        t1_users = (
            session.query(TenantUser)
            .filter(TenantUser.tenant_id == 1)
            .all()
        )
        print("Tenant 1 kullanıcıları:")
        for u in t1_users:
            print(f"  {u.id} - {u.name} (tenant_id={u.tenant_id})")

        # Tenant 2 için kullanıcılar
        t2_users = (
            session.query(TenantUser)
            .filter(TenantUser.tenant_id == 2)
            .all()
        )
        print("Tenant 2 kullanıcıları:")
        for u in t2_users:
            print(f"  {u.id} - {u.name} (tenant_id={u.tenant_id})")
    finally:
        session.close()


if __name__ == "__main__":
    init_db()
    seed_soft_users()
    demo_soft_delete()
    seed_tenant_users()
    demo_multi_tenant()

