import crypt
import sys
from cs50 import get_string

if len(sys.argv) != 2:
    print("ERROR")
    exit(1)

hashed = sys.argv[1]
salt = hashed[0] + hashed[1]

#one-char password
for i in range(65, 123, 1):
    #skip middle
    if i > 90 and i < 97:
        continue
    #create list key
    key = [chr(i)]
    #join list into string
    key0 = ''.join(key)
    #check for hashed
    if crypt.crypt(key0, salt) == hashed:
        print(key0)
        exit()

#two-char password
for i in range(65, 123, 1):
    if i > 90 and i < 97:
        continue
    for j in range(65, 123, 1):
        if j > 90 and j < 97:
            continue
        key = [chr(i), chr(j)]
        key1 = ''.join(key)
        if crypt.crypt(key1, salt) == hashed:
            print(key1)
            exit()

#three-char password
for i in range(65, 123, 1):
    if i > 90 and i < 97:
        continue
    for j in range(65, 123, 1):
        if j > 90 and j < 97:
            continue
        for k in range(65, 123, 1):
            if k > 90 and k < 97:
                continue
            key = [chr(i), chr(j), chr(k)]
            key2 = ''.join(key)
            if crypt.crypt(key2, salt) == hashed:
                print(key2)
                exit()

#four-char password
for i in range(65, 123, 1):
    if i > 90 and i < 97:
        continue
    for j in range(65, 123, 1):
        if j > 90 and j < 97:
            continue
        for k in range(65, 123, 1):
            if k > 90 and k < 97:
                continue
            for h in range(65, 123, 1):
                if h > 90 and h < 97:
                    continue
                key = [chr(i), chr(j), chr(k), chr(h)]
                key3 = ''.join(key)
                if crypt.crypt(key3, salt) == hashed:
                    print(key3)
                    exit()

#five-char password
for i in range(65, 123, 1):
    if i > 90 and i < 97:
        continue
    for j in range(65, 123, 1):
        if j > 90 and j < 97:
            continue
        for k in range(65, 123, 1):
            if k > 90 and k < 97:
                continue
            for h in range(65, 123, 1):
                if h > 90 and h < 97:
                    continue
                for l in range(65, 123, 1):
                    if l > 90 and l < 97:
                        continue
                    key = [chr(i), chr(j), chr(k), chr(h), chr(l)]
                    key4 = ''.join(key)
                    if crypt.crypt(key4, salt) == hashed:
                        print(key4)
                        exit()