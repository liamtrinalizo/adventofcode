#!/usr/bin/python

file = open("input", "r")
prev_window = [0, 0, 0]
inc_count = -3

for line in file:
    if prev_window[0] < int(line):
        inc_count += 1

    prev_window.append(int(line));
    prev_window = prev_window[1:4]

print("sums larger than previous " + str(inc_count))
