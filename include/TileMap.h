#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"
#include <vector>
#include <memory>
#include <string>

class TileMap : public Component {
public:
    TileMap(std::weak_ptr<GameObject> associated, std::string file, TileSet* tileSet);

    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z);
    void RenderLayer(int layer);
    void Render() override;
    void Update(float dt) override;
    bool Is(std::string type) override;

    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;

private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth, mapHeight, mapDepth;
};

#endif
