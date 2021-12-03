#!/usr/bin/python

most_common = [0] * 12

file = open("input")
for line in file:
    input_size = len(line) - 1
    for i in range(input_size):
        if int(line[i]) > 0:
            most_common[i] += 1
        else:
            most_common[i] -= 1

gamma = 0
epsilon = 0
for i in range(input_size):
    if most_common[i] > 0:
        gamma |= 1 << input_size - 1 -i
    else:
        epsilon |= 1 << input_size - 1 -i

print(bin(gamma), bin(epsilon))
print("power consumption " + str(epsilon * gamma))
