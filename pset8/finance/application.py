import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd
app = Flask(__name__)
# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db", connect_args={'check_same_thread': False})

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query database for holding stock
    stocks = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = :user_id",
                        user_id=session["user_id"])
    # User wallet
    total = cash = name = db.execute("SELECT cash, username FROM users WHERE id = :id",
                        id=session["user_id"])

    # List of Dictionary holding company, symbol, price, shares and total (worth of shares)
    stockInfo = []
    total = cash[0]["cash"]
    for i in range(len(stocks)):

        # Updated stock name, price, symbol
        stockInfo.append(lookup(stocks[i]["symbol"]))

        # Store user's shares
        stockInfo[i]["shares"] = stocks[i]["shares"]

        # Store total shares value as USD
        stockInfo[i]["total"] = usd(stockInfo[i]["shares"] * stockInfo[i]["price"])

        # Store sum of total share values
        total += stockInfo[i]["shares"] * stockInfo[i]["price"]

        # Price in USD
        stockInfo[i]["price"] = usd(stockInfo[i]["price"])

    return render_template("index.html", stockInfo=stockInfo, cash=usd(cash[0]["cash"]), total=usd(total), username=name[0]["username"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol and shares has been typed
        if not request.form.get("symbol"):
            return apology("MISSING SYMBOL")
        elif not request.form.get("shares"):
            return apology("MISSING SHARES")

        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        # Ensure symbol exist
        if not stock:
            return apology("INVALID SYMBOL")

        # Variables
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        user_id = session["user_id"]



        stock = lookup(symbol)
        company = stock["name"]
        symbol = stock["symbol"]
        price = float(stock["price"])

        # Query database for username
        cash = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=user_id)[0]["cash"]

        total = price * shares
        # Ensure user has enough cash
        if cash < total:
            return  apology("CAN'T EFFORT")

        sharesHolding = db.execute("SELECT shares FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                    user_id=user_id, symbol=symbol)

        cashRemain = cash - total

        # Ensure user's hold shares and update stocks
        if len(sharesHolding) != 0:

            newStock = sharesHolding[0]["shares"] + shares

            # Update user stock
            db.execute("UPDATE stocks SET shares = :newStock WHERE user_id = :user_id AND symbol = :symbol",
                    newStock=newStock, user_id=user_id, symbol=symbol)

            # Update user's wallet
            db.execute("UPDATE users SET cash = :cashRemain WHERE id = :id",
                    cashRemain=cashRemain, id=user_id)

        # If not holding shares Insert stock
        else:
            db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES (:user_id, :symbol, :shares)",
                    user_id=user_id, symbol=symbol, shares=shares)

            db.execute("UPDATE users SET cash = :cashRemain WHERE id = :id",
                    cashRemain=cashRemain, id=user_id)

        # Recording transanctions
        db.execute("INSERT INTO history (user_id, company, symbol, shares, price, total) VALUES (:user_id, :company, :symbol, :shares, :price, :total)", user_id=user_id, company=company, symbol=symbol, shares=shares, price=price, total=total)

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT symbol, shares, price, timestamp FROM history WHERE user_id = :user_id ORDER BY id DESC", user_id=session["user_id"])

    return render_template("history.html", history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    if request.method == "POST":

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("MISSING SYMBOL")
        elif not lookup(symbol):
            return apology("INVALID SYMBOL")

        stockQuote = lookup(symbol)
        name = stockQuote["name"]
        symbol = stockQuote["symbol"]
        price = stockQuote["price"]

        return render_template("quoted.html", name=name, symbol=symbol, price=usd(price))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

   # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password and confirmation are the same
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password doesn't match", 403)

        # Query database for username
        username = db.execute("SELECT username FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username does not exists
        if username:
            return apology("THE USER EXIST", 403)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Ensure user select symbol and typed number of shares
        if not symbol:
            return apology("MISSING SYMBOL")
        elif not shares:
            return apology("MISSING SHARES")

        # Remember update Stocks
        stock = lookup(symbol)
        company = stock["name"]
        symbol = stock["symbol"]
        price  = stock["price"]

        user_id = session["user_id"]
        # User's shares
        ownedShares = db.execute("SELECT shares FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                    user_id=user_id, symbol=symbol)[0]["shares"]

        # Ensure for enough shares
        if shares > ownedShares:
            return apology("TOO MANY SHARES")

        # Query database for cash
        cash = db.execute("SELECT cash FROM users WHERE id = :id",
                    id=user_id)[0]["cash"]

        # Remember update cost of shares
        amount = shares * price

        # Update user's shares
        db.execute("UPDATE stocks SET shares = :shares WHERE user_id = :user_id AND symbol = :symbol",
                    shares=ownedShares-shares, user_id=user_id, symbol=symbol)

        # Update wallet
        db.execute("UPDATE users SET cash = :cash WHERE id = :id",
                    cash=cash+amount, id=user_id)

        # Record into history
        db.execute("INSERT INTO history (user_id, company, symbol, shares, price, total) VALUES (:user_id, :company, :symbol, :shares, :price, :total)", user_id=user_id, company=company, symbol=symbol, shares=-shares, price=usd(price), total=usd(amount))

        # Redirect user to Homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        stocks = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = :user_id",
                    user_id=session["user_id"])

        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
