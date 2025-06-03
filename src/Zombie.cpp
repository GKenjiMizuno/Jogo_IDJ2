#include "Zombie.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Animator.h"
#include "Camera.h"

Zombie::Zombie(std::weak_ptr<GameObject> associated)
    : Component(associated), hitpoints(100), hit(false), dead(false) {

    if (auto go = associated.lock()) {
        SpriteRenderer* sr = new SpriteRenderer(go, "resources/img/Enemy.png", 3, 2);
        sr->SetFrame(1);
        go->AddComponent(sr);
    }

    deathSound.Open("resources/audio/Dead.wav");
    hitSound.Open("resources/audio/Hit0.wav");
}

void Zombie::Damage(int damage) {
    if (dead) return;

    hitpoints -= damage;
    hitSound.Play(1);

    if (auto go = associated.lock()) {
        if (hitpoints <= 0) {
            dead = true;
            if (auto animator = (Animator*)go->GetComponent("Animator")) {
                animator->SetAnimation("dead");
            }
            deathSound.Play(1);
            deathTimer.Restart();
        } else {
            hit = true;
            hitTimer.Restart();
            if (auto animator = (Animator*)go->GetComponent("Animator")) {
                animator->SetAnimation("hit");
            }
        }
    }
}

void Zombie::Update(float dt) {
    if (dead) {
        deathTimer.Update(dt);
        if (deathTimer.Get() > 5.0f) {
            if (auto go = associated.lock()) {
                go->RequestDelete();
            }
        }
        return;
    }

    hitTimer.Update(dt);

    if (hit && hitTimer.Get() > 0.5f) {
        if (auto go = associated.lock()) {
            if (auto animator = (Animator*)go->GetComponent("Animator")) {
                animator->SetAnimation("walking");
            }
        }
        hit = false;
    }

    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        int mx = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
        int my = InputManager::GetInstance().GetMouseY() + Camera::pos.y;

        if (auto go = associated.lock()) {
            if (go->box.Contains({(float)mx, (float)my})) {
                Damage(10);
            }
        }
    }
}

void Zombie::Render() {
    // vazio
}

bool Zombie::Is(std::string type) {
    return (type == "Zombie");
}
