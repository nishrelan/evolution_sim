from simulator import *
import argparse
import matplotlib.pyplot as plt

from matplotlib import colors
import numpy as np

def get_args():
    parser = argparse.ArgumentParser()

    parser.add_argument('-num_creatures', type=int, default=25)
    parser.add_argument('-num_food', type=int, default=50)
    parser.add_argument('-max_fps', type=int, default=50)
    parser.add_argument('-num_days', type=int, default=10)

    return parser.parse_args()


if __name__ == '__main__':

    args = get_args()

    sim = Simulator(num_creatures=args.num_creatures, 
                    num_food=args.num_food,
                    fps=args.max_fps,
                    days=args.num_days)
    sim.init()
    sim.run()

    speeds = [creature.speed for creature in sim.creatures]
    senses = [creature.sense_radius for creature in sim.creatures]
    
    hist, bins = np.histogram(speeds)
    plt.hist(speeds, density=False, bins=10)
    plt.show()
    hist, bins = np.histogram(senses)
    plt.hist(senses, density=False, bins=10)
    plt.show()
    print(np.average(np.asarray(senses)))
    print(np.average(np.asarray(speeds)))

    pg.quit()

