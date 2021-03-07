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






int main(int argc, char** argv) {

   Visualizer vis = Visualizer();
   
   vis.init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   while (vis.is_running) {
      vis.handle_events();
      vis.update();
      vis.render();
   }
   vis.clean();

}