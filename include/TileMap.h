#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"
#include <vector>
#include <memory>
#include <string>

class TileMap : public Component {
public:
    TileMap(GameObject& associated, std::string file, TileSet* tileSet);

    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);

    int& At(int x, int y, int z = 0);

    void RenderLayer(int layer);
    void Render() override;

    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;

    void Update(float dt) override;
    bool Is(std::string type) override;

private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;
    int mapWidth, mapHeight, mapDepth;
};

#endif
