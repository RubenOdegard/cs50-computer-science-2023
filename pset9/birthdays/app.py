import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database

        # get data from the form
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # could add validation for month and day here.
        # 1 <= month <= 12
        # 1 <= day <= 31

        # insert data into sql database.
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (:name, :month, :day)", name = name, month = month, day = day)
        return redirect("/")

    # This will run when the request method is GET.
    else:

        # TODO: Display the entries in the database on index.html
        rows = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", rows=rows)


