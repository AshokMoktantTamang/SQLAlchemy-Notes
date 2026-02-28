"""
Adım 7 – Async SQLAlchemy Temel Demo

create_async_engine + AsyncSession ile ekleme ve sorgulama.
Modelleri Base'e kaydetmek için models import edilir.
"""

import asyncio
import uuid

from sqlalchemy import select

from database_async import AsyncSessionLocal, engine, init_db
from models import AsyncUser


async def main() -> None:
    await init_db()
    print("Tablolar oluşturuldu.")

    # Her çalıştırmada benzersiz e-posta (tekrar çalıştırılabilir demo)
    suffix = uuid.uuid4().hex[:8]
    async with AsyncSessionLocal() as session:
        async with session.begin():
            session.add(AsyncUser(name="Async Ali", email=f"async_ali_{suffix}@example.com"))
            session.add(AsyncUser(name="Async Ayşe", email=f"async_ayse_{suffix}@example.com"))
        # begin() bloğu commit yapar

    async with AsyncSessionLocal() as session:
        result = await session.execute(select(AsyncUser).order_by(AsyncUser.id.desc()).limit(5))
        users = result.scalars().all()
        print("Son eklenen kullanıcılar:")
        for u in users:
            print(f"  id={u.id}, name={u.name}, email={u.email}")

    await engine.dispose()
    print("Bitti.")


if __name__ == "__main__":
    asyncio.run(main())
