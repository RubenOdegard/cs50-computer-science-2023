import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get user stocks and shares from database
    # grouping by symbol
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=session["user_id"],
    )

    # get user cash balance from database
    cash = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
    )[0]["cash"]

    # initialize variables to hold total value and grand total.
    t_value = cash
    g_value = cash

    # loop over stocks and add price and total value.
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["value"] = quote["price"] * stock["total_shares"]

        t_value += stock["value"]
        g_value += stock["value"]

    return render_template(
        "index.html", stocks=stocks, cash=cash, t_value=t_value, g_value=g_value
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # POST request
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # return early if symbol is blank
        if not symbol:
            return apology("No symbol provided. Please provide a symbol.", 400)
        # return early if shares is empty or not a positive integer
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Invalid shares. Shares must be a positive integer.", 400)

        # return early if symbol is inputted but not found
        quote = lookup(symbol)
        if quote is None:
            return apology(
                "Symbol not found. Please ensure you input a correct symbol.", 400
            )

        # debug line to see contents of quote
        # print(quote) ({'name': 'AMD', 'price': 123.46, 'symbol': 'AMD'})

        price = quote["price"]

        # find total cost of shares
        share_cost = int(shares) * price

        # get cash amount from the currect user (from the session object)
        cash = db.execute(
            "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
        )[0]["cash"]

        # return early if user does not have enough funds
        if cash < share_cost:
            return apology("You do not have enough funds to make this purchase.", 400)

        # At this point, we have the following
        # - valid symbol
        # - valid share amount
        # - valid funds to make the purchase

        # purchase can be made, update sql database
        try:
            db.execute(
                "UPDATE users SET cash = cash - :share_cost WHERE id = :user_id",
                share_cost=share_cost,
                user_id=session["user_id"],
            )
        except Exception:
            return apology("Something went wrong, try again.", 400)

        # one of the tasks is to store the transactions in the sql database
        # we can create a transactions table to store all transactions with stock, price, userid, timestamp.
        # transactions: id (autogen), user_id, symbol, shares, price, timestamp (autogen)

        # store purchase in transactions table
        db.execute(
            "INSERT INTO transactions (user_id, type, symbol, shares, price) VALUES (:user_id, :type, :symbol, :shares, :price)",
            user_id=session["user_id"],
            type="Buy",
            symbol=symbol,
            shares=shares,
            price=price,
        )

        # success
        return redirect("/")

    # GET request
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # get user transactions from database
    try:
        transactions = db.execute(
            "SELECT * FROM transactions WHERE user_id = :user_id ORDER BY timestamp DESC",
            user_id=session["user_id"],
        )
    except Exception:
        return apology("Something went wrong, try again.", 400)

    # success
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # POST request
    if request.method == "POST":
        # get symbol from form and loopup symbol with the function from helpers.py
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # debug line to see contents of quote
        # print(quote)

        # return early if there is no quote for the user input
        if not quote:
            return apology("Invalid symbol, please try again.", 400)
        # if quote is found, render quote.html with the quote data
        return render_template("quote.html", quote=quote)

    # GET request
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # clear session, only a non-user can register
    session.clear()

    # POST request
    if request.method == "POST":
        # return early if no username
        if not request.form.get("username"):
            return apology("You must provide a username.", 400)

        # return early if no password
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("You must provide a password.", 400)

        # return early if password and confirmation field does not match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match.", 400)

        #### PERSONAL TOUCH ####
        # Check if the password is at least 8 characters long
        if len(request.form.get("password")) < 8:
            return apology("Password must be at least 8 characters long.", 400)

        #### PERSONAL TOUCH ####
        # Check if the password contains at least one letter, one number, and one symbol
        # REGEX, check for one character, one number and one symbol.
        if not (
            re.search("[a-zA-Z]", request.form.get("password"))
            and re.search("[0-9]", request.form.get("password"))
            and re.search('[!@#$%^&*(),.?":{}|<>]', request.form.get("password"))
        ):
            return apology(
                "Password must include at least one letter, one number, and one symbol.",
                400,
            )

        # At this point, we have correct username and password from the input fields
        # we can query the database to check if username already exists
        userCheck = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        if len(userCheck) != 0:
            return apology("Username already exists.", 400)

        # if user doest not exist, we can try to create the new user.
        # throw error if something goes wrong.
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                request.form.get("username"),
                generate_password_hash(request.form.get("password")),
            )
        except Exception:
            return apology("Something went wrong, try again.", 400)

        # query the created user, and store in session.
        # after the users is registered, the user will stay logged in and authenticated.

        user = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        session["user_id"] = user[0]["id"]

        # success
        return redirect("/")

    # GET request
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # get user stocks on load
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares >0",
        user_id=session["user_id"],
    )

    # POST request
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # return early if symbol is blank
        if not symbol:
            return apology("No symbol provided. Please provide a symbol.", 400)
        # return early if shares is empty or not a positive integer
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Invalid shares. Shares must be a positive integer.", 400)
        else:
            shares = int(shares)

        # iterate over stocks
        for stock in stocks:
            # if the stock matches user input for sale
            if stock["symbol"] == symbol:
                # return early if we are trying to sell more shares than we have
                if stock["total_shares"] < shares:
                    return apology("Not enough shares to sell.", 400)
                else:
                    # get quote for the share the user wants to sell
                    quote = lookup(symbol)
                    # handle if quote is not found from the user input
                    if quote is None:
                        return apology("Invalid symbol or not found.", 400)

                    # if quote is found, we can continue
                    price = quote["price"]
                    # multiply shares (to be sold) with the price of the share (from lookup(symbol))
                    total_sale = shares * price

                    # update user in database
                    try:
                        db.execute(
                            "UPDATE users SET cash = cash + :total_sale WHERE id = :user_id",
                            user_id=session["user_id"],
                            total_sale=total_sale,
                        )
                    except Exception:
                        return apology("Something went wrong, try again.", 400)

                    # update users activity in transactions
                    db.execute(
                        "INSERT INTO transactions (user_id, type, symbol, shares, price) VALUES (:user_id, :type, :symbol, :shares, :price)",
                        user_id=session["user_id"],
                        type="Sale",
                        symbol=symbol,
                        shares=-shares,
                        price=price,
                    )

                    # success
                    return redirect("/")

        # This line should be at the same level as the 'for' loop, not inside it
        return apology("Symbol not found.", 400)

    # GET request
    else:
        return render_template("sell.html", stocks=stocks)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    # POST request
    if request.method == "POST":
        # get amount from the form
        amount = request.form.get("amount")

        # check if valid number
        if not amount or not amount.isdigit() or int(amount) <= 0:
            return apology("Invalid amount. Please provide a positive integer.", 400)

        # update user cash in database
        try:
            db.execute(
                "UPDATE users SET cash = cash + :amount WHERE id = :user_id",
                amount=amount,
                user_id=session["user_id"],
            )
        except Exception:
            return apology("Something went wrong, try again.", 400)

        # update users activity in transactions
        try:
            db.execute(
                "INSERT INTO transactions (user_id, type, symbol, shares, price) VALUES (:user_id, :type, :symbol, :shares, :price)",
                user_id=session["user_id"],
                type="Cash",
                symbol="null",
                shares="null",
                price=amount,
            )
        except Exception:
            return apology("Something went wrong, try again.", 400)

        # success
        return redirect("/")

    # GET request
    else:
        return render_template("add_cash.html")
