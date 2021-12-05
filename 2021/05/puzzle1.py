#!/usr/bin/python

line_points = []

with open("input2") as file:
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
                    line_points.append(vent_pos)
                line_points.append(p2)

    overlap_cnt = 0
    for pos in line_points:
        if line_points.count(pos) > 1:
            overlap_cnt +=1

    print("Overlap counter", overlap_cnt)
