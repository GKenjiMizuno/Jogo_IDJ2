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

    bool QuitRequested();

    void AddObject(GameObject* go);

private:
    std::vector<std::unique_ptr<GameObject>> objectArray;
    bool quitRequested;
};

#endif
