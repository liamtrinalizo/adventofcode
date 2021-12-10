#!/usr/bin/python

openBrqs = ["(", "[", "{", "<"]
closeBrqs = [")", "]", "}", ">"]
scores = [3, 57, 1197, 25137]

finalScore = 0

with open("input") as file:
    for line in file:
        chunk = []
        line = line.strip()
        for char in line:
            if openBrqs.count(char) != 0:
                chunk.append(char)
            elif closeBrqs.count(char) != 0:
                lastOpenBrq = chunk.pop()
                if closeBrqs.index(char) != openBrqs.index(lastOpenBrq):
                    finalScore += scores[closeBrqs.index(char)]
            else:
                print("Error unexpected char:", char)

    print("Final score:", finalScore)


