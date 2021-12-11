#!/usr/bin/python

import itertools, sys

lineSize = 10
totSteps = 1000
energyLevels = [["B"] * (lineSize + 2)] # border padding
adjacents = list(itertools.product([-1, 0, 1], [-1, 0, 1]))
adjacents.remove((0,0)) # remove origin coordinate

with open("input") as file:
    for line in file:
        lineVal = [int(i) for i in list(line.strip())]
        energyLevels.append(["B", *lineVal, "B"])
    energyLevels.append(["B"] * (lineSize + 2)) # border padding

    for step in range(totSteps):
        for y in range(1, lineSize + 1):
            for x in range(1, lineSize + 1):
                energyLevels[y][x] += 1

        for y in range(1, lineSize + 1):
            for x in range(1, lineSize + 1):
                if energyLevels[y][x] != "F" and energyLevels[y][x] > 9:
                    energyLevels[y][x] = "F"

                    adjacentFlashes = [[x, y]]
                    while len(adjacentFlashes) > 0:
                        currPos = adjacentFlashes.pop()

                        for adjacent in adjacents:
                            adjacentPos = [currPos[0] + adjacent[0], currPos[1] + adjacent[1]]
                            if energyLevels[adjacentPos[1]][adjacentPos[0]] in ["B", "F"]:
                                continue
                            if energyLevels[adjacentPos[1]][adjacentPos[0]] >= 9:
                                energyLevels[adjacentPos[1]][adjacentPos[0]] = "F"
                                adjacentFlashes.append(adjacentPos)
                            else:
                                energyLevels[adjacentPos[1]][adjacentPos[0]] += 1

        stepFlashCnt = 0
        for y in range(1, lineSize + 1):
            for x in range(1, lineSize + 1):
                if energyLevels[y][x] == "F":
                    energyLevels[y][x] = 0
                    stepFlashCnt += 1

        if stepFlashCnt == lineSize**2:
            print("All octopuses flash in step", step + 1)
            sys.exit()
