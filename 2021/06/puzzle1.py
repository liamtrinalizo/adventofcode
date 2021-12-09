#!/usr/bin/python

days=80

with open("input") as file:
    fishes = [int(i) for i in file.readline().split(sep=",")]
    for i in range(days):
        for fish_index in range(len(fishes) - 1, -1, -1):
            if fishes[fish_index] == 0:
                fishes.append(8)
                fishes[fish_index] = 6
            else:
                fishes[fish_index] -= 1

    print("Number of fish:", len(fishes))
