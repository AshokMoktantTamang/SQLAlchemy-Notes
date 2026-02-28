"""
Adım 7 – Async Session Context Manager Demo

Session'ı async with ile açıp commit/rollback/close yönetimi.
"""

import asyncio

from sqlalchemy import select

from database_async import AsyncSessionLocal, init_db
from models import AsyncUser


"""
Adım 7 – Async Session Context Manager Demo

Session'ı async with ile açıp commit/rollback/close yönetimi.
"""

import asyncio
import uuid

from sqlalchemy import select

from database_async import AsyncSessionLocal, init_db
from models import AsyncUser


async def successful_request() -> str:
    """Başarılı istek: ekleme + commit. Oluşturulan email'i döndürür."""
    email = f"ctx-{uuid.uuid4().hex[:8]}@example.com"
    print("İstek 1: Session açıldı.")
    async with AsyncSessionLocal() as session:
        session.add(AsyncUser(name="Context Kullanıcı", email=email))
        await session.commit()
    print("İstek 1: Commit ve close.\n")
    return email


async def query_after_commit(email: str) -> None:
    """Commit sonrası expire_on_commit=False sayesinde nesneye erişim."""
    async with AsyncSessionLocal() as session:
        result = await session.execute(select(AsyncUser).where(AsyncUser.email == email))
        user = result.scalar_one_or_none()
        if user:
            print(f"Bulunan: {user.name} ({user.email})")
        await session.commit()
    print("İstek 2: Bitti.\n")


async def main() -> None:
    await init_db()

    email = await successful_request()
    await query_after_commit(email)

    from database_async import engine
    await engine.dispose()
    print("Tüm demolar tamamlandı.")


if __name__ == "__main__":
    asyncio.run(main())
