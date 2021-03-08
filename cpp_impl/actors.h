#ifndef ACTOR_H
#define ACTOR_H

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

        
        Creature(double* pos, double* direction, double sr=30, double er=1, double speed=1);
        // Creature(const Creature &c) {
        //     std::cout << "copy constructor invoked\n";
        // }
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