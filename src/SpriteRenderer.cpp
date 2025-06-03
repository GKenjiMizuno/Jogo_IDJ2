#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Camera.h"


SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated), sprite(), cameraFollower(false){}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH)
    : Component(associated), sprite(file, frameCountW, frameCountH),cameraFollower(false) {
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    SetFrame(0);
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::Update(float dt) {
    // vazio
}
void SpriteRenderer::SetCameraFollower(bool follow) {
    cameraFollower = follow;
}



void SpriteRenderer::Render() {
    int x = (int)associated.box.x;
    int y = (int)associated.box.y;

    if (!cameraFollower) {
        x -= Camera::pos.x;
        y -= Camera::pos.y;
    }

    sprite.Render(x, y, (int)associated.box.w, (int)associated.box.h);
}


bool SpriteRenderer::Is(std::string type) {
    return (type == "SpriteRenderer");
}
