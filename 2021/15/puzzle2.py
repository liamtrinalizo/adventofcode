#!/usr/bin/python

import sys

graph = {}
size = 100
adjacents = [(-1, 0), (0, -1), (1, 0), (0, 1)]
inf = 999999

with open("input") as file:
    inputLines = []
    for line in file:
        inputLines.append(line.strip())

    # create dictionary of adjacent val for all positions
    for y in range(0, len(inputLines)):
        for yy in range(0, 5):
            for x in range(0, len(inputLines[0])):
                for xx in range(0, 5):
                    realx = x + (size*xx)
                    realy = y + (size*yy)
                    graph["{}-{}".format(realx,realy)] = {}
                    # TODO find better way to represent infinity
                    graph["{}-{}".format(realx,realy)]["dist"] = inf # infinite distance
                    graph["{}-{}".format(realx,realy)]["val"] = (int(inputLines[y][x]) + xx + yy - 1) % 9 + 1
                    graph["{}-{}".format(realx,realy)]["neighbors"] = []
                    for adjacent in adjacents:
                        adjax = realx + adjacent[0]
                        adjay = realy + adjacent[1]
                        if adjax < 0 or adjax > size*5 - 1 or adjay < 0 or adjay > size*5 - 1:
                            continue

                        coord = "{}-{}".format(realx + adjacent[0],realy + adjacent[1])
                        graph["{}-{}".format(realx,realy)]["neighbors"].append(coord)

    # implementing Dijkstra, TODO it's slow as F*** try A*
    curr = "0-0"
    graph["0-0"]["dist"] = 0
    while curr != "{}-{}".format(size*5 -1,size*5 -1):
        for neighbor in graph[curr]["neighbors"]:
            if neighbor in graph:
                newDist = graph[curr]["dist"] + graph[neighbor]["val"]
                if graph[neighbor]["dist"] == -1 or newDist < graph[neighbor]["dist"]:
                    graph[neighbor]["dist"] = newDist
        graph.pop(curr)
        curr = min(graph, key=lambda x: graph[x]["dist"])

    # test data should be 315
    print("total risk", graph[curr]["dist"])
