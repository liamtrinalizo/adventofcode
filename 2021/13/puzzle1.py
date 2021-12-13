#!/usr/bin/python

dots = []
axis = ["x", "y"]

with open("input") as file:
    for line in file:
        line = line.strip()
        if line != "":
            dots.append([int(i) for i in line.split(sep=",")])
        else:
            break;

    fold = file.readline().split()[2].split(sep="=")

    tmp = dots.copy()
    for dot in dots:
        foldAxis = axis.index(fold[0])
        foldVal  = int(fold[1])
        if dot[foldAxis] > foldVal:
            tmp.remove(dot)
            foldedDot = [0, 0]
            foldedDot[foldAxis] = 2*foldVal - dot[foldAxis]
            foldedDot[1 - foldAxis] = dot[1 - foldAxis]
            if tmp.count(foldedDot) == 0:
                tmp.append(foldedDot)

    print("Dots count: ", len(tmp))
