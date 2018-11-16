from cs50 import get_int

while True:
    credit = get_int("Number: ")
    if credit > 0:
        break

digit = []
for i in range(16):
    n = 10 ** (i+1)
    m = 10 ** i
    digit.append(credit % n // m)

sum = 0
multi = []
for i in range(8):
    multi.append(2 * digit[2 * i + 1])
    sum = sum + multi[i] // 10 + multi[i] % 10
    sum = sum + digit[2 *i]

if (sum % 10 == 0):
    if (digit[15] == 0 and digit[14] == 3 and (digit[13] == 4 or digit[13] == 7)):
        print("AMEX")
    elif (digit[15] == 5 and (digit[14] == 1 or digit[14] == 2 or digit[14] == 3 or digit[14] == 4 or digit[14] == 5)):
        print("MASTERCARD")
    elif ((digit[15] == 0 and digit[14] == 0 and digit[13] == 0 and digit[12] == 4) or (digit[15] == 4)):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")