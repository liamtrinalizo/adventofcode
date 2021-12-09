#!/usr/bin/python

line_size = 100
floor = ["9" * (line_size + 2) ] # adding y padding
riskSum = 0

with open("input") as file:
    for line in file:
        floor.append("9" + line.strip() + "9") # line with x padding
    floor.append(["9"] * (line_size + 2)) # adding y padding

    for y in range(1,len(floor) - 1):
        for x in range(1, len(floor[0]) - 1):
            lowest = True
            for neighbor in [[-1, 0],[0, -1],[1, 0],[0, 1]]:
                if int(floor[y][x]) >= int(floor[y+neighbor[1]][x+neighbor[0]]):
                    lowest = False
                    break

            if lowest == True:
                riskSum += int(floor[y][x]) + 1

    print("Risk sum:", riskSum)
