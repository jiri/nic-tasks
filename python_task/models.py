import enum

from sqlalchemy import *
from sqlalchemy.orm import relationship
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.sql import func

db = SQLAlchemy()


class FlagType(enum.Enum):
    expired = 1
    outzone = 2
    deletion_candidate = 3


class Domain(db.Model):
    __tablename__ = 'domains'

    id = Column(Integer, primary_key=True)
    fqdn = Column(String(255), nullable=False)
    creation = Column(DateTime, nullable=False)
    expiration = Column(DateTime, nullable=False)
    deletion = Column(DateTime)

    def active_flags(self):
        flags = DomainFlag.query.filter(
            and_(
                DomainFlag.domain_id == self.id,
                DomainFlag.valid_from <= func.now(),
                DomainFlag.valid_to >= func.now()
            )
        ).all()

        return [flag.type for flag in flags]


class DomainFlag(db.Model):
    __tablename__ = 'domain_flags'

    id = Column(Integer, primary_key=True)
    domain_id = Column(Integer, ForeignKey('domains.id'))
    domain = relationship("Domain")
    type = Column(Enum(FlagType), nullable=False)
    valid_from = Column(DateTime, nullable=False)
    valid_to = Column(DateTime, nullable=False)
