#!/usr/bin/python

most_common = [0] * 12

# rate_type 0 -> o2_gen, 1 -> scrubb
def most_common(bit, report, rate_type):
    msc = 0
    for val in report:
        if int(val[bit]) > 0:
            msc += 1
        else:
            msc -= 1

    if rate_type == "o2_gen":
        ret = 1 if msc >= 0 else 0
    elif rate_type == "scrubb":
        ret = 0 if msc >= 0 else 1

    return ret

rates = {"o2_gen": 0, "scrubb": 0}

with open("input") as file:
    report = [line.strip() for line in file]
    input_size = len(report[0]) - 1

    for key in rates:
        filtered = report
        for bit in range(input_size):
            msc = most_common(bit, filtered, key)
            filtered = filter(lambda val: int(val[bit]) == msc, filtered)
            filtered = list(filtered)
            if len(filtered) == 1:
                rates[key] = int(filtered[0], 2)
                break

    print("life support rating " + str(rates["o2_gen"] * rates["scrubb"]))
