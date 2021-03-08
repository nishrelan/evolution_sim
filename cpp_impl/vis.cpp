#include "vis.h"
#include <iostream>


Visualizer::Visualizer() {}

Visualizer::~Visualizer() {}

void Visualizer::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error" << std::endl;
        is_running = false;
    }
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (!window) {
        std::cout << "SDL_CreateWindow Error" << std::endl;
        is_running = false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cout << "SDL_CreateRenderer Error" << std::endl;
        is_running = false;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    is_running = true;
}

void Visualizer::handle_events() {
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type){
    case SDL_QUIT:
        is_running = false;
        break;
    default:
        break;
    }
}

void Visualizer::update(std::vector<Food>* foods, std::vector<Creature>* creatures) {
    food_rects.resize(foods->size());
    creature_rects.resize(creatures->size());

    for (int i = 0; i < foods->size(); i++) {
        SDL_Rect r;
        r.h = 5; r.w = 5;
        r.x = foods->at(i).pos[0];
        r.y = foods->at(i).pos[1];
        food_rects[i] = r;
    }

    for (int i = 0; i < creatures->size(); i++) {
        SDL_Rect r;
        r.h = 6; r.w = 6;
        r.x = creatures->at(i).pos[0];
        r.y = creatures->at(i).pos[1];
        creature_rects[i] = r;
    }
}

void Visualizer::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // draw stuff on screen



    // draw food and creatures
    for (int i = 0; i < food_rects.size(); i++) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(renderer, &food_rects[i]);
    }
    for (int i = 0; i < creature_rects.size(); i++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &creature_rects[i]);
    }


    SDL_RenderPresent(renderer);
}

void Visualizer::clean() {
    SDL_DestroyWindow(window); 
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

}

