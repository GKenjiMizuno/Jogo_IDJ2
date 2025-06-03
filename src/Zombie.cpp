#include "Zombie.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Animator.h"

Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100),hit(false),dead(false) {
    SpriteRenderer* sr = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    sr->SetFrame(1);
    associated.AddComponent(sr);
    deathSound.Open("resources/audio/Dead.wav");
    hitSound.Open("resources/audio/Hit0.wav");

}

void Zombie::Damage(int damage) {

    if (dead) return;


    hitpoints -= damage;
    hitSound.Play(1); // tocar som de hit sempre que levar dano
    if (hitpoints <= 0) {
        dead = true;
        Animator* animator = (Animator*)associated.GetComponent("Animator");
        if (animator) animator->SetAnimation("dead");
        deathSound.Play(1);
        deathTimer.Restart();

    } else {
        hit = true;
        hitTimer.Restart();
        Animator* animator = (Animator*)associated.GetComponent("Animator");
        if (animator) animator -> SetAnimation("hit");
    }
}

void Zombie::Update(float dt) {

    if (dead) {
        deathTimer.Update(dt);
        if (deathTimer.Get() > 5.0f){
            associated.RequestDelete();
        }
        return;
    }

    hitTimer.Update(dt);

    if (hit && hitTimer.Get() > 0.5f) {
        Animator* animator = (Animator*)associated.GetComponent("Animator");
        if (animator) animator->SetAnimation("walking");
        hit = false;
    }


    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        int mx = InputManager::GetInstance().GetMouseX();// + Camera::pos.x;
        int my = InputManager::GetInstance().GetMouseY();// + Camera::pos.y;

        if (associated.box.Contains({(float)mx, (float)my})) {
            Damage(10);  // valor arbitrário
        }
    }
}

void Zombie::Render() {
    // vazio
}

bool Zombie::Is(std::string type) {
    return (type == "Zombie");
}
