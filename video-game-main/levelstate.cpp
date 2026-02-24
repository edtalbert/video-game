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
             w, h),
      tileMap(r, mm, "images/tiles/tileset.bmp", 32, 32)
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
    cameraX = player.getWorldX() - screenWidth  / 2;
    cameraY = player.getWorldY() - screenHeight / 2;

    // Optional: clamp camera so you don’t scroll past edge of map
    int maxCamX = tileMap.getWidthInTiles()  * tileMap.getTileSize() - screenWidth;
    int maxCamY = tileMap.getHeightInTiles() * tileMap.getTileSize() - screenHeight;

    if (cameraX < 0) cameraX = 0;
    if (cameraY < 0) cameraY = 0;

    if (cameraX > maxCamX) cameraX = maxCamX;
    if (cameraY > maxCamY) cameraY = maxCamY;
}

void LevelState::render(SDL_Renderer* renderer) {

    // 1) Draw the tilemap (big textured world)
    tileMap.render(renderer, cameraX, cameraY,
                   screenWidth, screenHeight);

    // 2) Draw the player on top
    player.render(renderer);
}