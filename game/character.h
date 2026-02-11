#pragma once
#include <SDL.h>

class Character {
private:
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dst;
    int screenW, screenH;

public:
    Character(SDL_Renderer* renderer,
              const char* imagePath,
              int x, int y,
              int screenWidth, int screenHeight);

    ~Character();

    void handleEvent(const SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);
    void stats();
};
