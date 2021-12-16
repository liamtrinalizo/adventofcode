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

def readOperator():
    if readOffset(1) == 0:
        subpackLength = readOffset(15)
        currOffset = offset
        while offset - currOffset < subpackLength:
            readPackage()
    else:
        subpackCnt = readOffset(11)
        for i in range(subpackCnt):
            readPackage()

def readPackage():
    global versSum
    vers = readOffset(3) # read packet version
    versSum += vers

    if readOffset(3) == 4:   # read packet type
        readLiteral()
    else:
        readOperator()

with open("input") as file:
    hexaInput = file.readline().strip()
    for char in hexaInput:
        for bit in range(3, -1, -1):
            num.append(int(char,16) >> bit & 0x1)

    readPackage()
    print("Version sum:", versSum)
