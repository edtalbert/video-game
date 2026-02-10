#include <SDL.h>
#include "character.h"
#include <iostream>

using namespace std;

int error(string s){
    cerr << s << SDL_GetError()<<endl;
    return -1;
}

int init(SDL_Window* &window,SDL_Renderer* &renderer,int width,int height){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return error("SDL could not initialize! SDL_Error: "); 
    window = SDL_CreateWindow("Simple SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) return error("Window could not be created! SDL_Error:");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) return error("Renderer could not be created! SDL_Error:");
    return 0;
}

void cleanup(SDL_Window* &window,SDL_Renderer* &renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int res_width = 1280;
int res_height = 720;

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (init(window, renderer, res_width, res_height) != 0)
        return -1;

    bool quit = false;
    SDL_Event e;

    Character player(
        renderer,
        "images/characters/burger/burger.bmp",
        0, 0,
        res_width, res_height
    );

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;

            player.handleEvent(e);
        }

        player.update();

        SDL_SetRenderDrawColor(renderer, 65, 0, 150, 255);
        SDL_RenderClear(renderer);

        player.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 240);
    }

    cleanup(window, renderer);
    return 0;
}
