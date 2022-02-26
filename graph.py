from sqlalchemy import create_engine
import pandas as pd
import yaml
import matplotlib.pyplot as plt

db = yaml.load(open("db.yaml"))
hostname=db["mysql_host"]
dbname=db["mysql_db"]
uname=db['mysql_user']
pwd=db["mysql_password"]
tablename=db["mysql_table"]

engine = create_engine("mysql+pymysql://{user}:{pw}@{host}/{db}"
                           .format(host=hostname, db=dbname,
                                   user=uname,pw=pwd))
df = pd.read_sql(tablename, engine)
print(df.shape)

plt.plot(df["Time"],df["Moisture"])
plt.gcf().autofmt_xdate()
plt.show()