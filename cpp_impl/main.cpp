#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include <SDL2/SDL.h>
#include "sim.h"
#include "actors.h"
#include "utils.h"






int main(int argc, char** argv) {

    initialize_randomness();
    int n = 50;
    if (argc > 1) {
        n = std::stoi(argv[1]);
    }    
    Simulator sim(n, n);
    sim.run(5);
    return 0;
}