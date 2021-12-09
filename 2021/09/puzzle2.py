#!/usr/bin/python

line_size = 100
floor = ["9" * (line_size + 2) ] # adding y padding
bassinsSizes = []
neighbors = [[-1, 0],[0, -1],[1, 0],[0, 1]]

with open("input") as file:
    for line in file:
        floor.append("9" + line.strip() + "9") # line with x padding
    floor.append(["9"] * (line_size + 2)) # adding y padding

    for y in range(1,len(floor) - 1):
        for x in range(1, len(floor[0]) - 1):
            lowest = True
            for neighbor in neighbors:
                if int(floor[y][x]) >= int(floor[y+neighbor[1]][x+neighbor[0]]):
                    lowest = False
                    break

            if lowest == True:
                bassinStack = [[x,y]]
                bassinPos = [[x,y]]
                while len(bassinStack) > 0:
                    currPos = bassinStack.pop()
                    for neighbor in neighbors:
                        currNeighbor = [currPos[0]+neighbor[0], currPos[1]+neighbor[1]]
                        if int(floor[currNeighbor[1]][currNeighbor[0]]) != 9 and bassinPos.count(currNeighbor) == 0:
                            bassinPos.append(currNeighbor)
                            bassinStack.append(currNeighbor)
                bassinsSizes.append(len(bassinPos))

    bassinsSizes.sort(reverse=True)
    print("Bassins multiplication:", bassinsSizes[0]*bassinsSizes[1]*bassinsSizes[2])
