#include "levelstate.h"

LevelState::LevelState(SDL_Renderer* r,
                       MediaManager& mm,
                       int w,
                       int h)
    : renderer(r),
      media(mm),
      screenWidth(w),
      screenHeight(h),
      player(r, mm,
             "images/characters/burger/burger.bmp",
             w / 2,
             h / 2,
             w, h)
{
    cameraX = 0;
    cameraY = 0;
}

void LevelState::handleEvent(const SDL_Event& e) {
    player.handleEvent(e);
}

void LevelState::update(float deltaTime) {

    player.update();

    // Center camera on player
    cameraX = player.getWorldX() - screenWidth / 2;
    cameraY = player.getWorldY() - screenHeight / 2;
}

void LevelState::render(SDL_Renderer* renderer) {

    // Example background (large world)
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_Rect worldRect = { -cameraX, -cameraY, 2000, 2000 };
    SDL_RenderFillRect(renderer, &worldRect);

    player.render(renderer, cameraX, cameraY);
}