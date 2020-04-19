import os

from flask import Flask, render_template
from sqlalchemy import *
from sqlalchemy.sql import func

import models


def create_app(database_uri=None):
    app = Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = database_uri or os.environ['SQLALCHEMY_DATABASE_URI']
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

    models.db.init_app(app)

    @app.route('/')
    def index():
        domains = models.Domain.query.filter(
            or_(
                models.Domain.deletion == None,
                models.Domain.deletion > func.now()
            )
        ).all()
        return render_template('index.html', domains=domains, FlagType=models.FlagType);

    @app.route('/domain/<int:id>')
    def domain_detail(id):
        domain = models.Domain.query.get(id)
        return render_template('domain.html', domain=domain, FlagType=models.FlagType)

    return app


if __name__ == '__main__':
    main_app = create_app('sqlite:///test.db')
    main_app.run()
