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


int main(int argc, char** argv) {

   initialize_randomness();
   Visualizer vis = Visualizer();
   Simulator sim = Simulator(50, 300);
   
   vis.init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   int nticks = 5000;
   int fps = 60;


   run_simulation(&sim, &vis, nticks, fps);
   std::cout << sim.creatures.size() << std::endl;
   

}