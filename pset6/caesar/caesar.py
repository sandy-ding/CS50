import sys
from cs50 import get_string

if len(sys.argv) != 2:
    print("ERROR")
    exit(1)

k = int(sys.argv[1])
p = get_string("plaintext:")
print("ciphertext:", end="")

for c in p:
    if c.isalpha():
        if c.isupper():
            c = chr(65 + (ord(c) - 65 + k) % 26)
            print(c, end="")
        if c.islower():
            c = chr(97 + (ord(c) - 97 + k) % 26)
            print(c, end="")
    else:
        print(c, end="")
print()