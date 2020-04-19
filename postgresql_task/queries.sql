-- Query 1
SELECT DISTINCT domain.fqdn
    FROM domain, domain_flag
    WHERE domain.fqdn = domain_flag.fqdn AND domain_flag.flag = 'expired' AND now()::timestamp <@ domain_flag.validity;

-- Query 2
CREATE OR REPLACE FUNCTION check_flag(fqdn_ VARCHAR(255), flag_ FLAG) RETURNS BOOLEAN
AS $BODY$
BEGIN
    RETURN (
        SELECT COUNT(id) FROM domain_flag
            WHERE fqdn = fqdn_ AND flag = flag_ AND NOT now()::timestamp < lower(validity)
    ) > 0;
END $BODY$ LANGUAGE plpgsql;

SELECT DISTINCT fqdn
    FROM domain_flag
    WHERE check_flag(fqdn, 'expired') AND check_flag(fqdn, 'outzone');
