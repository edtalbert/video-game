#include <SDL.h>
#include <iostream>
#include <memory>

#include "levelstate.h"
#include "menustate.h"
#include "mediaManager.hpp"
#include "button.hpp"

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

    window = SDL_CreateWindow("SDL Level + Menu Overlay",
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

// global MediaManager (same as before)
MediaManager mm;

int res_width  = 1280;
int res_height = 720;

int main(int argc, char* args[]) {

    SDL_Window* window    = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (init(window, renderer, res_width, res_height) != 0)
        return -1;

    bool quit = false;
    SDL_Event e;

    // Gameplay state: always exists
    std::unique_ptr<LevelState> levelState =
        std::make_unique<LevelState>(renderer,
                                     mm,
                                     res_width,
                                     res_height);

    // Menu overlay: exists only when open
    std::unique_ptr<MenuState> menuState = nullptr;

    // 🔹 Load title texture once (for menu header)
    int titleW = 0;
    int titleH = 0;
    SDL_Texture* titleTexture =
        mm.read(renderer, "images/title.bmp", titleW, titleH);

    while (!quit) {

        // --- EVENT LOOP ---
        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT) {
                quit = true;
                continue;
            }

            // Toggle menu with M
            if (e.type == SDL_KEYDOWN &&
                e.key.keysym.sym == SDLK_m)
            {
                if (!menuState) {
                    // open menu overlay
                    menuState = std::make_unique<MenuState>(renderer);
                } else {
                    // close menu overlay
                    menuState.reset();
                }
                continue; // don't forward this event further
            }

            // If menu is open, it eats the input
            if (menuState) {
                menuState->handleEvent(e);
            } else {
                levelState->handleEvent(e);
            }
        }

        // --- UPDATE ---
        if (!menuState) {
            // game runs only when menu is closed
            levelState->update(0.016f);
        } else {
            // optional: update menu, but not game
            menuState->update(0.016f);
        }

        // --- RENDER ---
        SDL_SetRenderDrawColor(renderer, 65, 0, 150, 255);
        SDL_RenderClear(renderer);

        // Always draw the level first
        levelState->render(renderer);

        // If menu is open, draw it on top + title image
        if (menuState) {
            // Draw the menu overlay (panel, etc.)
            menuState->render(renderer);

            // 🔹 Draw the title centered at the top of the screen
            if (titleTexture) {
                SDL_Rect dst;
                dst.w = titleW;
                dst.h = titleH;
                dst.x = (res_width - titleW) / 2;
                dst.y = 20;   // distance from top

                SDL_RenderCopy(renderer, titleTexture, nullptr, &dst);

                
            }

            Button button1(renderer, mm, "images/characters/burger/burger.bmp", 0, 0, 32, 32 );
            SDL_RenderCopy(renderer, button1.buttonText, nullptr, &button1.rect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    cleanup(window, renderer);
    return 0;
}