#!/usr/bin/python

caves = dict()
paths = []

def searchPath(curr, visited, path):
    if curr.islower():
        visited[curr] = True

    path.append(curr)
    if curr == "end":
        paths.append(path)
    else:
        for i in caves[curr]:
            if not visited[i]:
                searchPath(i, visited, path.copy())

    visited[curr] = False


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
                visited[orig] = False

    searchPath("start", visited, [])

    print("Number of paths", len(paths))
