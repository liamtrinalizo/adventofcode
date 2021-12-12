#!/usr/bin/python

caves = dict()
paths = []

def searchPath(curr, visited, path):
    if curr.islower():
        visited[curr] += 1

    path.append(curr)
    if curr == "end":
        paths.append(path)
    else:
        for i in caves[curr]:
            if i != "start" and (visited[i] < 1 or visited[i] > 0 and max(visited.values()) < 2):
                searchPath(i, visited, path.copy())

    visited[curr] -= 1


with open("input") as file:
    visited = dict()
    for line in file:
        connections = line.strip().split(sep="-")
        for i in range(2):
            orig = connections[i]
            dest = connections[1-i]
            if caves.__contains__(orig):
                caves[orig].append(dest)
            else:
                caves[orig] = [dest]
                visited[orig] = 0

    searchPath("start", visited, [])

    print("Number of paths", len(paths))
