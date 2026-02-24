#pragma once
#include <SDL.h>

class MediaManager;

class Character {
private:
    SDL_Texture* charText;

    SDL_Rect src;          // portion of texture
    int worldX, worldY;    // position in world space

    int screenW, screenH;  // screen dimensions
    int spriteW = 128;
    int spriteH = 128;

public:
    Character(SDL_Renderer* renderer, MediaManager& mm,
              const char* bmpName,
              int x, int y,
              int screenWidth, int screenHeight);

    void handleEvent(const SDL_Event& e);
    void update();

    void render(SDL_Renderer* renderer);

    void stats();

    int getWorldX() const { return worldX; }
    int getWorldY() const { return worldY; }
};