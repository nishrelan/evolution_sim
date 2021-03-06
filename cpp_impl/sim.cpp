#include "sim.h"
#include "utils.h"
#include "actors.h"

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