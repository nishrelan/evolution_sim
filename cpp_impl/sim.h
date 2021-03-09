#ifndef SIM_H
#define SIM_H

#include <vector>

const int FOOD_GEN = 10;
const int FOOD_INTERVAL = 100;

class Creature;
struct Food;

class Simulator {
    
    public:
        int num_creatures;
        int num_food;
        std::vector<Creature> creatures;
        std::vector<Food> foods;
        std::vector<Creature> baby_buffer;
        int num_ticks;
        

        Simulator(int num_creatures, int num_food);
        void run(int num_ticks);
        void update();

        bool attempt_eat_food(double* pos, double eat_radius);
        bool find_food_in_radius(double* pos, double* food_pos, double sense_radius);
        void make_baby(Creature* baby) {
            baby_buffer.push_back(*baby);
        }
         
    
};





#endif