#!/usr/bin/python

horiz = 0
depth = 0
aim = 0

file = open("input")
for line in file:
    val = line.split()
    if val[0] == "forward":
        horiz += int(val[1])
        depth += aim * int(val[1])
    if val[0] == "down":
        aim   += int(val[1])
    if val[0] == "up":
        aim   -= int(val[1])

print("final pos " + str(horiz * depth))
