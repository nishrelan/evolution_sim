

import numpy as np
from globals import *
from utils import *


class Dot:
    def __init__(self, simulator, x, y,
                    speed=1, curr_direction=[0,0],
                    sense_radius=30):


        self.pos = np.array([x,y], dtype=np.float64)
        self.curr_direction = np.asarray(curr_direction, dtype=np.float64)
        # amount of steps left in current direction
        self.steps_left = 30 + np.random.randint(0, 30) - 15
        self.speed = speed
        self.sense_radius = sense_radius
        self.simulator = simulator
        self.eat_radius = 1
        self.food_eaten = 0
        self.energy = 800


    # if override is True, reset direction
    def _random_move(self, override=False):
        if self.steps_left > 0 and not override:
            self.steps_left -= 1
        else:
            self.steps_left = 30 + np.random.randint(0, 30) - 15
            self.curr_direction = np.random.rand(2) * 2 - 1
            self.curr_direction = self.curr_direction / np.linalg.norm(self.curr_direction)


    def _glide_through_walls(self):
        x,y = self.pos

        if x < 0:
            self.pos[0] = WIDTH
        elif x > WIDTH:
            self.pos[0] = 0
        if y < 0:
            self.pos[1] = HEIGHT
        elif y > HEIGHT:
            self.pos[1] = 0


    def _hit_walls(self):
        x,y = self.pos

        if x < 0 or x > WIDTH or y < 0 or y > HEIGHT:
            self._random_move(override=True)

        if x < 0:
            x = 0
            self.pos[0] = 0
        elif x > WIDTH:
            x = WIDTH
            self.pos[0] = WIDTH
        if y < 0:
            y = 0
            self.pos[1] = 0
        elif y > HEIGHT:
            y = HEIGHT
            self.pos[1] = HEIGHT


        
    def set_pos(self, x, y):
        self.pos = np.array([x, y], dtype=np.float64)

    def reproduce(self):
        if self.food_eaten > 1:
            # 50% chance of mutation
            if np.random.rand() < 0.5:
                speed_noise = np.random.normal(0, 0.25, 1)[0]
            else:
                speed_noise = 0
            if np.random.rand() < 0.5:
                sense_noise = np.random.normal(0, 3, 1)[0]
            else:
                sense_noise = 0
            return Dot(
                self.simulator, 0, 0, 
                curr_direction=random_dir(),
                speed=self.speed+speed_noise,
                sense_radius=self.sense_radius + sense_noise
            )
        else:
            return None


    def sleep(self):
        self.food_eaten = 0
        self.energy = 800

    def update(self, do_nothing=False):
        if do_nothing:
            return

        # sit, do nothing, do not expend energy if have eaten 2 food
        if self.food_eaten > 1:
            return

        # Eat food if collision
        if self.simulator.attempt_eat_food(self, self.eat_radius):
            self.food_eaten += 1
            self.energy += 1000

        # Check if food is nearby. If so, orient direction towards it
        food = self.simulator.get_closest_food(self.pos, self.sense_radius)
        if food:
            self.curr_direction = orient(self.pos, food.pos)

        else:
            self._random_move()

        # execute movement
        self.pos += self.speed*self.curr_direction

        self._hit_walls()

        
        self.energy -= (self.sense_radius/60 + 1 + (self.speed/2)**2)
        if self.energy <= 0:
            self.simulator.kill(self)


class Food:
    def __init__(self, x, y):
        self.pos = np.array([x,y], dtype=np.float64)




    