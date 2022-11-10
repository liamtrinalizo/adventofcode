#!/usr/bin/python

import re

with open("input") as file:
    target = [int(i) for i in re.findall("-?\d+", file.readline())]
    counter = 0

    # try with highest x velocity and decrease
    for x in range(target[1], 1, -1):
        for y in range(target[2], -1 * target[2]):
            pos = [0, 0]
            velo = [x, y]
            tmp = []
            maxheight = 0
            while pos[0] < target[1] and pos[1] > target[2]:
                pos[0] = pos[0] + velo[0]
                pos[1] = pos[1] + velo[1]
                #print("\t", pos, target)
                velo[0] = velo[0] - 1 if velo[0] > 0 else 0
                velo[1] = velo[1] - 1
                if pos[0] >= target[0] and pos[0] <= target[1] and pos[1] >= target[2] and pos[1] <= target[3]:
                    if tmp != [x,y]:
                        tmp = [x,y]
                        counter += 1
                    #print("{}, {}".format(x, y))

    print(counter, "distinct velocity values")
