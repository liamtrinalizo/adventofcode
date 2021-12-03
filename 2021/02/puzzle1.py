#!/usr/bin/python

horiz = 0
depth = 0

file = open("input")
for line in file:
    val = line.split()
    if val[0] == "forward":
        horiz += int(val[1])
    if val[0] == "down":
        depth += int(val[1])
    if val[0] == "up":
        depth -= int(val[1])

print("final pos" + str(horiz * depth))
