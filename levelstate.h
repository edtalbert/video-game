#pragma once
#include "gamestate.h"
#include "character.h"
#include "mediaManager.hpp"

class LevelState : public GameState {
public:
    LevelState(SDL_Renderer* renderer,
               MediaManager& mm,
               int screenW,
               int screenH);

    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& e) override;

private:
    SDL_Renderer* renderer;
    MediaManager& media;

    Character player;

    int screenWidth;
    int screenHeight;

    int cameraX;
    int cameraY;
};