#pragma once
#include "gamestate.h"
#include <SDL.h>
#include <iostream>

class MenuState : public GameState {
public:
    explicit MenuState(SDL_Renderer* renderer);
    ~MenuState() override;

    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;

private:
    int selectedIndex = 0;
    SDL_Renderer* renderer_ = nullptr;
};