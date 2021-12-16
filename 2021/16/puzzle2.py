#!/usr/bin/python

num = []
numSize = 64
offset = 0
versSum = 0

def readOffset(cnt): # cnt: digit count
    global offset
    ret = 0
    for i in range(cnt):
        ret += num[offset + i] << cnt - i -1
    offset += cnt
    return ret

def readLiteral():
    group = readOffset(5)
    literal = group & 0xF
    while group & 0x10:
        group = readOffset(5)
        literal = (literal << 4) + (group & 0xF)
    return literal

def readOperator(typeId):
    litValues = []
    if readOffset(1) == 0:
        subpackLength = readOffset(15)
        currOffset = offset
        while offset - currOffset < subpackLength:
            litValues.append(readPackage())
    else:
        subpackCnt = readOffset(11)
        for i in range(subpackCnt):
            litValues.append(readPackage())

    if typeId == 0:
        return sum(litValues)
    elif typeId == 1:
        ret = 1
        for i in litValues:
            ret *= i
        return ret
    elif typeId == 2:
        return min(litValues)
    elif typeId == 3:
        return max(litValues)
    elif typeId == 5:
        return 1 if litValues[0] > litValues[1] else 0
    elif typeId == 6:
        return 1 if litValues[0] < litValues[1] else 0
    elif typeId == 7:
        return 1 if litValues[0] == litValues[1] else 0

def readPackage():
    global versSum
    vers = readOffset(3) # read packet version
    versSum += vers

    typeId = readOffset(3)
    if typeId == 4:   # read packet type
        return readLiteral()
    else:
        return readOperator(typeId)

with open("input") as file:
    hexaInput = file.readline().strip()
    for char in hexaInput:
        for bit in range(3, -1, -1):
            num.append(int(char,16) >> bit & 0x1)

    print("Evaluated num:", readPackage())
