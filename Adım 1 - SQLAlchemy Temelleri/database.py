"""
Adım 1 – SQLAlchemy Temelleri

Bu modül, proje genelinde kullanılacak:

- Engine (bağlantı fabrikası),
- Session factory (ORM oturumları için),
- Base (tüm modellerin miras alacağı temel sınıf)

bileşenlerini merkezi bir noktada toplar.

Diğer dosyalar:
- `models.py` → `Base`'i kullanarak tablo/model tanımlar.
- `main.py`  → `engine` ve `SessionLocal` ile tablo oluşturur ve veritabanı işlemlerini yürütür.
"""

from sqlalchemy import create_engine
from sqlalchemy.orm import declarative_base, sessionmaker

# Uygulamanın bağlantı dizesi.
# Eğitim amaçlı olarak SQLite dosya tabanlı veritabanı kullanılmaktadır.
# Örnek diğer bağlantı şekilleri:
# - PostgreSQL: "postgresql+psycopg2://user:pass@localhost:5432/dbname"
# - MySQL:      "mysql+mysqlclient://user:pass@localhost:3306/dbname"
DATABASE_URL = "sqlite:///database.db"

# Engine, veritabanı ile konuşan ve bağlantı havuzunu yöneten çekirdek bileşendir.
# Buradaki parametreler:
# - url:     Hangi veritabanına, hangi sürücü ile bağlanılacağını belirtir.
# - echo:    True ise, üretilen tüm SQL sorgularını stdout'a/loga yazar (öğrenme ve debug için faydalı).
# - future:  SQLAlchemy 2.x tarzı API ve davranışları aktifleştirir (yeni sürümle uyumlu kullanım).
engine = create_engine(
    url=DATABASE_URL,
    echo=True,
    future=True,
)

# SessionLocal, her kullanımda yeni bir Session üretmek için kullanılacak factory'dir.
# Buradaki parametreler:
# - bind:        Bu session'ların hangi engine üzerinden çalışacağını belirtir.
# - autoflush:   True ise, belirli noktalarda (ör. query) otomatik flush yapılır; burada manuel kontrol için False.
# - autocommit:  False iken, değişikliklerin veri tabanına yansıması için açıkça commit çağrılması gerekir.
# - future:      Engine'de olduğu gibi, 2.x tarzı davranışları aktifleştirir.
SessionLocal = sessionmaker(
    bind=engine,
    autoflush=False,
    autocommit=False,
    future=True,
)

# Base, tüm ORM modellerinin miras alacağı temel sınıftır.
# Base.metadata altında tablo şemaları toplanır ve `create_all` gibi işlemler bu metadata üzerinden yürütülür.
Base = declarative_base()


def get_session():
    """
    Yeni bir Session örneği üretir.

    Eğitim senaryolarında:
    - `with get_session() as session:` veya
    - try/finally içinde `session.close()` ile birlikte
    kullanılabilir.
    """
    return SessionLocal()


# ============================================================
# Mimari Diyagram (Özet)
#
#   Uygulama kodu (ör. main.py)
#                │
#                ▼
#        get_session() / SessionLocal
#                │
#                ▼
#             Session
#        (ORM state & transaction)
#                │
#        Modeller (Base'den türeyen
#          User vb. sınıflar)
#                │
#                ▼
#              Engine
#        (Connection pool + Dialect)
#                │
#                ▼
#           DBAPI Sürücüsü
#      (sqlite3, psycopg2, mysqlclient ...)
#                │
#                ▼
#           Veritabanı Sunucusu
#       (SQLite dosyası, PostgreSQL, vb.)
#
# Bu dosya:
# - Engine'i tanımlar (veritabanı bağlantısı).
# - SessionLocal'i tanımlar (ORM oturum fabrikası).
# - Base'i tanımlar (tüm modellerin ortak temeli).
# Diğer modüller bu bileşenleri içe aktararak kendi görevlerini yerine getirir.