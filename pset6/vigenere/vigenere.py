import sys
from cs50 import get_string

if len(sys.argv) != 2:
    print("ERROR")
    exit(1)

k = sys.argv[1]
m = len(k)
for c in k:
    if not(c.isalpha()):
        print("ERROR")
        exit(1)

p = get_string("plaintext:")
print("ciphertext:", end="")
j = 0

for c in p:
    if c.isalpha():
        if c.isupper():
            if k[j % m].isupper():
                c = chr(65 + (ord(c) - 65 + ord(k[j % m]) - 65) % 26)
                print(c, end="")
            if k[j % m].islower():
                c = chr(65 + (ord(c) - 65 + ord(k[j % m]) - 97) % 26)
                print(c, end="")
        elif c.islower():
            if k[j % m].isupper():
                c = chr(97 + (ord(c) - 97 + ord(k[j % m]) - 65) % 26)
                print(c, end="")
            if k[j % m].islower():
                c = chr(97 + (ord(c) - 97 + ord(k[j % m]) - 97) % 26)
                print(c, end="")
        j += 1
    else:
        print(c, end="")
print()