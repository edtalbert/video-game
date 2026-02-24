#include <SDL.h>
#include "levelstate.h"
#include "mediaManager.hpp"
#include <iostream>
#include <memory>

using namespace std;

int error(string s){
    cerr << s << SDL_GetError() << endl;
    return -1;
}

int init(SDL_Window*& window, SDL_Renderer*& renderer,
         int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        return error("SDL could not initialize! SDL_Error: ");

    window = SDL_CreateWindow("SDL Level System",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);

    if (!window)
        return error("Window could not be created! SDL_Error: ");

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED);

    if (!renderer)
        return error("Renderer could not be created! SDL_Error: ");

    return 0;
}

void cleanup(SDL_Window*& window, SDL_Renderer*& renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

MediaManager mm;

int res_width = 1280;
int res_height = 720;

int main(int argc, char* args[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (init(window, renderer, res_width, res_height) != 0)
        return -1;

    bool quit = false;
    SDL_Event e;

    std::unique_ptr<GameState> currentState =
        std::make_unique<LevelState>(renderer,
                                     mm,
                                     res_width,
                                     res_height);

    while (!quit) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;

            currentState->handleEvent(e);
        }

        currentState->update(0.016f);

        SDL_SetRenderDrawColor(renderer, 65, 0, 150, 255);
        SDL_RenderClear(renderer);

        currentState->render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    cleanup(window, renderer);
    return 0;
}