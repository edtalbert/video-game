#pragma once
#include <SDL.h>

class MediaManager;

class Character {
private:
    SDL_Texture* charText;

    SDL_Rect src;          // portion of texture
    int worldX, worldY;    // position in world space

    int screenW, screenH;  // screen dimensions

public:
    Character(SDL_Renderer* renderer, MediaManager& mm,
              const char* bmpName,
              int x, int y,
              int screenWidth, int screenHeight);

    void handleEvent(const SDL_Event& e);
    void update();

    // NEW: render now uses camera offset
    void render(SDL_Renderer* renderer,
                int cameraX,
                int cameraY);

    void stats();

    // Needed for camera centering
    int getWorldX() const { return worldX; }
    int getWorldY() const { return worldY; }
};