#include "menustate.h"

MenuState::MenuState(SDL_Renderer* renderer)
    : selectedIndex(0), renderer_(renderer) {
    std::cout << "MenuState constructor called" << std::endl;
}

MenuState::~MenuState() {
    std::cout << "MenuState destructor called" << std::endl;
}

void MenuState::update(float /*deltaTime*/) {
    // menu logic would go here
}

void MenuState::render(SDL_Renderer* renderer) {
    // simple placeholder: clear to a color so we can see state rendering
    if (renderer) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 100, 255);
        SDL_RenderClear(renderer);
    }
}

void MenuState::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: selectedIndex--; break;
            case SDLK_DOWN: selectedIndex++; break;
            case SDLK_RETURN: /* trigger state change in a real game */ break;
            default: break;
        }
    }
}