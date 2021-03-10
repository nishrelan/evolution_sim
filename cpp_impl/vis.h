#include "SDL2/SDL.h"
#include <stdio.h>
#include <vector>
#include "actors.h"

struct Drawable;

class Visualizer {
    public:
        Visualizer();
        ~Visualizer();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handle_events();
        void update(std::vector<Food>* foods, std::vector<Creature>* creatures);
        void render();
        void clean();
        bool is_running;

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::vector<SDL_Rect> food_rects;
        std::vector<Drawable> creature_rects;


};

struct Drawable {
    public:
        SDL_Rect rect;
        int r; int g; int b;
};


/*
class Drawable {
    public:
        SDL_Rect rect;
        int r;
        int g;
        int b;
        Drawable(SDL_Rect rect, int red, int blue, int green) 
            : rect(rect), r(red), g(green) {}
};
*/