#ifndef UTILS_H
#define UTILS_H

#include <random>

extern const double WIDTH;
extern const double HEIGHT;


extern std::random_device rd; // truly random 
extern std::mt19937 mt; // prng

// uniform distributions
extern std::uniform_real_distribution<double>  dist; 
extern std::uniform_real_distribution<double> width; 
extern std::uniform_real_distribution<double> height;




void initialize_randomness();

double uniform_rand();

double width_rand();
double height_rand();

void normalize(double* v);

void random_unit_direction(double* v);

void random_pos(double* v);

double distance(double* x, double* y);

void orient_towards(double* food_pos, double* pos, double* direction);
#endif