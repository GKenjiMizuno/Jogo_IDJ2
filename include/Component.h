#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include <memory>

class GameObject;

class Component {

    public:
        std::weak_ptr<GameObject> associated;

        Component(std::weak_ptr<GameObject> associated);
        virtual ~Component();

        virtual void Start();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(std::string type) = 0;

};

#endif