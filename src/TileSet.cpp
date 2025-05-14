#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight)
{
    int tilesInWidth = tileSet.GetWidth() / tileWidth;
    int tilesInHeight = tileSet.GetHeight() / tileHeight;
    tileCount = tilesInWidth * tilesInHeight;
    tileSet.SetFrameCount(tilesInWidth, tilesInHeight); // trata como linha única de frames
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index >= (unsigned)tileCount) return;
    tileSet.SetFrame((int)index);
    tileSet.Render((int)x, (int)y);
}

int TileSet::GetTileWidth() const {
    return tileWidth;
}

int TileSet::GetTileHeight() const {
    return tileHeight;
}
