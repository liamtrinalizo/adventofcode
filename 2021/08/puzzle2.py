#!/usr/bin/python

defSegs = ["abcefg","df","acdeg","acdfg","bcdf","abdfg","abdefg","acf","abcdefg","abcdfg"]
segs2 = "abcdefg"

outputSum = 0

with open("input") as file:
    for line in file:
        segments = [''.join(sorted(i)) for i in line.split(sep="|")[0].split()]
        outputs = [''.join(sorted(i)) for i in line.split(sep="|")[1].split()]
        codes = [""] * 10

        for easyNum in [1, 4, 7, 8]:
            for seg in segments:
                if len(seg) == len(defSegs[easyNum]):
                    codes[easyNum] = seg
                    segments.remove(seg)
                    break

        for seg in segments:
            if len(seg) == len(defSegs[3]) and set(codes[1]).issubset(set(seg)):
                codes[3] = seg
                segments.remove(seg)
                break
        for seg in segments:
            if len(seg) == len(defSegs[6]) and not set(codes[1]).issubset(set(seg)):
                codes[6] = seg
                segments.remove(seg)
                break
        for seg in segments:
            if len(seg) == len(defSegs[9]) and set(codes[4]).issubset(set(seg)):
                codes[9] = seg
                segments.remove(seg)
                break
        for seg in segments:
            if len(seg) == len(defSegs[0]):
                codes[0] = seg
                segments.remove(seg)
                break
        for seg in segments:
            if len(seg) == len(defSegs[5]) and set(seg).issubset(set(codes[9])):
                codes[5] = seg
                segments.remove(seg)
                break
        codes[2] = segments[0]

        outputVal = ""
        for out in outputs:
            outputVal += str(codes.index(out))

        outputSum += int(outputVal)
        print(outputVal)

    print("Output sum:", outputSum)
