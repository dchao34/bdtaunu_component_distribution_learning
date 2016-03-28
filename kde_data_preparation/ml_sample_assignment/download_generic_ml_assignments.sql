CREATE TEMPORARY VIEW F AS
SELECT 
    eid,
    event_weight, 
    ml_sample
FROM (McEvent INNER JOIN EventMetaData USING (eid))
WHERE 
    data_source>1 AND 
    ml_sample=-1
;

\copy (SELECT * FROM F) TO 'generic_ml_assignments.csv' WITH CSV HEADER;
