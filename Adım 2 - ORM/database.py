from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, declarative_base

DATABASE_URL = "sqlite:///database.db"

engine = create_engine(
    url=DATABASE_URL,
    echo=True,
    future=True
)

session_maker = sessionmaker(
    bind=engine,
    autoflush=False,
    autocommit=False,
    future=True
)

Base = declarative_base()


def get_session():
    return session_maker()