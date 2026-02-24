#pragma once
#include <SDL.h>
#include <functional>

class Button {
    private:
    
    
    bool hovered;
    bool pressed;
    public:
    Button(SDL_Renderer* renderer, MediaManager& mm,
                     const char* bmpName, int newX,
                    int newY, int newW, int newH ){
        
        rect.w = newW;
        rect.h = newH;
        rect.x = newX;
        rect.y = newY;
        buttonText = mm.read(renderer, bmpName, rect.w, rect.h);
    }
    void handleEvent(const SDL_Event& e){
        if(e.type == SDL_MOUSEMOTION) {
            //get the pososition of mouse when MOUSEMOTION event is triggered
            int mx = e.motion.x, my = e.motion.y;
            //if mx and my is touching button then make hovered==true

        }


    }
    void render(SDL_Renderer* renderer ){
        SDL_RenderCopy(renderer, buttonText, NULL, &rect);
    }
    public:
    SDL_Rect rect;
    SDL_Texture* buttonText;
};