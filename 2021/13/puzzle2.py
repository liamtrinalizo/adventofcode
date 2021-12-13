#!/usr/bin/python

dots = []
axis = ["x", "y"]
foldLast = [0, 0]

with open("input") as file:
    for line in file:
        line = line.strip()
        if line != "":
            dots.append([int(i) for i in line.split(sep=",")])
        else:
            break;

    for line in file:
        fold = line.split()[2].split(sep="=")

        tmp = dots.copy()
        for dot in dots:
            foldAxis = axis.index(fold[0])
            foldVal  = int(fold[1])
            foldLast[foldAxis] = foldVal
            if dot[foldAxis] > foldVal:
                tmp.remove(dot)
                foldedDot = [0, 0]
                foldedDot[foldAxis] = 2*foldVal - dot[foldAxis]
                foldedDot[1 - foldAxis] = dot[1 - foldAxis]
                if tmp.count(foldedDot) == 0:
                    tmp.append(foldedDot)

        dots = tmp.copy()

    for y in range(foldLast[1]):
        for x in range(foldLast[0]):
            if tmp.count([x,y]) > 0:
                print("#",end="")
            else:
                print(".",end="")
        print()
