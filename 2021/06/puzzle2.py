#!/usr/bin/python

days=256
fishes_day = [0] * 9

with open("input") as file:
    fishes = [int(i) for i in file.readline().split(sep=",")]
    for fish in fishes:
        fishes_day[fish] +=1
    for i in range(days):
        fishes_tmp = fishes_day.copy()
        for i in range(len(fishes_day) - 1, -1, -1):
            if i == 0:
                fishes_day[6] += fishes_tmp[0]
                fishes_day[8] = fishes_tmp[0]
            else:
                fishes_day[i - 1] = fishes_tmp[i]

    print("Number of fish:", sum(fishes_day[:]))
