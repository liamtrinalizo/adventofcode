#!/usr/bin/python

import sys

graph = {}
size = 100
adjacents = [(-1, 0), (0, -1), (1, 0), (0, 1)]

with open("input") as file:
    inputLines = ["9" * (size+2)]
    for line in file:
        inputLines.append("9" + line.strip() + "9")
    inputLines.append("9" * (size+2))

    # create dic of adjacent val for all positions
    for y in range(1, len(inputLines) - 1):
        for x in range(1, len(inputLines[0]) - 1):
            graph["{}-{}".format(x,y)] = {}
            # TODO find better way to represent infinity
            graph["{}-{}".format(x,y)]["dist"] = -1 # infinite distance
            graph["{}-{}".format(x,y)]["neighbors"] = []
            for adjacent in adjacents:
                graph["{}-{}".format(x,y)]["neighbors"].append(["{}-{}".format(x+adjacent[0],y+adjacent[1]),
                    int(inputLines[y+adjacent[1]][x+adjacent[0]])])

    # implementing Dijkstra
    curr = "1-1"
    graph["1-1"]["dist"] = 0
    while curr != "{}-{}".format(size,size):
        for neighbor in graph[curr]["neighbors"]:
            if neighbor[0] in graph:
                newDist = graph[curr]["dist"] + neighbor[1]
                if graph[neighbor[0]]["dist"] == -1 or newDist < graph[neighbor[0]]["dist"]:
                    graph[neighbor[0]]["dist"] = newDist
        graph.pop(curr)
        # search for smallest unvisited node
        minDist = -1
        for node in graph:
            if minDist == -1 or (graph[node]["dist"] < minDist and graph[node]["dist"] != -1):
                curr = node
                minDist = graph[node]["dist"]

    print("total risk", graph[curr]["dist"])
