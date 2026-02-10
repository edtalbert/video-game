#include "character.h"
#include <iostream>

Character::Character(SDL_Renderer* renderer,
                     const char* imagePath,
                     int x, int y,
                     int screenWidth, int screenHeight)
{
    screenW = screenWidth;
    screenH = screenHeight;

    SDL_Surface* surface = SDL_LoadBMP(imagePath);
    if (!surface) {
        std::cout << "Could not read burger bmp file: "
                  << SDL_GetError() << std::endl;
        texture = nullptr;
        return;
    }

    // Make black (0,0,0) transparent
    SDL_SetColorKey(
        surface,
        SDL_TRUE,
        SDL_MapRGB(surface->format, 0, 0, 0)
    );

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    src = {0, 0, 32, 32};
    dst = {x, y, 128, 128};
}


Character::~Character() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Character::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_a: dst.x--; break;
            case SDLK_d: dst.x++; break;
            case SDLK_w: dst.y--; break;
            case SDLK_s: dst.y++; break;
        }
    }
}

void Character::update() {
    if (dst.x < 0) dst.x = screenW - dst.w;
    if (dst.x > screenW) dst.x = 0;
    if (dst.y < 0) dst.y = screenH - dst.h;
    if (dst.y > screenH) dst.y = 0;
}

void Character::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Character::stats(){
    int health =10;
    float speed =1;
    float damage=1;
    int damage_reduction=0;
}