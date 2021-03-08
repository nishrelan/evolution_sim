#include "sim.h"
#include "utils.h"
#include "actors.h"
#include <iostream>
#include <algorithm>

Simulator::Simulator(int nc, int nf) : num_creatures(nc), num_food(nf) {
    // randomly assign position and direction
    for (int i = 0; i < num_creatures; i++) {
        double dir[2];
        double pos[2];
        random_unit_direction(dir);
        random_pos(pos);
        Creature c = Creature(pos, dir);
        c.sim = this;
        creatures.push_back(c);
    }
    // randomly assign position
    for (int i = 0; i < num_food; i++) {
        double pos[2];
        random_pos(pos);
        foods.push_back(Food(pos));
    }
}


void Simulator::run(int num_ticks) {
    for (int i = 0; i < num_ticks; i++) {

        for (int i = 0; i < creatures.size(); i++) {
            creatures[i].update();
        }

    }
}



void Simulator::update() {
    for (int i = 0; i < creatures.size(); i++) {
            creatures[i].update();
        }

    // remove dead creatures
    creatures.erase(std::remove_if(creatures.begin(), creatures.end(), 
    [](Creature & c) {return c.is_dead; }
    ), creatures.end());
}


bool Simulator::attempt_eat_food(double* pos, double eat_radius) {
    int remove_idx = -1;
    for (int i = 0; i < foods.size(); i++) {
        if (distance(pos, foods[i].pos) < eat_radius) {
            remove_idx = i;
            break;
        }
    }

    if (remove_idx != -1) foods.erase(foods.begin() + remove_idx);
    return remove_idx == -1 ? false : true;
}

bool Simulator::find_food_in_radius(double* pos, double* food_pos, double sense_radius) {
    for (int i = 0; i < foods.size(); i++) {
        if (distance(pos, foods[i].pos) < sense_radius) {
            food_pos[0] = foods[i].pos[0];
            food_pos[1] = foods[i].pos[1];
            return true;
        }
    }
    return false;
}