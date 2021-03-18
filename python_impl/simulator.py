import numpy as np
import sys
from globals import *
from actors import *





class Simulator:

    def __init__(self, num_creatures=10, num_food=5, fps=30, ticks=1000, days=10):
        self.num_food = num_food
        self.num_creatures = num_creatures
        self.fps = fps
        self.ticks = ticks
        self.dead = 0
        self.days = days



    # returns closest sprite within radius, if one exists
    def get_closest_food(self, creature_pos, radius):
        if not self.foods:
            return None
        distances = [distance(food.pos, creature_pos) for food in self.foods]
        min_distance = min(distances)
        closest_food = None
        if min_distance < radius:
            closest_food = self.foods[distances.index(min_distance)]

        return closest_food

    
    def attempt_eat_food(self, creature, eat_radius):
        eaten_food = None
        remove_idx = -1
        for idx, food in enumerate(self.foods):
            if distance(food.pos, creature.pos) < eat_radius:
                eaten_food = food
                remove_idx = idx
                break
        if eaten_food is not None:
            self.foods.pop(remove_idx)
        return False if eaten_food is None else True


    def kill(self, creature):
        self.creatures.remove(creature)
        self.num_creatures -= 1

    def init(self):

        self.creatures = []
        self.foods = []
        

        # Create the creatures, initialize with random position on edge and velocity
        for i in range(self.num_creatures):
            x,y = random_wall_pos()

            direction = np.random.rand(2) * 2 - 1
            direction = direction / np.linalg.norm(direction)

            dot = Dot(self, x, y, curr_direction=direction)
            self.creatures.append(dot)

        # create food, initialize with random position
        for i in range(self.num_food):
            x = np.random.randint(0, WIDTH + 1)
            y = np.random.randint(0, HEIGHT + 1)

            food = Food(x, y)
            self.foods.append(food)



    def run(self):
        for day in range(self.days):
            # Go through day 
            for i in range(1000):
                for creature in self.creatures:
                    creature.update()
                

            # Put creatures back on edges, have them replicate
            baby_list = []
            for creature in self.creatures:
                x, y = random_wall_pos()
                creature.set_pos(x, y)
                baby = creature.reproduce()
                if baby:
                    x, y = random_wall_pos()
                    baby.set_pos(x, y)
                    baby_list.append(baby)
                creature.sleep()

            
            self.creatures += baby_list
            self.num_creatures += len(baby_list)    
            self.foods = []

            # Add new food for next day
            for i in range(self.num_food):
                x = np.random.randint(0, WIDTH + 1)
                y = np.random.randint(0, HEIGHT + 1)

                food = Food(x, y)
                self.foods.append(food)


            print(self.num_creatures)

