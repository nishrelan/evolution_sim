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

        
        Creature(double* pos, double* direction, double sr=30, double er=1, double speed=1);
        // Creature(const Creature &c) {
        //     std::cout << "copy constructor invoked\n";
        // }
        void update();
};

struct Food {
    double pos[2];
};




#endif