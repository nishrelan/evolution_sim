#include "actors.h"
#include "utils.h"
#include "sim.h"





Creature::Creature(double* pos, double* direction, 
                    double sr, double er, double speed) : 
sense_radius(sr), eat_radius(er), speed(speed) {
    this->pos[0] = pos[0]; this->pos[1] = pos[1];
    this->direction[0] = direction[0]; this->direction[1] = direction[1];
    steps_left = 60;
    energy = INITIAL_ENERGY;
    is_dead = false;
    time_till_procreate = PROCREATION_TIME;
}


void Creature::continue_random_movement() {
    if (steps_left > 0) {
        steps_left--;
    }
    else {
        steps_left = 60;
        random_unit_direction(direction);  
    }
}

void Creature::update() {

    // eat food within eat radius if possible
    if (sim->attempt_eat_food(pos, eat_radius))
        energy += ENERGY_FROM_FOOD;


    // orient direction towards food if food within sense radius
    double food_pos[2] = {-1., -1.};
    bool found_food = sim->find_food_in_radius(pos, food_pos, sense_radius);
    if (found_food) orient_towards(food_pos, pos, direction);
    else continue_random_movement();

    // move
    pos[0] += speed*direction[0];
    pos[1] += speed*direction[1];
    energy -= (0.5 + speed*speed/5. + sense_radius/100);
    time_till_procreate--;
    if (energy <= 0) {
        is_dead = true;
        return;
    }

    double x = pos[0]; double y = pos[1];

    if (x < 0) pos[0] = 0;
    else if (x > WIDTH) pos[0] = WIDTH;
    if (y < 0) pos[1] = 0;
    else if (y > HEIGHT) pos[1] = HEIGHT;

    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) {
        steps_left = 60;
        random_unit_direction(direction);
    }

    // make a baby if possible
    if (energy >= 500 && time_till_procreate <= 0) {
        // baby spawns at same position but in random direction
        double baby_dir[2];
        random_unit_direction(baby_dir);
        Creature c(pos, baby_dir);
        if (type == 3 || type == 2) {
            c.speed = speed + (norm_rand() / 5);
            c.speed = c.speed < 0.1 ? 0.1 : c.speed;
        }
        if (type == 3 || type == 1) {
            c.sense_radius = sense_radius + (norm_rand() * 3);
            c.sense_radius = c.sense_radius < 0 ? 0 : c.sense_radius;
        }
        
        c.sim = sim;
        c.type = type;
        sim->make_baby(&c);
        time_till_procreate = PROCREATION_TIME;
    }
}