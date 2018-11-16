from nltk.tokenize import sent_tokenize, word_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    lista = a.split('\n')
    listb = b.split('\n')
    line = []
    for list in lista:
        if listb.count(list) > 0 and line.count(list) == 0:
            line.append(list)
    return line


def sentences(a, b):
    """Return sentences in both a and b"""
    a = a.replace('\n',' ')
    b = b.replace('\n',' ')
    lista = sent_tokenize(a)
    listb = sent_tokenize(b)
    sentence = []
    for list in lista:
        if listb.count(list) > 0 and sentence.count(list) == 0:
            sentence.append(list)
    return sentence


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    a = a.replace('\n',' ')
    b = b.replace('\n',' ')
    lista = a.split()
    listb = b.split()
    suba = []
    subb = []
    sub = []
    for s in lista:
        if len(s) >= n:
            for i in range(len(s) - n + 1):
                suba.append(s[i: i + n])

    for s in listb:
        if len(s) >= n:
            for i in range(len(s) - n + 1):
                subb.append(s[i: i + n])

    for substring in suba:
        if subb.count(substring) > 0 and sub.count(substring) == 0:
            sub.append(substring)
    return sub
