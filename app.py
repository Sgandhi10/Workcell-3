from flask import Flask, render_template, request, redirect
from flask_mysqldb import MySQL
import yaml
from datetime import datetime, date

app = Flask(__name__)


# Load Sensitive Data
db = yaml.load(open("db.yaml"))
app.config['MYSQL_HOST'] = db["mysql_host"]
app.config['MYSQL_USER'] = db['mysql_user']
app.config["MYSQL_PASSWORD"] = db["mysql_password"]
app.config["MYSQL_DB"] = db["mysql_db"]


mysql = MySQL(app)


@app.route('/', methods=["GET", "POST"])
def index():
    if request.method == "POST":
        userDetails = request.form
        moisture = float(userDetails["moisture"])
        diameter = float(userDetails["diameter"])
        id = float(userDetails["id"])
        cur = mysql.connection.cursor()
        cur.execute("INSERT INTO data(Id, Time, Moisture, Diameter) VALUES(%s, %s, %s, %s)",
                    (id, datetime.now(), moisture, diameter))
        mysql.connection.commit()
        cur.close()
        return redirect('/users/{}'.format(id))
    return render_template("index.html")


@app.route("/users")
def all_data():
    cur = mysql.connection.cursor()
    resultValue = cur.execute("SELECT * FROM data")
    if resultValue > 0:
        userDetails = cur.fetchall()
        return render_template("users.html", userDetails=userDetails)


@app.route("/users/<nm>")
def users(nm):
    cur = mysql.connection.cursor()
    resultValue = cur.execute("SELECT * FROM data WHERE Id = {}".format(nm))
    if resultValue > 0:
        userDetails = cur.fetchall()
        return render_template("users.html", userDetails=userDetails)


@app.route("/nodemcu/", methods=["POST", "GET"])
def adding():
    print(request.method)
    if request.method == "POST":
        name = request.data.decode("utf-8")
        print(name)
        vals = name.split("/")
        if len(vals) == 3:
            id_val=int(vals[0])
            moisture=float(vals[1])
            diameter=float(vals[2])
        else:
            print("Invalid")
            return "Invalid"
        cur = mysql.connection.cursor()
        cur.execute("INSERT INTO data(Id, Time, Moisture, Diameter) VALUES(%s, %s, %s, %s)",
                    (id_val, datetime.now(), moisture, diameter))
        mysql.connection.commit()
        cur.close()
        return redirect('/users/{}'.format(name))
    return "Not working yet"


if __name__ == '__main__':
    app.run(host="0.0.0.0")