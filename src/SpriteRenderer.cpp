#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Camera.h"

SpriteRenderer::SpriteRenderer(std::weak_ptr<GameObject> associated)
    : Component(associated), sprite(), cameraFollower(false) {}

SpriteRenderer::SpriteRenderer(std::weak_ptr<GameObject> associated, std::string file, int frameCountW, int frameCountH)
    : Component(associated), sprite(file, frameCountW, frameCountH), cameraFollower(false) {
    if (auto go = associated.lock()) {
        go->box.w = sprite.GetWidth();
        go->box.h = sprite.GetHeight();
    }
    SetFrame(0);
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    if (auto go = associated.lock()) {
        go->box.w = sprite.GetWidth();
        go->box.h = sprite.GetHeight();
    }
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::SetCameraFollower(bool value) {
    cameraFollower = value;
}

void SpriteRenderer::Update(float dt) {
    // Pode ser usado no futuro para animação automática
}

void SpriteRenderer::Render() {
    if (auto go = associated.lock()) {
        int x = (int)go->box.x;
        int y = (int)go->box.y;

        if (!cameraFollower) {
            x -= (int)Camera::pos.x;
            y -= (int)Camera::pos.y;
        }

        sprite.Render(x, y, (int)go->box.w, (int)go->box.h);
    }
}

bool SpriteRenderer::Is(std::string type) {
    return (type == "SpriteRenderer");
}
