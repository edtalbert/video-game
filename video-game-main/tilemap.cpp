#include "tilemap.h"

TileMap::TileMap(SDL_Renderer* renderer,
                 MediaManager& mm,
                 const std::string& tilesetPath,
                 int tileW,
                 int tileH)
    : tileWidth(tileW),
      tileHeight(tileH)
{
    // Load tileset texture using MediaManager
    tileset = mm.read(renderer, tilesetPath, tilesetW, tilesetH);

    if (!tileset) {
        // basic fallback: avoid divide-by-zero
        tilesPerRow = 1;
        width = 0;
        height = 0;
        return;
    }

    tilesPerRow = tilesetW / tileWidth;

    // --- TEMP: Hardcoded map so you see something ---

    // Example 50x20 tile level
    width  = 50;
    height = 20;

    map.resize(height, std::vector<int>(width, 0));

    // Put a "ground" line using tile 1
    for (int x = 0; x < width; ++x) {
        map[height - 1][x] = 1;  // bottom row
        map[height - 2][x] = 1;  // second to last row
    }

    // Some random blocks
    map[10][5] = 2;
    map[9][5]  = 2;
    map[10][6] = 2;
    map[8][20] = 3;
}

void TileMap::render(SDL_Renderer* renderer,
                     int cameraX,
                     int cameraY,
                     int screenW,
                     int screenH)
{
    if (!tileset) return;

    // Which tiles are visible on screen?
    int firstCol = cameraX / tileWidth;
    int firstRow = cameraY / tileHeight;

    if (firstCol < 0) firstCol = 0;
    if (firstRow < 0) firstRow = 0;

    int lastCol = (cameraX + screenW) / tileWidth + 1;
    int lastRow = (cameraY + screenH) / tileHeight + 1;

    if (lastCol > width)  lastCol = width;
    if (lastRow > height) lastRow = height;

    for (int row = firstRow; row < lastRow; ++row) {
        for (int col = firstCol; col < lastCol; ++col) {

            int tileIndex = map[row][col];
            if (tileIndex < 0) continue; // -1 = empty tile

            // Source rect in tileset
            SDL_Rect src;
            src.w = tileWidth;
            src.h = tileHeight;

            int tileX = tileIndex % tilesPerRow;
            int tileY = tileIndex / tilesPerRow;

            src.x = tileX * tileWidth;
            src.y = tileY * tileHeight;

            // Destination rect on screen (world → camera → screen)
            SDL_Rect dst;
            dst.w = tileWidth;
            dst.h = tileHeight;
            dst.x = col * tileWidth - cameraX;
            dst.y = row * tileHeight - cameraY;

            SDL_RenderCopy(renderer, tileset, &src, &dst);
        }
    }
}