#ifndef ACTOR_H
#define ACTOR_H


const double INITIAL_ENERGY = 500;
const double ENERGY_FROM_FOOD = 500;
const double PROCREATION_TIME = 300;

const int SPEED = 1; const int SENSE = 2;

class Simulator;

class Creature {
    public:
        double pos[2];
        double sense_radius;
        double eat_radius;
        double speed;
        double direction[2];
        Simulator* sim;
        int steps_left;
        double energy;
        bool is_dead;
        double time_till_procreate;
        int type;


        
        Creature(double* pos, double* direction, double sr=30, double er=1, double speed=1);
        void update();
        void continue_random_movement();
};

struct Food {
    double pos[2];
    Food(double* p) {
        pos[0] = p[0];
        pos[1] = p[1];
    }
};




#endif