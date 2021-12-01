#!/usr/bin/python

file = open("input", "r")
prev_line = 0
inc_count = -1

for line in file:
    if prev_line < int(line):
        inc_count += 1

    prev_line = int(line)

print("measurements larger than previous " + str(inc_count))
