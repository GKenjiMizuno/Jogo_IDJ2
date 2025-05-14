#include "Animator.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Animator::Animator(GameObject& associated) :
    Component(associated),
    frameStart(0),
    frameEnd(0),
    frameTime(0),
    currentFrame(0),
    timeElapsed(0) {}

void Animator::Update(float dt) {
    if (frameTime <= 0) return;

    timeElapsed += dt;
    if (timeElapsed > frameTime) {
        timeElapsed -= frameTime;
        currentFrame++;
        if (currentFrame > frameEnd)
            currentFrame = frameStart;

        SpriteRenderer* sr = (SpriteRenderer*)associated.GetComponent("SpriteRenderer");
        if (sr)
            sr->SetFrame(currentFrame);
    }
}

void Animator::Render() {
    // vazio
}

bool Animator::Is(std::string type) {
    return (type == "Animator");
}

void Animator::SetAnimation(std::string name) {
    auto it = animations.find(name);
    if (it != animations.end()) {
        frameStart = it->second.frameStart;
        frameEnd = it->second.frameEnd;
        frameTime = it->second.frameTime;
        currentFrame = frameStart;
        timeElapsed = 0;

        SpriteRenderer* sr = (SpriteRenderer*)associated.GetComponent("SpriteRenderer");
        if (sr)
            sr->SetFrame(currentFrame);
    }
}

void Animator::AddAnimation(std::string name, Animation anim) {
    if (animations.find(name) == animations.end()) {
        animations.emplace(name, anim);
    }
}
