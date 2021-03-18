import matplotlib.pyplot as plt 
import numpy as np

import sys





if __name__ == '__main__':
    
    red_pop = []
    blue_pop = []
    green_pop = []

    blue_avg_speed = []
    green_avg_speed = []

    green_avg_sense = []

    with open("results/run7.txt", 'r') as f:
        for line in f:
            lst = np.array(line.split(), dtype=np.float64)
            lst = lst.reshape((-1, 3))
            pops = lst[:,0]
            red_pop.append(pops[pops == 1].shape[0])
            blue_pop.append(pops[pops == 2].shape[0])
            green_pop.append(pops[pops == 3].shape[0])
            blue_filter = lst[:,0] == 2
            green_filter = lst[:,0] == 3
            blue_avg_speed.append(np.average(lst[blue_filter][:,1]))
            green_avg_speed.append(np.average(lst[green_filter][:,1]))
            green_avg_sense.append(np.average(lst[green_filter][:,2]))
            


 

    red_pop = np.array(red_pop, dtype=int)
    blue_pop = np.array(blue_pop, dtype=int)
    green_pop = np.array(green_pop, dtype=int)
    total_pop = red_pop + blue_pop + green_pop

    blue_avg_speed = np.array(blue_avg_speed, dtype=np.float64)
    green_avg_speed = np.array(green_avg_speed, dtype=np.float64)

    green_avg_sense = np.array(green_avg_sense, dtype=np.float64)


    plt.figure(1)
    plt.plot(blue_avg_speed[:], 'b')
    plt.plot(green_avg_speed[:], 'g')
 
    plt.figure(2)
    plt.plot(red_pop[:], 'r')
    plt.plot(blue_pop[:], 'b')
    plt.plot(green_pop[:], 'g')
    plt.plot(total_pop[:], 'y')


    plt.figure(3)
    plt.plot(green_avg_sense[:], 'g')

    plt.show()