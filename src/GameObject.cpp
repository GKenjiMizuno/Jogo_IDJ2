#include "GameObject.h"

GameObject::GameObject() {
    isDead = false;
    started = false;
}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Start() {
    for (auto& comp : components) {
        comp->Start();
    }
    started = true;
}

void GameObject::Update(float dt) {
    for (auto& comp : components) {
        comp->Update(dt);
    }
}

void GameObject::Render() {
    for (auto& comp : components) {
        comp->Render();
    }
}

void GameObject::RequestDelete() {
    isDead = true;
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::AddComponent(Component* cpt) {
    std::shared_ptr<Component> ptr(cpt);
    components.emplace_back(ptr);
    if (started) {
        ptr->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (it->get() == cpt) {
            components.erase(it);
            break;
        }
    }
}

Component* GameObject::GetComponent(std::string type) {
    for (auto& comp : components) {
        if (comp->Is(type)) {
            return comp.get();
        }
    }
    return nullptr;
}
