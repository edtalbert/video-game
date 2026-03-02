#pragma once
#include <SDL.h>
#include <filesystem>
class Mouse{
    //image of the mouse
    SDL_Texture * mouseText;
    //rectangle for the mouse
    SDL_Rect rect;
    public:
    //point rectangle for collision detection
    SDL_Rect point;
    
    Mouse(SDL_Renderer* renderer, const char* bmpName, MediaManager& mm){
        //size of mouse image
        rect.w = 32;
        rect.h = 32;
        //size of point for collision detection
        point.w = 1;
        point.h = 1;
        
        //create mouse texture with error handling
        try{
            mouseText = mm.read(renderer, bmpName, rect.w,rect.h);
        } catch (const char* msg) {
            std::cerr << "Exception: " << msg << std::endl;
        }

    }
    //update mouse position
    void update() {
        //get mouse position
        SDL_GetMouseState(&rect.x, &rect.y);
        //update point position for collision detection
        point.x = rect.x;
        point.y = rect.y;

        
    }
    //render mouse
    void draw(SDL_Renderer* renderer){
        SDL_RenderCopy(renderer, mouseText, NULL, &rect);
    }

};