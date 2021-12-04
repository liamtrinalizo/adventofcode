#!/usr/bin/python

from dataclasses import dataclass
import sys

@dataclass
class Grid:
    nums: list[int]
    marked: [bool]

grids = []

with open("input") as file:
    draws = [int(x) for x in file.readline().split(",")]

    for line in file:
        if line == "\n":
            grid_row = 0
            grids.append(Grid([], [False] * 25))
        else:
            grids[-1].nums[grid_row*5:grid_row*5 + 4] = [int(x) for x in line.split()]
            grid_row += 1

    win_grid = None
    for draw in draws:
        win_draw = draw
        for grid in grids:
            try:
                grid.marked[grid.nums.index(draw)] = True
            except ValueError:
                continue

            for row in range(5):
                if grid.marked[row*5:row*5 + 5] == [True] * 5:
                    win_grid = grid
                    break

            for col in range(5):
                if [grid.marked[i] for i in [0+col, 5+col, 10+col, 15+col, 20+col]] == [True] * 5:
                    win_grid = grid
                    break

            if win_grid != None:
                unmarked_sum = 0
                for num in win_grid.nums:
                    if not win_grid.marked[win_grid.nums.index(num)]:
                        unmarked_sum += num
                print("Final score", win_draw*unmarked_sum)
                sys.exit()
