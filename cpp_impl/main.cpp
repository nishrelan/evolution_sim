#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <string>


double WIDTH = 500;
double HEIGHT = 500;


std::random_device rd; // truly random 
std::mt19937 mt; // prng

// uniform distributions
std::uniform_real_distribution<double>  dist; 
std::uniform_real_distribution<double> width; 
std::uniform_real_distribution<double> height;


void initialize_randomness() {
    mt.seed(rd());

    width.param(std::uniform_real_distribution<double>::param_type(0, WIDTH));
    height.param(std::uniform_real_distribution<double>::param_type(0, HEIGHT));
    dist.param(std::uniform_real_distribution<double>::param_type(-1, 1));
}

double uniform_rand() {
    return dist(mt);
}

double width_rand() {
    return width(mt);
}
double height_rand() {
    return height(mt);
}

void normalize(double* v) {
    double magnitude = sqrt(v[0]*v[0] + v[1]*v[1]);
    v[0] = v[0] / magnitude;
    v[1] = v[1] / magnitude;
}

void random_unit_direction(double* v) {
    v[0] = uniform_rand();
    v[1] = uniform_rand();
    normalize(v);
}

void random_pos(double* v) {
    v[0] = width_rand();
    v[1] = height_rand();
}

class Simulator;




struct Food {
    double pos[2];
};

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

class Simulator {
    
    public:
        int num_creatures;
        int num_food;

        std::vector<Creature> creatures;
        std::vector<Food*> foods;



        Simulator(int num_creatures, int num_food);
        void run(int num_ticks);
         
    
};


Simulator::Simulator(int nc, int nf) : num_creatures(nc), num_food(nf) {
    // randomly assign position and direction
    for (int i = 0; i < num_creatures; i++) {
        double dir[2];
        double pos[2];
        random_unit_direction(dir);
        random_pos(pos);
        creatures.push_back(Creature(pos, dir));
    }
    // randomly assign position
    for (int i = 0; i < num_food; i++) {
        double pos[2];
        random_pos(pos);
    }
}


void Simulator::run(int num_ticks) {
    for (int i = 0; i < num_ticks; i++) {

        for (int i = 0; i < creatures.size(); i++) {
            creatures[i].update();
        }


    }
}


Creature::Creature(double* pos, double* direction, 
                    double sr, double er, double speed) : 
sense_radius(sr), eat_radius(er), speed(speed) {
    this->pos[0] = pos[0]; this->pos[1] = pos[1];
    this->direction[0] = direction[0]; this->direction[1] = direction[1];
    steps_left = 30;
}
                    
void Creature::update() {

    if (steps_left > 0) {
        steps_left--;
        pos[0] += speed * direction[0];
        pos[1] += speed * direction[1];
    }
    else {
        steps_left = 30;
        random_unit_direction(direction);  
        pos[0] += speed * direction[0];
        pos[1] += speed * direction[1];
    }

    double x = pos[0]; double y = pos[1];

    if (x < 0) pos[0] = 0;
    else if (x > WIDTH) pos[0] = WIDTH;
    if (y < 0) pos[1] = 0;
    else if (y > HEIGHT) pos[1] = HEIGHT;

    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) {
        steps_left = 30;
        random_unit_direction(direction);
    }

}




int main(int argc, char** argv) {
    initialize_randomness();

    int num_food = 0;
    int num_creatures = 100;
    Simulator sim(num_creatures, num_food);

    sim.run(1000);


    return 0;
}