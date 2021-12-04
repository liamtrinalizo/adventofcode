#!/usr/bin/python

from dataclasses import dataclass
from itertools import filterfalse
import sys

@dataclass
class Grid:
    nums: list[int]
    marked: list[bool]

grids = []

with open("input") as file:
    draws = [int(x) for x in file.readline().split(",")]

    for line in file:
        if line == "\n":
            grid_row = 0
            grids.append(Grid([], [False] * 25))
        else:
            grids[-1].nums[grid_row*5:grid_row*5 + 5] = [int(x) for x in line.split()]
            grid_row += 1

    for draw in draws:
        win_draw = draw
        grids_tmp = grids.copy()
        for grid in grids:
            for num in grid.nums:
                if num == draw:
                    grid.marked[grid.nums.index(draw)] = True

            for row in range(5):
                if grid.marked[row*5:row*5 + 5] == [True] * 5:
                    grids_tmp.remove(grid)

            if grids_tmp.count(grid) > 0:
                for col in range(5):
                    if [grid.marked[i] for i in [0+col, 5+col, 10+col, 15+col, 20+col]] == [True] * 5:
                        grids_tmp.remove(grid)

            if len(grids_tmp) == 0:
                unmarked_sum = 0
                for num in grid.nums:
                    if not grid.marked[grid.nums.index(num)]:
                        unmarked_sum += num
                print(win_draw)
                print(grid)
                print("Final score of last board", win_draw*unmarked_sum)
                sys.exit()

        grids = grids_tmp.copy()
