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
#include <fstream>



void run_simulation(Simulator* sim, Visualizer* vis, int nticks, int fps) {
   int frame_delay = 1000 / fps;

   Uint32 frame_start;
   int frame_time;

   vis->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
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



void run_simulation(Simulator* sim, int nticks, int record, std::string filename) {
   std::string path = "results/";
   std::ofstream file(path + filename);

   for (int i = 0; i < nticks; i++) {
      sim->update();

      if (i % record == 0) {
         for (int j = 0; j < sim->creatures.size(); j++) {
            Creature* c = &(sim->creatures[j]);
            file << c->type << " " << c->speed << " " << c->sense_radius << " ";
         }
         file << std::endl;
      }

   }
   
   file.close();
}

int main(int argc, char** argv) {


   int nticks = 300000;
   int fps = 60;
   int num_creatures = 6;
   int num_food = 100;

   initialize_randomness();
   Visualizer vis = Visualizer();

   



   for (int i = 0; i < 5; i++) {
      Simulator sim(num_creatures, num_food);
      std::string filename = "more_iters";
      filename += std::to_string(i+1) + ".txt";
      run_simulation(&sim, nticks, 100, filename);
   }
  

   

}