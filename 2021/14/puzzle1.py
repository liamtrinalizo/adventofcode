#!/usr/bin/python

steps = 10

with open("input") as file:
    polymer = list(file.readline().strip())
    file.readline()

    rules = {}
    for line in file:
        rule = line.strip().split()
        rules[rule[0]] = rule[2]

    for step in range(steps):
        tmp = polymer.copy()
        for i in range(len(polymer)-1):
            tmp.insert(i*2+1, rules[polymer[i] + polymer[i+1]])
        polymer = tmp.copy()

    extrems = [0, 0] # min, max
    for letter in set(rules.values()): # uniq set of letters
        if polymer.count(letter) < extrems[0] or extrems[0] == 0:
            extrems[0] = polymer.count(letter)
        if polymer.count(letter) > extrems[1] or extrems[1] == 0:
            extrems[1] = polymer.count(letter)

    print("Max minus min:", extrems[1]-extrems[0])
