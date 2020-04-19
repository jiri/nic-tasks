import os
import tempfile

import pytest

import app as nic_task


@pytest.fixture
def client():
    app = nic_task.create_app('sqlite:///test.db')
    app.config['TESTING'] = True

    with app.test_client() as client:
        with app.app_context():
            nic_task.models.db.create_all()
        yield client


def test_index_page(client):
    rv = client.get('/')

    assert b'seznam.cz' in rv.data
    assert b'google.com' in rv.data
    assert b'blockbuster.com' not in rv.data


def test_detail_page(client):
    rv = client.get('/domain/1')

    assert b'2020-01-01 12:00:00' in rv.data
    assert b'2020-01-31 12:00:00' in rv.data
    assert b'seznam.cz' in rv.data
    assert b'expired' in rv.data