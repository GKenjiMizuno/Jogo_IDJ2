#include "Zombie.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100) {
    SpriteRenderer* sr = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    sr->SetFrame(1);
    associated.AddComponent(sr);
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        SpriteRenderer* sr = (SpriteRenderer*)associated.GetComponent("SpriteRenderer");
        if (sr) sr->SetFrame(5);
    }
}

void Zombie::Update(float dt) {
    Damage(1); // tira 1 de HP por frame
}

void Zombie::Render() {
    // vazio
}

bool Zombie::Is(std::string type) {
    return (type == "Zombie");
}
