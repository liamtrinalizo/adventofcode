#!/usb/bin/python

import re, sys

def explode(line):
    level = 0
    i = 0
    nums = []
    for m in re.finditer("\d+", line):
        nums.append({"num":int(m.group(0)), "pos":m.start() - 1})

    while i < len(line):
        if line[i] == "[":
            level += 1
            if level > 4: #test explosion first
                explo =  int(re.findall("\d+", line[i+1:])[0])
                exploPos = nums.index({"num": explo, "pos": i})

                # eval right num
                if exploPos + 2 < len(nums):
                    pos = nums[exploPos + 2]["pos"]
                    num = nums[exploPos + 2]["num"] + nums[exploPos + 1]["num"]
                    offset = 1 if nums[exploPos + 2]["num"] < 10 else 2
                    line = line[0:pos+1] + str(num) + line[pos + 1 + offset:]
                #print("  right ", line)

                # set exploded pair to 0
                pos = nums[exploPos]["pos"]
                offset = 3 + (1 if nums[exploPos]["num"]   < 10 else 2) + (1 if nums[exploPos+1]["num"] < 10 else 2)
                line = line[0:pos] + str(0) + line[pos + offset:]
                #print("  middle", line)

                # eval left num
                if exploPos - 1 >= 0:
                    pos = nums[exploPos - 1]["pos"]
                    num = nums[exploPos - 1]["num"] + nums[exploPos]["num"]
                    offset = 1 if nums[exploPos - 1]["num"] < 10 else 2
                    line = line[0:pos+1] + str(num) + line[pos + 1 + offset:]
                #print("  left  ", line)

                return line
        elif line[i] == "]":
            level -= 1

        i += 1
    return line

def split(line):
    i = 0
    while i < len(line):
        if ord(line[i]) > 47 and ord(line[i]) < 58 and ord(line[i+1]) > 47 and ord(line[i+1]) < 58:
            num = int(line[i] + line[i+1])
            #print("  split ", line)
            return line[0:i] + "[{},{}]".format(int(num/2), int((num+1)/2)) + line[i+2:]

        i += 1
    return line

def magnitude(line, i):
    val = 0
    pos = 0
    while i < len(line):
        if line[i] == '[':
            if pos == 0:
                tmp = magnitude(line, i+1)
                val = 3 * tmp[0]
                i = tmp[1]
            else:
                tmp = magnitude(line, i+1)
                val = val + 2 * tmp[0]
                i = tmp[1]
        elif line[i] == ']':
            return val, i
        elif line[i] == ',':
            pos += 1
        else:
            if pos == 0:
                val = 3 * int(line[i])
            else:
                val = val + 2 * int(line[i])

        i += 1


with open("input") as file:
    currNum = ""
    i = 0
    for line in file:
        i += 1

        if currNum == "":
            currNum = line.strip()
        else:
            currNum = "[{},{}]".format(currNum, line.strip())
            while True:
                prevNum = currNum
                currNum = explode(currNum)
                if prevNum == currNum:
                    currNum = split(currNum) # called only if nothing exploded
                if prevNum == currNum:
                    break

    print("magnitude", magnitude(currNum, 1)[0])
