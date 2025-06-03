#include "Animator.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Animator::Animator(std::weak_ptr<GameObject> associated)
    : Component(associated), timeElapsed(0), currentFrame(0), frameStart(0), frameEnd(0), frameTime(0.0f) {}

void Animator::AddAnimation(std::string name, Animation anim) {
    animations[name] = anim;
}

void Animator::SetAnimation(std::string name) {
    if (animations.count(name) == 0) return;

    Animation anim = animations[name];
    currentAnimation = name;
    frameStart = anim.frameStart;
    frameEnd = anim.frameEnd;
    frameTime = anim.frameTime;
    currentFrame = frameStart;

    if (auto go = associated.lock()) {
        SpriteRenderer* sr = (SpriteRenderer*)go->GetComponent("SpriteRenderer");
        if (sr) {
            sr->SetFrame(currentFrame);
        }
    }
}

void Animator::Update(float dt) {
    if (frameTime <= 0) return;

    timeElapsed += dt;
    if (timeElapsed > frameTime) {
        timeElapsed -= frameTime;
        currentFrame++;
        if (currentFrame > frameEnd) {
            currentFrame = frameStart;
        }

        if (auto go = associated.lock()) {
            SpriteRenderer* sr = (SpriteRenderer*)go->GetComponent("SpriteRenderer");
            if (sr) {
                sr->SetFrame(currentFrame);
            }
        }
    }
}

void Animator::Render() {
    // Nada a renderizar diretamente
}

bool Animator::Is(std::string type) {
    return (type == "Animator");
}
