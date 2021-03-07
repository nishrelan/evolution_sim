#include "SDL2/SDL.h"
#include <stdio.h>


class Visualizer {
    public:
        Visualizer();
        ~Visualizer();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handle_events();
        void update();
        void render();
        void clean();
        bool is_running;

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

};