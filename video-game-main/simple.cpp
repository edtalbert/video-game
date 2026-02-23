#include <SDL.h>
#include "character.h"
#include "menustate.h"
#include "mediaManager.hpp"
#include <iostream>
#include <memory>
//#include <map>

using namespace std;

int error(string s){
    cerr << s << SDL_GetError() << endl;
    return -1;
}

int init(SDL_Window*& window, SDL_Renderer*& renderer, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        return error("SDL could not initialize! SDL_Error: ");

    window = SDL_CreateWindow("Simple SDL2 Example",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);

    if (!window)
        return error("Window could not be created! SDL_Error: ");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

    // Game State (menu system)
    std::unique_ptr<GameState> currentState = nullptr;

    /*
    // Load title texture
    SDL_Surface* titleSurface = SDL_LoadBMP("Title.bmp");
    if (!titleSurface) return error("Could not load Title.bmp: ");

    SDL_Texture* titleTexture =
        SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_FreeSurface(titleSurface);

    if (!titleTexture)
        return error("Failed to create title texture: ");
*/
    int titleW, titleH;
    SDL_Texture* titleTexture = mm.read(renderer,"images/title.bmp",titleW,titleH);

    // Create player
    Character player(
        renderer, mm,
        "images/characters/burger/burger.bmp",
        0, 0,
        res_width, res_height
    );

    while (!quit) {

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT)
                quit = true;

            // Toggle menu with M
            if (e.type == SDL_KEYDOWN &&
                e.key.keysym.sym == SDLK_m)
            {
                if (!currentState)
                    currentState = std::make_unique<MenuState>(renderer);
                else
                    currentState.reset();

                continue;
            }

            // If menu is open, send input only to menu
            if (currentState) {
                currentState->handleEvent(e);
                continue;
            }

            // Otherwise send to player
            player.handleEvent(e);
        }

        // Update
        if (!currentState)
            player.update();

        // Render
        SDL_SetRenderDrawColor(renderer, 65, 0, 150, 255);
        SDL_RenderClear(renderer);

        // Render gameplay (player always drawn)
        player.render(renderer);

        // Render menu on top if open
        if (currentState) {
            currentState->update(0.0f);
            currentState->render(renderer);

            // Draw title centered at top
            SDL_Rect dst;
            dst.w = titleW;
            dst.h = titleH;
            dst.x = (res_width - titleW) / 2;
            dst.y = 20;

            SDL_RenderCopy(renderer, titleTexture, NULL, &dst);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 240);
    }

    cleanup(window, renderer);
    return 0;
}
