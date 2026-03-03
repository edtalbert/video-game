#pragma once
#include <SDL.h>
#include <functional>
#include "mouse.hpp"

class Button {
    private:
    //not yet used but could be for animations
    bool hovered;
    
    //each button can have an associated action stored in onClick
    //initialized via constructor parameter
    std::function<void()> onClick;
    public:
    Button(SDL_Renderer* renderer, MediaManager& mm,
              const char* bmpName, int newX,
              int newY, int newW, int newH,
              std::function<void()> callback = nullptr) {
        std::cerr << "Button constructor called for: " << bmpName << std::endl;
          dstrect.x = newX;
          dstrect.y = newY;
          dstrect.w = newW;
          dstrect.h = newH;
          
          buttonText = mm.read(renderer, bmpName, dstrect.w, dstrect.h);
          onClick = callback;
          hovered = false;
    }
    void update(Mouse& mouse){
        if(SDL_HasIntersection(&dstrect, &mouse.point)){
            hovered = true;
        } else {
            hovered = false;
        }
           
    }
    
    void handleEvent(const SDL_Event& e){
        if(e.type == SDL_MOUSEBUTTONDOWN && hovered && onClick) {
            onClick();
        }
    }
    void render(SDL_Renderer* renderer ){
        SDL_RenderCopy(renderer, buttonText, NULL, &dstrect);
    }
    public:
    SDL_Rect dstrect, srcrect;
    SDL_Texture* buttonText;
};