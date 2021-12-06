#!/usr/bin/python

coor_max = 1000
floor_map = [[0 for x in range(coor_max)] for y in range(coor_max)]

def print_floor(floor_map):
    overlap_cnt = 0
    for y in range(len(floor_map)):
        for x in range(len(floor_map)):
            value = floor_map[x][y]
            if value > 0:
                print(floor_map[x][y], end="")
                if value > 1:
                    overlap_cnt += 1
            else:
                print(".", end="")
        print()
    return overlap_cnt

with open("input") as file:
    for line in file:
        value = line.split()
        p1 = [int(i) for i in value[0].split(sep=",")]
        p2 = [int(i) for i in value[2].split(sep=",")]
        for axis in range(2):
            if p1[axis] == p2[axis]:
                diff_axis = 1 - axis
                for diff_val in range(p1[diff_axis], p2[diff_axis], 1 if p1[diff_axis] < p2[diff_axis] else -1):
                    vent_pos = [0,0]
                    vent_pos[axis] = p1[axis] # common value
                    vent_pos[diff_axis] = diff_val
                    floor_map[vent_pos[0]][vent_pos[1]] += 1
        for pos in zip(range(p1[0], p2[0], 1 if p1[0] < p2[0] else -1), range(p1[1], p2[1], 1 if p1[1] < p2[1] else -1)):
            vent_pos = [pos[0], pos[1]]
            floor_map[pos[0]][pos[1]] += 1

        floor_map[p2[0]][p2[1]] += 1

    overlap_cnt = print_floor(floor_map)
    print("Overlap counter", overlap_cnt)
