import psycopg2

assignments = []
with open('generic_kde_mlsample.csv', 'r') as f:
  for line in f:
    assignments.append(line.strip().split())

update_cmd = 'UPDATE EventMeta SET ml_sample={0} WHERE eid={1}'

host = 'positron02.hep.caltech.edu'
dbname = 'bdtaunu'
conn = psycopg2.connect("host={0} dbname={1}".format(host, dbname))
cur = conn.cursor()
    
for rec in assignments:
  cur.execute(update_cmd.format(rec[1], rec[0]))
conn.commit()

cur.close()
conn.close()
