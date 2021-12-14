#!/usr/bin/python

steps = 40

with open("input") as file:
    polymer = file.readline().strip()
    file.readline()

    polymerPairsCnt = {}
    rules = {}
    defaultRules = {}
    for line in file:
        rule = line.strip().split()
        rules[rule[0]] = rule[2]
        defaultRules[rule[0]] = 0
        polymerPairsCnt[rule[0]] = polymer.count(rule[0])

    for step in range(steps):
        tmp = defaultRules.copy()
        for pair in polymerPairsCnt:
            tmp[pair[0] + rules[pair]] += polymerPairsCnt[pair]
            tmp[rules[pair] + pair[1]] += polymerPairsCnt[pair]
        polymerPairsCnt = tmp.copy()

    letterCnt = {letter:0 for letter in set(rules.values())}
    for pair in polymerPairsCnt:
        letterCnt[pair[0]] += polymerPairsCnt[pair] # overall count of the pair first letter

    letterCnt[polymer[-1]] += 1 # Increment last char of polymer

    print("Max minus min:", letterCnt[max(letterCnt, key=letterCnt.get)] - letterCnt[min(letterCnt, key=letterCnt.get)])
