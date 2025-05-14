#include "GameObject.h"
#include <algorithm>

GameObject::GameObject() : isDead(false), box(0,0,0,0) {}

GameObject::~GameObject() {
    for (auto cpt : components)
        delete cpt;
    components.clear();
}

void GameObject::Update(float dt) {
    for (auto cpt : components)
        cpt->Update(dt);
}

void GameObject::Render() {
    for (auto cpt : components)
        cpt->Render();
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    components.erase(std::remove(components.begin(), components.end(), cpt), components.end());
}

Component* GameObject::GetComponent(std::string type) {
    for (auto cpt : components) {
        if (cpt->Is(type))
            return cpt;
    }
    return nullptr;
}
