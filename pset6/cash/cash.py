
from cs50 import get_float

while True:
    reminder = round(get_float("Change owed: ")*100)
    if reminder > 0:
        break

coin = 0

quarter = reminder // 25
if quarter > 0:
    coin += quarter
    reminder = reminder % 25

dime = reminder // 10
if dime > 0:
    coin += dime
    reminder = reminder % 10

nickel = reminder // 5
if nickel > 0:
    coin += nickel
    reminder = reminder % 5

penny = reminder // 1
if penny > 0:
    coin += penny

print(coin)
