#include "actors.h"
#include "utils.h"

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