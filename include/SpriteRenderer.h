#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "Sprite.h"
#include <string>

class SpriteRenderer : public Component {
public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, std::string file, int frameCountW=1, int frameCountH=1);
    ~SpriteRenderer();

    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrame(int frame);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void SetCameraFollower(bool follow);

private:
    Sprite sprite;
    bool cameraFollower;
};

#endif
