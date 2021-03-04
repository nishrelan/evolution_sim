import numpy as np
import pygame as pg
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
        closest_food = None
        closest_distance = radius + 1
        for food in self.foods:
            d = distance(food.pos, creature_pos)
            if d < radius:
                if closest_food is None or d < closest_distance:
                    closest_food = food
                    closest_distance = d
                
        return closest_food

    # uses sprite collide function to see if food can be eaten. If so, remove the food
    def attempt_eat_food(self, creature, eat_radius):
        def collided(creature, food):
            return distance(creature.pos, food.pos) < eat_radius

        food_within_reach = pg.sprite.spritecollide(creature, self.foods, dokill=True, collided=collided)
        return True if food_within_reach else False


    def kill(self, creature):
        self.creatures.remove(creature)
        self.num_creatures -= 1
        self.dead += 1

    def init(self):
        pg.init()
        self.screen = pg.display.set_mode([WIDTH, HEIGHT])
        self.creatures = pg.sprite.Group()
        self.foods = pg.sprite.Group()
        

        # Create the creatures, initialize with random position on edge and velocity
        for i in range(self.num_creatures):
            x,y = random_wall_pos()

            direction = np.random.rand(2) * 2 - 1
            direction = direction / np.linalg.norm(direction)

            dot = Dot(self, x, y, color=BLUE, curr_direction=direction)
            self.creatures.add(dot)

        # create food, initialize with random position
        for i in range(self.num_food):
            x = np.random.randint(0, WIDTH + 1)
            y = np.random.randint(0, HEIGHT + 1)

            food = Food(x, y)
            self.foods.add(food)



    def run(self):
        clock = pg.time.Clock()
        end = False
        

        for day in range(self.days):
            # Go through day 
            for i in range(1000):
                for event in pg.event.get():
                    if event.type == pg.QUIT:
                        sys.exit(0)
                self.creatures.update()
                self.foods.update()
                self.screen.fill(BACKGROUND)
                self.creatures.draw(self.screen)
                self.foods.draw(self.screen)
                pg.display.flip()
                clock.tick(self.fps)

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

            
            self.creatures.add(*baby_list)
            self.num_creatures += len(baby_list)    
            self.foods.empty()

            # Add new food for next day
            for i in range(self.num_food):
                x = np.random.randint(0, WIDTH + 1)
                y = np.random.randint(0, HEIGHT + 1)

                food = Food(x, y)
                self.foods.add(food)


            print(self.num_creatures)

