#include <SDL.h>
#include "menustate.h"
#include "character.h"
#include <iostream>
#include <memory>

using namespace std;

int error(string s){
    cerr << s << SDL_GetError()<<endl;
    return -1;
}


//test

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

int main(int argc, char* args[]) {
    cout << "Arg 0 " << args[0]<< endl;
    cout << "Arg 1 " << args[1]<< endl;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int retval=init(window,renderer,640,480);
    if (retval!=0) return retval;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Gray color
    
    bool quit = false;

    // current game state
    std::unique_ptr<GameState> currentState = std::make_unique<MenuState>(renderer);

    SDL_Event e;
    int rcount=0;
    int bcount=0;
    // Character will be created from its own constructor below

    SDL_Surface* title;
    title=SDL_LoadBMP("Title.bmp");
    if (title==NULL) return error("Could not read title.bmp file");
    SDL_Texture* titleText;
    titleText=SDL_CreateTextureFromSurface(renderer,title);
    if(titleText==NULL) return error("Failed to create texture");
    SDL_FreeSurface(title);

    // Create player using the Character class (it will load burger.bmp)
    Character player(renderer, "burger.bmp", 0, 0, 640, 480);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)  { quit = true; continue; }

            // toggle menu with M key
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m) {
                if (!currentState || dynamic_cast<MenuState*>(currentState.get()) == nullptr) {
                    currentState = std::make_unique<MenuState>(renderer); // open menu
                } else {
                    currentState.reset(); // close menu
                }
                continue; // skip further handling for this event
            }

            // If the menu is open, forward the event only to the menu and skip gameplay input
            if (currentState && dynamic_cast<MenuState*>(currentState.get()) != nullptr) {
                currentState->handleEvent(e);
                continue;
            }

            // Gameplay input (only when menu is not open) -> forward to player
            if (e.type == SDL_KEYDOWN) {
                player.handleEvent(e);
            }

            // forward event to current state as well (e.g., gameplay state)
            if (currentState) currentState->handleEvent(e);
        }
        // update player (handles wrapping/clamping internally)
        player.update();

        // Clear the screen every frame to avoid sprite trails
        SDL_SetRenderDrawColor(renderer, rcount, 0, bcount, 255);
        SDL_RenderClear(renderer);

        // Let the current state update/render
        if (currentState) {
            currentState->update(0.0f);
            currentState->render(renderer);
        }

        // If the menu is open, draw the title texture on top of the state's rendering
        if (currentState && dynamic_cast<MenuState*>(currentState.get()) != nullptr) {
            int tw = 0, th = 0;
            SDL_QueryTexture(titleText, NULL, NULL, &tw, &th);
            SDL_Rect titleDst;
            titleDst.w = tw; titleDst.h = th;
            // Center near the top — tweak as needed
            titleDst.x = (640 - titleDst.w) / 2;
            titleDst.y = 20;
            SDL_RenderCopy(renderer, titleText, NULL, &titleDst);
        }

        // draw the character on top via Character
        player.render(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/240);
    }
    cleanup(window,renderer);
    return 0;
}
