CREATE EXTENSION IF NOT EXISTS btree_gist;

-- # domain

DROP TABLE IF EXISTS domain CASCADE;

CREATE TABLE domain(
    id SERIAL PRIMARY KEY,
    fqdn VARCHAR(255) NOT NULL,
    registered TSRANGE NOT NULL,

    CONSTRAINT overlap_exclude EXCLUDE USING gist ( fqdn WITH =, registered WITH && ),
    CONSTRAINT lower_bound CHECK ( NOT lower_inf(registered) )
);

-- NOTE: This excludes multiple rows with the unbounded ranges. I couldn't figure out how to make it a constraint.
CREATE UNIQUE INDEX ON domain (fqdn, registered) WHERE upper_inf(registered);

-- # domain_flag

DROP TYPE IF EXISTS FLAG CASCADE;

CREATE TYPE FLAG AS ENUM ( 'expired', 'outzone', 'delete_candidate' );

DROP TABLE IF EXISTS domain_flag CASCADE;

CREATE TABLE domain_flag(
    id BIGSERIAL PRIMARY KEY,
    fqdn VARCHAR(255) NOT NULL,
    flag FLAG NOT NULL,
    validity TSRANGE NOT NULL,

    CONSTRAINT validity_bound CHECK ( NOT lower_inf(validity) ),
    CONSTRAINT bound_overlap EXCLUDE USING gist ( fqdn WITH =, flag WITH =, validity WITH && )
);

-- NOTE: This excludes multiple rows with the unbounded ranges. I couldn't figure out how to make it a constraint.
CREATE UNIQUE INDEX ON domain_flag (fqdn, flag, validity) WHERE upper_inf(validity);

-- NOTE: I'm not sure how to implement 'if upper limit is unbouned it can be set to specific point in time but never
-- to the past' as a constraint. Maybe using triggers?
