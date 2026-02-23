#pragma once
#include <SDL.h>

class MediaManager;

class Character {
private:
    SDL_Texture* charText;
    SDL_Rect src;
    SDL_Rect dst;
    int screenW, screenH;

public:
    Character(SDL_Renderer* renderer, MediaManager& mm,
              const char* bmpName,
              int x, int y,
              int screenWidth, int screenHeight);

    //media manager should now handle this
    //~Character();

    void handleEvent(const SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);
    void stats();
};
