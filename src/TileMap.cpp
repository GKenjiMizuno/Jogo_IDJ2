#include "TileMap.h"
#include "GameObject.h"
#include "Camera.h"
#include <fstream>
#include <iostream>

TileMap::TileMap(std::weak_ptr<GameObject> associated, std::string file, TileSet* tileSet)
    : Component(associated), tileSet(tileSet) {
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream mapFile(file);
    if (!mapFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo de mapa: " << file << std::endl;
        return;
    }

    mapFile >> mapWidth >> mapHeight >> mapDepth;
    tileMatrix.resize(mapWidth * mapHeight * mapDepth);

    for (int z = 0; z < mapDepth; ++z)
        for (int y = 0; y < mapHeight; ++y)
            for (int x = 0; x < mapWidth; ++x)
                mapFile >> At(x, y, z);

    mapFile.close();
}

void TileMap::SetTileSet(TileSet* tileSet_) {
    tileSet = tileSet_;
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[(z * mapHeight * mapWidth) + (y * mapWidth) + x];
}

void TileMap::RenderLayer(int layer) {
    if (!tileSet) return;

    int tileW = tileSet->GetTileWidth();
    int tileH = tileSet->GetTileHeight();

    if (auto go = associated.lock()) {
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                int tileIndex = At(x, y, layer);
                if (tileIndex < 0) continue;

                float renderX = (float)(go->box.x + x * tileW - Camera::pos.x);
                float renderY = (float)(go->box.y + y * tileH - Camera::pos.y);
                tileSet->RenderTile(tileIndex, renderX, renderY);
            }
        }
    }
}

void TileMap::Render() {
    for (int layer = 0; layer < mapDepth; layer++)
        RenderLayer(layer);
}

void TileMap::Update(float dt) {
    // Não faz nada ainda
}

bool TileMap::Is(std::string type) {
    return (type == "TileMap");
}

int TileMap::GetWidth() const {
    return mapWidth;
}

int TileMap::GetHeight() const {
    return mapHeight;
}

int TileMap::GetDepth() const {
    return mapDepth;
}
