#!/usr/bin/python

pos_max=2000
positions = [0] * pos_max

with open("input") as file:
    data = [int(i) for i in file.readline().split(sep=",")]
    for i in data:
        positions[i] += 1

    fuel_min = -1
    for i in range(len(positions)):
        fuel_cnt = 0
        for j in range(len(positions)):
            fuel_cnt += abs(i - j) * positions[j]

        if fuel_cnt < fuel_min or fuel_min == -1:
            fuel_min = fuel_cnt

    print("Minimum fuel", fuel_min)
