#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include "mediaManager.hpp"

class TileMap {
public:
    TileMap(SDL_Renderer* renderer,
            MediaManager& mm,
            const std::string& tilesetPath,
            int tileW,
            int tileH);

    void render(SDL_Renderer* renderer,
                int cameraX,
                int cameraY,
                int screenW,
                int screenH);

    int getWidthInTiles() const { return width; }
    int getHeightInTiles() const { return height; }
    int getTileSize() const { return tileWidth; }

private:
    SDL_Texture* tileset = nullptr;
    int tilesetW = 0;
    int tilesetH = 0;
    int tileWidth = 0;
    int tileHeight = 0;
    int tilesPerRow = 0;

    int width = 0;   // in tiles
    int height = 0;  // in tiles

    std::vector<std::vector<int>> map;  // tile indices
};