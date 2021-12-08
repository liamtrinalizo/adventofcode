#!/usr/bin/python

easyDigitCnt = 0

with open("input") as file:
    for line in file:
        outputs = line.split(sep="|")[1].split()
        for dig in outputs:
            if len(dig) in [2, 4, 3, 7]:
                easyDigitCnt += 1

    print(easyDigitCnt)
