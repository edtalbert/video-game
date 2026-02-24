#include "character.h"
#include "mediaManager.hpp"
#include <iostream>

Character::Character(SDL_Renderer* renderer, MediaManager& mm,
                     const char* bmpName,
                     int x, int y,
                     int screenWidth, int screenHeight)
{
    charText = mm.read(renderer, bmpName, src.w, src.h);

    screenW = screenWidth;
    screenH = screenHeight;

    src = {0, 0, 32, 32};

    worldX = x;
    worldY = y;
}

void Character::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_a: worldX -= 10; break;
            case SDLK_d: worldX += 10; break;
            case SDLK_w: worldY -= 10; break;
            case SDLK_s: worldY += 10; break;
        }
    }
}

void Character::update() {
    // Optional world wrapping example
    if (worldX < 0) worldX = 2000;
    if (worldY < 0) worldY = 2000;
}

void Character::render(SDL_Renderer* renderer,
                       int cameraX,
                       int cameraY)
{
    SDL_Rect screenRect;

    screenRect.w = 128;
    screenRect.h = 128;

    // Convert world position to screen position
    screenRect.x = worldX - cameraX;
    screenRect.y = worldY - cameraY;

    SDL_RenderCopy(renderer, charText, &src, &screenRect);
}

void Character::stats(){
    int health = 10;
    float speed = 1;
    float damage = 1;
    int damage_reduction = 0;
}