#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include "GameObject.h"

class State {
public:
    State();
    ~State();

    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start(); 
    bool QuitRequested();

    void AddObject(GameObject* go);
    std::weak_ptr<GameObject> AddObject(std::shared_ptr<GameObject> go); // para permitir uso de weak_ptr
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go); // localizar um objeto


private:
    std::vector<std::shared_ptr<GameObject>> objectArray;
    bool quitRequested;
    bool started;
};

#endif
