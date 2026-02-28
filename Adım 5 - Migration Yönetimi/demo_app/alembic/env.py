"""
Adım 5 – Alembic env.py

Bu dosya, Alembic'in migration üretirken ve çalıştırırken kullandığı ortam
tanımlarını barındırır. Kritik nokta: SQLAlchemy Base.metadata'yı Alembic'e tanıtmak.
demo_app dizininden çalıştırıldığında: from database import Base
"""

import os
import sys

from logging.config import fileConfig

from sqlalchemy import engine_from_config, pool

from alembic import context

# alembic/env.py'den demo_app kökünü path'e ekle
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

config = context.config

if config.config_file_name is not None:
    fileConfig(config.config_file_name)

# demo_app dizininden çalıştırıldığında database modülü bulunur
from database import Base  # noqa: E402

target_metadata = Base.metadata


def run_migrations_offline() -> None:
    """Offline modda migration (sadece SQL üretir)."""
    url = config.get_main_option("sqlalchemy.url")
    context.configure(
        url=url,
        target_metadata=target_metadata,
        literal_binds=True,
        dialect_opts={"paramstyle": "named"},
    )

    with context.begin_transaction():
        context.run_migrations()


def run_migrations_online() -> None:
    """Gerçek veritabanına bağlı migration."""
    connectable = engine_from_config(
        config.get_section(config.config_ini_section),
        prefix="sqlalchemy.",
        poolclass=pool.NullPool,
    )

    with connectable.connect() as connection:
        context.configure(connection=connection, target_metadata=target_metadata)

        with context.begin_transaction():
            context.run_migrations()


if context.is_offline_mode():
    run_migrations_offline()
else:
    run_migrations_online()
