INSERT INTO domain VALUES (DEFAULT, 'seznam.cz', '[2019-01-01 12:00, 2019-01-31 12:00]');
INSERT INTO domain VALUES (DEFAULT, 'seznam.cz', '[2019-02-01 12:00,]');

INSERT INTO domain VALUES (DEFAULT, 'google.com', '[2019-01-01 12:00,2019-01-31 12:00]');
INSERT INTO domain VALUES (DEFAULT, 'google.com', '[2019-02-01 12:00,]');

INSERT INTO domain_flag VALUES (DEFAULT, 'seznam.cz', 'expired', '[2019-01-30 12:00, 2019-01-31 12:00]');
INSERT INTO domain_flag VALUES (DEFAULT, 'seznam.cz', 'outzone', '[2019-01-15 12:00, 2019-01-15 12:45]');

INSERT INTO domain_flag VALUES (DEFAULT, 'google.com', 'expired', '[2019-02-28 12:00,]');
