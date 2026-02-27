#pragma once

#include <SDL.h>
#include <string>
#include <vector>

#include "mediaManager.hpp"

class TileMap {
private:
  SDL_Texture* tileset;
  int tilesetW;
  int tilesetH;
  int tileWidth;
  int tileHeight;
  int tilesPerRow;
  int width;
  int height;
  std::vector<std::vector<int>> map;

public:
  TileMap(SDL_Renderer* renderer,
          MediaManager& mm,
          const std::string& tilesetPath,
          int tileW,
          int tileH)
      : tileset(nullptr),
        tilesetW(0),
        tilesetH(0),
        tileWidth(tileW),
        tileHeight(tileH),
        tilesPerRow(1),
        width(0),
        height(0) {
    tileset = mm.read(renderer, tilesetPath, tilesetW, tilesetH);
    if (!tileset || tileWidth <= 0 || tileHeight <= 0) return;

    tilesPerRow = tilesetW / tileWidth;
    if (tilesPerRow <= 0) tilesPerRow = 1;

    int tileCount = (tilesetW / tileWidth) * (tilesetH / tileHeight);
    if (tileCount <= 0) tileCount = 1;

    width = 240;
    height = 160;
    map.assign(height, std::vector<int>(width, 0));

    int grassTile = 0;
    int dirtTile = (tileCount > 1) ? 1 : grassTile;
    int pathTile = (tileCount > 2) ? 2 : dirtTile;

    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        map[y][x] = grassTile;
      }
    }

    int cx = width / 2;
    int cy = height / 2;

    for (int x = 0; x < width; ++x) {
      map[cy][x] = pathTile;
      if (cy + 1 < height) map[cy + 1][x] = pathTile;
    }
    for (int y = 0; y < height; ++y) {
      map[y][cx] = pathTile;
      if (cx + 1 < width) map[y][cx + 1] = pathTile;
    }

    for (int i = 0; i < 22; ++i) {
      int upY = cy - i;
      int downY = cy + i;
      int leftX = cx - i;
      int rightX = cx + i;

      if (upY >= 0 && leftX >= 0) map[upY][leftX] = pathTile;
      if (upY >= 0 && rightX < width) map[upY][rightX] = pathTile;
      if (downY < height && leftX >= 0) map[downY][leftX] = pathTile;
      if (downY < height && rightX < width) map[downY][rightX] = pathTile;
    }

    struct Patch {
      int x;
      int y;
      int rx;
      int ry;
    };
    Patch patches[] = {
      {18, 14, 7, 4},
      {92, 16, 9, 5},
      {30, 58, 8, 5},
      {84, 54, 10, 6},
      {58, 34, 6, 3},
      {150, 30, 12, 7},
      {190, 44, 10, 6},
      {170, 120, 14, 8},
      {70, 130, 11, 7},
    };

    for (const Patch& p : patches) {
      for (int y = p.y - p.ry; y <= p.y + p.ry; ++y) {
        if (y < 0 || y >= height) continue;
        for (int x = p.x - p.rx; x <= p.x + p.rx; ++x) {
          if (x < 0 || x >= width) continue;
          int dx = x - p.x;
          int dy = y - p.y;
          if ((dx * dx) * (p.ry * p.ry) + (dy * dy) * (p.rx * p.rx) <=
              (p.rx * p.rx) * (p.ry * p.ry)) {
            if (map[y][x] != pathTile) map[y][x] = dirtTile;
          }
        }
      }
    }
  }

  void render(SDL_Renderer* renderer,
              int cameraX,
              int cameraY,
              int screenW,
              int screenH) {
    if (!renderer || !tileset || map.empty()) return;

    int firstCol = cameraX / tileWidth;
    int firstRow = cameraY / tileHeight;
    if (firstCol < 0) firstCol = 0;
    if (firstRow < 0) firstRow = 0;

    int lastCol = (cameraX + screenW) / tileWidth + 1;
    int lastRow = (cameraY + screenH) / tileHeight + 1;
    if (lastCol > width) lastCol = width;
    if (lastRow > height) lastRow = height;

    for (int row = firstRow; row < lastRow; ++row) {
      for (int col = firstCol; col < lastCol; ++col) {
        int tileIndex = map[row][col];
        if (tileIndex < 0) continue;

        SDL_Rect src;
        src.w = tileWidth;
        src.h = tileHeight;
        src.x = (tileIndex % tilesPerRow) * tileWidth;
        src.y = (tileIndex / tilesPerRow) * tileHeight;

        SDL_Rect dst;
        dst.w = tileWidth;
        dst.h = tileHeight;
        dst.x = col * tileWidth - cameraX;
        dst.y = row * tileHeight - cameraY;
        SDL_RenderCopy(renderer, tileset, &src, &dst);
      }
    }
  }

  int getWidthInTiles() const { return width; }
  int getHeightInTiles() const { return height; }
  int getTileSize() const { return tileWidth; }
};
