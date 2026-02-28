"""
Adım 5 – İlk Migration Örneği

Bu dosya, `models_v1.User` tanımına göre oluşturulmuş ilk migration'ı temsil eder.

Alembic komutu (gerçek projede):
    alembic revision --autogenerate -m "initial schema"
"""

from alembic import op
import sqlalchemy as sa


# Alembic tarafından kullanılan metadata
revision = "1234_initial_schema"
down_revision = None
branch_labels = None
depends_on = None


def upgrade() -> None:
    """
    Şemayı bir üst versiyona taşır.

    Burada:
    - `users` tablosu oluşturulur.
    """
    op.create_table(
        "users",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("name", sa.String(length=100), nullable=False),
    )


def downgrade() -> None:
    """
    Şemayı bir önceki versiyona geri alır.

    Burada:
    - `users` tablosu düşürülür.
    """
    op.drop_table("users")

