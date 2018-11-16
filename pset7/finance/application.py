import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session,url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, validate_password

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

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM portfolio WHERE id= :id", id=session["user_id"])
    money = 0

    # update price and total in portfolio
    for stock in stocks:
        symbol = stock["symbol"]
        owned = lookup(symbol)
        total = owned["price"] * stock["shares"]
        money += total
        db.execute("UPDATE portfolio SET price=:price,total=:total WHERE id=:id AND symbol=:symbol",
                    price=usd(owned["price"]), total=usd(total), id=session["user_id"], symbol=symbol)

    # send data to index
    update_stocks = db.execute("SELECT * FROM portfolio WHERE id= :id", id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    money = money + cash[0]["cash"]
    return render_template("index.html", stocks=update_stocks, cash=usd(cash[0]["cash"]), money=usd(money))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        shares = int(float(request.form.get("shares")))

        # Ensure symbol was submitted
        if not request.form.get("symbol") or not stock:
            return apology("Invalid symbol", 400)

        # Ensure shares was submitted
        elif not request.form.get("shares") or not shares > 0:
            return apology("Invalid shares", 400)

        price = stock["price"]
        cash = db.execute("SELECT cash FROM users WHERE id= :id", id=session["user_id"])
        cost = price * shares

        # check enough cash
        if not cash or float(cash[0]["cash"]) < price * shares:
            return apology("Money not enough", 400)

        # insert into history
        db.execute("INSERT INTO history(id,symbol,price,shares) \
                    VALUES(:id, :symbol, :price, :shares)",
                    id=session["user_id"], symbol=stock["symbol"],
                    price=usd(stock["price"]), shares=shares)

        # update users[cash]
        db.execute("UPDATE users SET cash = cash-:cost WHERE id= :id",
                    id=session["user_id"], cost=cost)

        # if shares bought before
        owned = db.execute("SELECT * FROM portfolio WHERE id=:id AND symbol=:symbol",
                            id=session["user_id"], symbol=stock["symbol"])

        # if not, insert into portfolio
        if not owned:
            db.execute("INSERT INTO portfolio(id,name,symbol,shares,price,total) \
                        VALUES(:id,:name,:symbol,:shares,:price,:total)",
                        id=session["user_id"], name=stock["name"], symbol=stock["symbol"],
                        shares=shares, price=usd(price), total=usd(shares * price))

        # else, update shares
        else:
            shares = shares + owned[0]["shares"]
            db.execute("UPDATE portfolio SET shares=:shares WHERE id=:id AND symbol=:symbol",
                        id=session["user_id"], shares=shares, symbol=stock["symbol"])

        # return to index
        return redirect(url_for("index"))

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM history WHERE id=:id", id=session["user_id"])
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


@app.route("/cpw", methods=["GET", "POST"])
@login_required
def change_password():
    """change password"""

    if request.method == "GET":
        return render_template("cpw.html")

    # reached via POST, change password
    else:
        # get username
        if not request.form.get("username"):
            return apology("Missing username!", 400)

        # get old password
        elif not request.form.get("oldPassword"):
            return apology("Missing old password!", 400)

        # get new password
        elif not request.form.get("newPassword"):
            return apology("Missing new password!", 400)

        # confirm new password
        elif not request.form.get("confirmation"):
            return apology("Missing confirmation!", 400)

        # validate new password
        elif not validate_password(request.form.get("newPassword")):
            return apology("Password too simple", 400)

        # check new password == confirmation
        elif not request.form.get("newPassword") == request.form.get("confirmation"):
            return apology("Password and confirmation doesn't match", 400)

        # generate password hash
        hash = generate_password_hash(request.form.get("newPassword"))

        # update hash
        db.execute("UPDATE users SET hash=:hash WHERE username=:username",
                    hash=hash, username=request.form.get("username"))

        # login homepage
        user = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        session["user_id"] = user[0]["id"]
        return redirect("/")


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

        if not request.form.get("symbol"):
            return apology("Missing symbol", 400)

        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Invalid symbol", 400)
        else:
            return render_template("quoted.html", stock=stock, price=usd(stock["price"]))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Missing username!", 400)

        elif not request.form.get("password"):
            return apology("Missing password!", 400)

        elif not request.form.get("confirmation"):
            return apology("Missing confirmation!", 400)

        # validate new password
        elif not validate_password(request.form.get("password")):
            return apology("Password too simple", 400)

        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("Password and confirmation doesn't match", 400)

        hash = generate_password_hash(request.form.get("password"))

        result = db.execute("SELECT username FROM users WHERE username = :username",
                            username = request.form.get("username"))
        if result:
            return apology("Username already exists", 400)
        else:
            db.execute("INSERT INTO users(username,hash) VALUES(:username, :hash)",
                        username = request.form.get("username"), hash=hash)

        user = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        session["user_id"] = user[0]["id"]
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        sell_shares = int(float(request.form.get("shares")))

        # Ensure symbol was submitted
        if not request.form.get("symbol") or not stock:
            return apology("Invalid symbol", 400)

        # Ensure shares was submitted
        elif not request.form.get("shares") or not sell_shares > 0:
            return apology("Invalid shares", 400)

        # query shares from portfolio
        portfolio = db.execute("SELECT * FROM portfolio WHERE id=:id AND symbol=:symbol",
                                id=session["user_id"], symbol=request.form.get("symbol"))

        # check if enough shares
        if portfolio[0]["shares"] - sell_shares < 0:
            return apology("Not enough shares", 400)

        # if left no shares, delete from portfolio
        elif portfolio[0]["shares"] - sell_shares == 0:
            db.execute("DELETE FROM portfolio WHERE id=:id AND symbol=:symbol",
                        id=session["user_id"], symbol=request.form.get("symbol"))

        # else update portfolio
        else:
            db.execute("UPDATE portfolio SET shares=shares-:sell_shares WHERE id=:id AND symbol=:symbol",
                        sell_shares=sell_shares, id=session["user_id"], symbol=stock["symbol"])

        # insert into history
        db.execute("INSERT INTO history(id,symbol,price,shares) \
                    VALUES(:id, :symbol, :price, :shares)",
                    id=session["user_id"], symbol=stock["symbol"],
                    price=usd(stock["price"]), shares=-sell_shares)

        # update users
        earn_cash = stock["price"] * sell_shares
        db.execute("UPDATE users SET cash=cash+:earn_cash WHERE id=:id",
                    earn_cash=earn_cash, id=session["user_id"])

        # return to index
        return redirect(url_for("index"))

    else:
        portfolio = db.execute("SELECT * FROM portfolio WHERE id=:id", id=session["user_id"])
        return render_template("sell.html", portfolio=portfolio)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
