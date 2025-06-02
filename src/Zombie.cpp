#include "Zombie.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "InputManager.h"

Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100) {
    SpriteRenderer* sr = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    sr->SetFrame(1);
    associated.AddComponent(sr);
    deathSound.Open("resources/audio/Dead.wav");
    hitSound.Open("resources/audio/Hit0.wav");

}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    hitSound.Play(1); // tocar som de hit sempre que levar dano
    if (hitpoints <= 0) {
        SpriteRenderer* sr = (SpriteRenderer*)associated.GetComponent("SpriteRenderer");
        if (sr) sr->SetFrame(5);
        deathSound.Play(1);

    }
}

void Zombie::Update(float dt) {
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
