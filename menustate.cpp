#include "menustate.h"

MenuState::MenuState(SDL_Renderer* renderer)
    : selectedIndex(0), renderer_(renderer) {
    std::cout << "MenuState constructor called" << std::endl;
}

MenuState::~MenuState() {
    std::cout << "MenuState destructor called" << std::endl;
}

void MenuState::update(float /*deltaTime*/) {
    // menu logic would go here (e.g., animations)
}

void MenuState::render(SDL_Renderer* renderer) {
    if (!renderer) return;

    // Example: draw a simple menu panel in the middle of the screen
    SDL_Rect panel;
    panel.w = 400;
    panel.h = 300;
    panel.x = (1280 - panel.w) / 2;  // you can make these configurable
    panel.y = (720  - panel.h) / 2;

    // Draw a solid rectangle (no clear)
    SDL_SetRenderDrawColor(renderer, 50, 50, 100, 255);
    SDL_RenderFillRect(renderer, &panel);

    // You can later draw text or options inside here
}

void MenuState::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:    selectedIndex--; break;
            case SDLK_DOWN:  selectedIndex++; break;
            case SDLK_RETURN:
                // in a real game, you'd trigger an action here
                break;
            default: break;
        }
    }
}