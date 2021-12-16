#!/usr/bin/python

import itertools
graph = {}
size = 10
adjacents = [(-1, 0), (0, -1), (1, 0), (0, 1)]

with open("input_test") as file:
    inputLines = ["9" * (size)]
    for line in file:
        inputLines.append("9" + line.strip() + "9")
    inputLines.append("9" * (size))

    for y in range(1, len(inputLines) - 1):
        for x in range(1, len(inputLines[0]) - 1):
            graph["{}-{}".format(x,y)] = []
            for adjacent in adjacents:
                graph["{}-{}".format(x,y)].append(["{}-{}".format(x+adjacent[0],y+adjacent[1]), int(inputLines[y+adjacent[1]][x+adjacent[0]])])

    print(graph)
