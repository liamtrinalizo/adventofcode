#!/usr/bin/python

import statistics as stats

openBrqs = ["(", "[", "{", "<"]
closeBrqs = [")", "]", "}", ">"]

scores = []

with open("input") as file:
    for line in file:
        chunk = []
        line = line.strip()
        isCorrupt = False
        for char in line:
            if openBrqs.count(char) != 0:
                chunk.append(char)
            elif closeBrqs.count(char) != 0:
                lastOpenBrq = chunk.pop()
                if closeBrqs.index(char) != openBrqs.index(lastOpenBrq):
                    isCorrupt = True
                    break

        if not isCorrupt:
            lineScore = 0
            while len(chunk) > 0:
                lineScore *= 5
                lineScore += openBrqs.index(chunk.pop()) + 1

            scores.append(lineScore)

    print("Final score:", stats.median(scores))


