#pragma once

#include <SDL.h>
#include "mediaManager.hpp"

class Character {
private:
  SDL_Texture* charText;
  SDL_Rect src;
  int worldX;
  int worldY;
  int screenW;
  int screenH;
  int spriteW;
  int spriteH;

public:
  Character(SDL_Renderer* renderer, MediaManager& mm,
            const char* bmpName,
            int x, int y,
            int screenWidth, int screenHeight)
      : charText(nullptr),
        src{0, 0, 32, 32},
        worldX(x),
        worldY(y),
        screenW(screenWidth),
        screenH(screenHeight),
        spriteW(128),
        spriteH(128) {
    charText = mm.read(renderer, bmpName, src.w, src.h);
  }

  void handleEvent(SDL_Keycode symbol) {
    switch (symbol) {
      case SDLK_a: worldX -= 10; break;
      case SDLK_d: worldX += 10; break;
      case SDLK_w: worldY -= 10; break;
      case SDLK_s: worldY += 10; break;
      default: break;
    }
  }

  void moveBy(int dx, int dy) {
    worldX += dx;
    worldY += dy;
  }

  void update() {
    if (worldX < 0) worldX = 0;
    if (worldY < 0) worldY = 0;
  }

  void clampToWorld(int minX, int maxX, int minY, int maxY) {
    if (worldX < minX) worldX = minX;
    if (worldX > maxX) worldX = maxX;
    if (worldY < minY) worldY = minY;
    if (worldY > maxY) worldY = maxY;
  }

  void render(SDL_Renderer* renderer) {
    if (!renderer || !charText) return;
    SDL_Rect screenRect;
    screenRect.w = spriteW;
    screenRect.h = spriteH;
    screenRect.x = (screenW - screenRect.w) / 2;
    screenRect.y = (screenH - screenRect.h) / 2;
    SDL_RenderCopy(renderer, charText, &src, &screenRect);
  }

  int getWorldX() const { return worldX; }
  int getWorldY() const { return worldY; }
};
