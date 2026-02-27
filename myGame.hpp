#pragma once

#include "character.hpp"
#include "tileMap.hpp"

const int WIDTH=1280;
const int HEIGHT=720;

class MyGame:public Game{
    Character* player;
    TileMap* tileMap;
    SDL_Texture* titleTexture;
    int titleW;
    int titleH;
    int cameraX;
    int cameraY;
    int worldW;
    int worldH;
    bool menuOpen;
    int selectedIndex;

    void setup() override {
        tileMap = new TileMap(renderer, mm, "images/tiles/tileset.bmp", 32, 32);
        worldW = tileMap->getWidthInTiles() * tileMap->getTileSize();
        worldH = tileMap->getHeightInTiles() * tileMap->getTileSize();

        player = new Character(renderer, mm,
                               "images/characters/burger/burger.bmp",
                               worldW / 2, worldH / 2, WIDTH, HEIGHT);
        titleTexture = mm.read(renderer, "images/Title.bmp", titleW, titleH);
    }

    void update(float dt) override {
        if (menuOpen) return;

        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        int moveStep = static_cast<int>(400.0f * dt);
        if (moveStep < 1) moveStep = 1;
        int dx = 0;
        int dy = 0;
        if (keys[SDL_SCANCODE_A]) dx -= moveStep;
        if (keys[SDL_SCANCODE_D]) dx += moveStep;
        if (keys[SDL_SCANCODE_W]) dy -= moveStep;
        if (keys[SDL_SCANCODE_S]) dy += moveStep;
        player->moveBy(dx, dy);
        player->update();
        int halfScreenW = WIDTH / 2;
        int halfScreenH = HEIGHT / 2;
        int minPlayerX = halfScreenW;
        int minPlayerY = halfScreenH;
        int maxPlayerX = worldW - halfScreenW;
        int maxPlayerY = worldH - halfScreenH;

        // Handle tiny maps safely (map smaller than screen in a dimension).
        if (maxPlayerX < minPlayerX) minPlayerX = maxPlayerX = worldW / 2;
        if (maxPlayerY < minPlayerY) minPlayerY = maxPlayerY = worldH / 2;

        player->clampToWorld(minPlayerX, maxPlayerX, minPlayerY, maxPlayerY);

        cameraX = player->getWorldX() - WIDTH / 2;
        cameraY = player->getWorldY() - HEIGHT / 2;

        int maxCamX = tileMap->getWidthInTiles()  * tileMap->getTileSize() - WIDTH;
        int maxCamY = tileMap->getHeightInTiles() * tileMap->getTileSize() - HEIGHT;
        if (maxCamX < 0) maxCamX = 0;
        if (maxCamY < 0) maxCamY = 0;

        if (cameraX < 0) cameraX = 0;
        if (cameraY < 0) cameraY = 0;
        if (cameraX > maxCamX) cameraX = maxCamX;
        if (cameraY > maxCamY) cameraY = maxCamY;
    }

    void keyHandler(SDL_Keycode symbol) override {
        if (symbol == SDLK_m) {
            menuOpen = !menuOpen;
            return;
        }

        if (menuOpen) {
            if (symbol == SDLK_UP) selectedIndex--;
            if (symbol == SDLK_DOWN) selectedIndex++;
            return;
        }

        // Movement is handled continuously in update() from keyboard state.
    }

    void draw() override {
        SDL_SetRenderDrawColor(renderer, 65, 0, 150, 255);
        SDL_RenderClear(renderer);

        tileMap->render(renderer, cameraX, cameraY, WIDTH, HEIGHT);
        player->render(renderer);

        if (!menuOpen) return;

        SDL_Rect panel;
        panel.w = 400;
        panel.h = 300;
        panel.x = (WIDTH - panel.w) / 2;
        panel.y = (HEIGHT - panel.h) / 2;
        SDL_SetRenderDrawColor(renderer, 50, 50, 100, 255);
        SDL_RenderFillRect(renderer, &panel);

        if (titleTexture) {
            SDL_Rect dst;
            dst.w = titleW;
            dst.h = titleH;
            dst.x = (WIDTH - titleW) / 2;
            dst.y = 20;
            SDL_RenderCopy(renderer, titleTexture, nullptr, &dst);
        }
    }

    public:
    MyGame():Game(WIDTH,HEIGHT,"Our Cool Game"){ 
        player = nullptr;
        tileMap = nullptr;
        titleTexture = nullptr;
        titleW = 0;
        titleH = 0;
        cameraX = 0;
        cameraY = 0;
        menuOpen = false;
        selectedIndex = 0;
        worldW = 0;
        worldH = 0;
    }
    ~MyGame() override {
        delete player;
        delete tileMap;
    }
};
