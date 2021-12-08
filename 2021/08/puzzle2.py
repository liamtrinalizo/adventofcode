#!/usr/bin/python

defSegs = ["abcefg","df","acdeg","acdfg","bcdf","abdfg","abdefg","acf","abcdefg","abcdfg"]
segs2 = "abcdefg"

easyDigitCnt = 0

with open("input") as file:
    for line in file:
        segments = [''.join(sorted(i)) for i in line.split(sep="|")[0].split()]
        outpus = [''.join(sorted(i)) for i in line.split(sep="|")[1].split()]
        codes = [""] * 10

        for easyNum in [1, 4, 7, 8]:
            for seg in segments:
                if len(seg) == len(defSegs[easyNum]):
                    codes[easyNum] = seg
                    segments.remove(seg)
                    break

        for seg in segments:
            if len(seg) == len(defSegs[3] and set(defSegs[1]).isSubset(set(seg)):
                codes[3] = seg
                segments.remove(seg)
                break
        for seg in segments:
            if len(seg) == len(defSegs[6] and not set(defSegs[1]).isSubset(set(seg)):
                codes[6] = seg
                segments.remove(seg)
                break
        for seg in segments:
            if len(seg) == len(defSegs[9] and set(defSegs[4]).isSubset(set(seg)):
                codes[9] = seg
                segments.remove(seg)
                break
        for seg in segments:
            if len(seg) == len(defSegs[0]):
                codes[0] = seg
                segments.remove(seg)
                break
        for seg in segments:
            if len(seg) == len(defSegs[5] and set(seg).isSubset(set(defSegs[9])):
                codes[5] = seg
                segments.remove(seg)
                break
        codes[2] == segments[0]

        print(codes)

    outputSum = 0
