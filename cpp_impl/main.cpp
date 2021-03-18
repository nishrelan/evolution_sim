#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include <SDL2/SDL.h>
#include "sim.h"
#include "actors.h"
#include "utils.h"
#include "vis.h"



void run_simulation(Simulator* sim, Visualizer* vis, int nticks, int fps) {
   int frame_delay = 1000 / fps;

   Uint32 frame_start;
   int frame_time;

   for (int i = 0; i < nticks; i++) {
      if (vis->is_running) {

         frame_start = SDL_GetTicks();


         vis->handle_events();
         vis->update(&(sim->foods), &(sim->creatures));
         vis->render();

         frame_time = SDL_GetTicks() - frame_start;
         if (frame_delay > frame_time) SDL_Delay(frame_delay - frame_time);
         sim->update();
      }
      else {
         std::cout << "graphics error" << std::endl;
         break;
      }

   }
}

void run_simulation(Simulator* sim, int nticks) {
   for (int i = 0; i < nticks; i++) {
      sim->update();
   }
}

double average_speed(Simulator* sim) {
   double average = 0;
   for (int i = 0; i < sim->creatures.size(); i++) {
      average += sim->creatures[i].speed;
   }
   return average/(sim->creatures.size());
}

int main(int argc, char** argv) {

   initialize_randomness();
   Visualizer vis = Visualizer();
   Simulator sim = Simulator(6, 100);
   
   vis.init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   int nticks = 500000;
   int fps = 60;

  


   run_simulation(&sim, &vis, nticks, fps);

   int num_red = 0; int num_blue = 0; int num_green = 0;
   for (int i = 0; i < sim.creatures.size(); i++) {
      int type = sim.creatures[i].type;
      if (type == 1) num_red++;
      else if (type == 2) num_blue++;
      else num_green++;
   }

   std::cout << "Number of greens: " << num_green << std::endl;
   std::cout << "Number of blues: " << num_blue << std::endl;
   std::cout << "Number of reds: " << num_red << std::endl;
   

}