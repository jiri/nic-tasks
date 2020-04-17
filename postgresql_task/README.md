# PostgreSQL Task

The files should be pretty self-explanatory. I'm not sure I understood the task correctly, at first I thought the `domain_flag` table is supposed to be an audit log of changes to the `domain` table.

Both `domain_flag` and `domain` tables share the same `fqdn` field, which would ideally be stored in a separate table (since the `domain` table is really a `registrations` table IMO).

The `fqdn` field is a `VARCHAR(255)` because fully qualified domain names should be at most 255 characters long.