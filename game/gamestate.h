#pragma once
#include <SDL.h>

class GameState {
public:
    virtual ~GameState() = default;

    // Called once per-frame with seconds elapsed since last frame
    virtual void update(float deltaTime) = 0;

    // Called to render the state
    virtual void render(SDL_Renderer* renderer) = 0;

    // Called for each incoming SDL event
    virtual void handleEvent(const SDL_Event& e) = 0;
};