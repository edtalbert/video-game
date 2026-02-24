#include "character.h"
#include "mediaManager.hpp"
#include <iostream>

Character::Character(SDL_Renderer* renderer, MediaManager& mm,
                     const char* bmpName,
                     int x, int y,
                     int screenWidth, int screenHeight)
{
    // Load texture via MediaManager
    charText = mm.read(renderer, bmpName, src.w, src.h);

    screenW = screenWidth;
    screenH = screenHeight;

    // Source rectangle (portion of sprite sheet to use)
    src = {0, 0, 32, 32};

    // World position (logical position in the level)
    worldX = x;
    worldY = y;
}

void Character::handleEvent(const SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_a: worldX -= 10; break;
            case SDLK_d: worldX += 10; break;
            case SDLK_w: worldY -= 10; break;
            case SDLK_s: worldY += 10; break;
            default: break;
        }
        std::cout << "Player world pos: (" << worldX
                  << ", " << worldY << ")\n";
    }
}

void Character::update()
{
    // Optional world wrapping example
    if (worldX < 0) worldX = 2000;
    if (worldY < 0) worldY = 2000;
}

void Character::render(SDL_Renderer* renderer)
{
    if (!renderer || !charText) return;

    SDL_Rect screenRect;

    screenRect.w = 128;
    screenRect.h = 128;

    // Always draw in the center of the screen
    screenRect.x = (screenW - screenRect.w) / 2;
    screenRect.y = (screenH - screenRect.h) / 2;

    SDL_RenderCopy(renderer, charText, &src, &screenRect);
}

void Character::stats()
{
    int health = 10;
    float speed = 1;
    float damage = 1;
    int damage_reduction = 0;
}