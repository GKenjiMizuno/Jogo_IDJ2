#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "Rect.h"

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();

    bool IsDead() const;
    void RequestDelete();

    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);

    Component* GetComponent(std::string type);

    Rect box;

private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead;
    bool started;
};

#endif
