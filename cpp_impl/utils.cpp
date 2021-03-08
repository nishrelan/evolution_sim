#include "utils.h"
#include <iostream>

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

double distance(double* x, double* y) {
    double r1 = x[0] - y[0];
    double r2 = x[1] - y[1];
    return sqrt(r1*r1 + r2*r2);
}

// modify direction to point from pos to food_pos. normalize as well
void orient_towards(double* food_pos, double* pos, double* direction) {
    direction[0] = food_pos[0] - pos[0];
    direction[1] = food_pos[1] - pos[1];
    normalize(direction);
}