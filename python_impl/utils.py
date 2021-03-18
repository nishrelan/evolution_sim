import numpy as np
from globals import *
import math

# Return distance between two points
def distance(pos1, pos2):
    diff = pos1 - pos2
    return math.sqrt(diff[0]**2 + diff[1]**2)

# return unit vecor that points from start to goal
def orient(start, goal):
    dir = goal - start
    unit = dir / np.linalg.norm(dir) 
    return unit


def random_wall_pos():
    wall = np.random.randint(0, 4)
    if wall == 0:
        y = 0
        x = np.random.randint(1, WIDTH)
    elif wall == 1:
        x = WIDTH - 1
        y = np.random.randint(1, HEIGHT)
    elif wall == 2:
        y = HEIGHT - 1
        x = np.random.randint(1, WIDTH)
    elif wall == 3:
        x = 0
        y = np.random.randint(1, HEIGHT)

    return x, y


def random_dir():
    direction = np.random.rand(2) * 2 - 1
    direction = direction / np.linalg.norm(direction)
    return direction