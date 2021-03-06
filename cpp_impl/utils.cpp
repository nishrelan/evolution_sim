#include "utils.h"

const double HEIGHT = 600;
const double WIDTH = 600;
std::random_device rd; // truly random 
std::mt19937 mt; // prng

// uniform distributions
std::uniform_real_distribution<double>  dist; 
std::uniform_real_distribution<double> width; 
std::uniform_real_distribution<double> height; 


void initialize_randomness() {



    mt.seed(0); // For replicable results

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