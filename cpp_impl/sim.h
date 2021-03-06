#ifndef SIM_H
#define SIM_H

#include <vector>


class Creature;
struct Food;

class Simulator {
    
    public:
        int num_creatures;
        int num_food;
        std::vector<Creature> creatures;
        std::vector<Food*> foods;

        Simulator(int num_creatures, int num_food);
        void run(int num_ticks);
         
    
};





#endif