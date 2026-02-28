"""
Adım 5 – İkinci Migration Örneği

Bu dosya, `models_v2.User` ile eklenen `email` kolonunu temsil eder.

Alembic komutu (gerçek projede):
    alembic revision --autogenerate -m "add email to user"
"""

from alembic import op
import sqlalchemy as sa


revision = "5678_add_email_to_user"
down_revision = "1234_initial_schema"
branch_labels = None
depends_on = None


def upgrade() -> None:
    """
    `users` tablosuna yeni bir `email` kolonu ekler.

    Not:
    - İlk aşamada `nullable=True` bırakmak, mevcut kayıtlarda hata
      oluşmasını engeller.
    - Sonraki bir migration'da (gerekirse) backfill + NOT NULL constraint
      eklenebilir.
    """
    op.add_column(
        "users",
        sa.Column("email", sa.String(length=200), nullable=True),
    )
    op.create_index(
        "ix_users_email",
        "users",
        ["email"],
        unique=True,
    )


def downgrade() -> None:
    """
    Eklenen email kolonunu ve index'ini geri alır.
    """
    op.drop_index("ix_users_email", table_name="users")
    op.drop_column("users", "email")

