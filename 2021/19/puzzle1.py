#!/usr/bin/python

import re, sys, itertools as itt

detectedBeacons = 0

with open("input_test") as file:
    scanners = []
    for line in file:
        if line[0:12] == "--- scanner ":
            scanners.append({"scanner":re.findall("\d+", line), "beacons":[]})
        elif len(line.strip()) != 0:
            scanners[-1]["beacons"].append([])
            for coor in re.findall("-?\d+", line):
                scanners[-1]["beacons"][-1].append(int(coor))
                detectedBeacons += 1

    intersections = 0
    beaconMatch = []
# TODO check overlap with stack
    for s0 in range(len(scanners)):
        for s1 in range(s0 + 1, len(scanners)):
            beaconMatch.append({"scan0": s0, "scan1": s1, "matches":[]})
            for b00 in range(len(scanners[s0]["beacons"])):
                for b01 in range(b00 + 1, len(scanners[s0]["beacons"])):

                    vector1 = []
                    for a,b in zip(scanners[s0]["beacons"][b00], scanners[s0]["beacons"][b01]):
                        vector1.append(b - a)

                    matchFound = False
                    for b10 in range(len(scanners[s1]["beacons"])):
                        for b11 in range(b10 + 1, len(scanners[s1]["beacons"])):

                            vector2 = []
                            for a,b in zip(scanners[s1]["beacons"][b10], scanners[s1]["beacons"][b11]):
                                vector2.append(b - a)

                            # apply the 48 rotations
                            for perm in itt.permutations(vector2):
                                for orient in itt.product([perm[0], -1*perm[0]],
                                                          [perm[1], -1*perm[1]],
                                                          [perm[2], -1*perm[2]]):

                                    # check if same vector
                                    if vector1[0] == orient[0] and vector1[1] == orient[1] and vector1[2] == orient[2]:
                                        # TODO save matching rotation to compare with expl
                                        relativOrigin = []
                                        # TODO  cannot work the rotation has to be applied
                                        for r0, r1 in zip(scanners[s0]["beacons"][b00], scanners[s1]["beacons"][b10]):
                                            relativOrigin.append(r0 - r1)

                                        beaconMatch[-1]["matches"].append([b00, b01, b10, b11, relativOrigin])
                                        matchFound = True
                                        break
                                if matchFound:
                                    break
                            if matchFound:
                                break
                        if matchFound:
                            break

            # check if there is enougth matches to conserder overlap
            if len(beaconMatch[-1]["matches"]) >= 12:
                intersections += len(beaconMatch[-1]["matches"])

    for i in beaconMatch:
        print(i["scan0"], i["scan1"])
        for j in i["matches"]:
            print("\t\t\t", j)


    scanners[0]["posiRel0"] = [0,0,0]

    posiRel = []
    uniqBeacons = []
    # TODO try to check matches for wrong relativ position
    for p0, p1 in zip(beaconMatch[0]["matches"][0], beaconMatch[0]["matches"][0]):
        posiRel.append(p1 - p0)
    scanners[1]["posiRel0"] = posiRel

    for b in scanners[1]["beacons"]:
        uniqBeacons.append([])
        for b1, b2 in zip(b, scanners[1]["posRel0"]):
            uniqBeacons[-1].append(b1 + b2)

    print(uniqBeacons)

    print("tot", detectedBeacons - intersections)
