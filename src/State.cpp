#include "State.h"
#include "SDL_include.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Animator.h"
#include "Animation.h"
#include "TileSet.h"
#include "TileMap.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Timer.h"
#include "Game.h"
#include "Camera.h"


State::State() : quitRequested(false) {

    // Criar background
    std::shared_ptr<GameObject> background = std::make_shared<GameObject>();
    background->box = Rect(0, 0, 1200, 900);
    SpriteRenderer* bgSprite = new SpriteRenderer(std::weak_ptr<GameObject>(background), "resources/img/Background.png");
    bgSprite->SetCameraFollower(true);
    background->AddComponent(bgSprite);

    // Cria o Tileset
    TileSet* tileSet = new TileSet(64, 64, "resources/img/Tileset.png");

    // Cria o GameObject do mapa e adiciona TileMap
    std::shared_ptr<GameObject> mapObject = std::make_shared<GameObject>();
    TileMap* tileMap = new TileMap(std::weak_ptr<GameObject>(mapObject), "resources/map/mapf.txt", tileSet);
    mapObject->AddComponent(tileMap);

    // Definir o box do mapa com tamanho correto
    mapObject->box = Rect(
        0, 0,0,0
    );

    // Criar zombie
    
    AddObject(background);
    AddObject(mapObject);

}


State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    // Implementar se desejar carregar antes
}

void State::Start() {
    for (auto& obj : objectArray)
        obj->Start();
    started = true;
}


void State::Update(float dt) {

    Camera::Update(dt);
    InputManager& input = InputManager::GetInstance();
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
        return;
    }


    if (input.KeyPress(SDLK_SPACE)) {
        auto zombie = std::make_shared<GameObject>();
        int mx = input.GetMouseX() + Camera::pos.x;
        int my = input.GetMouseY() + Camera::pos.y;
        zombie->box = Rect(mx, my, 0, 0);

        Zombie* zombieComponent = new Zombie(std::weak_ptr<GameObject>(zombie));
        zombie->AddComponent(zombieComponent);

        Animator* animator = new Animator(std::weak_ptr<GameObject>(zombie));
        animator->AddAnimation("walking", Animation(0, 3, 0.1f));
        animator->AddAnimation("dead", Animation(5, 5, 0.0f));
        animator->AddAnimation("hit", Animation(4,4,0.0f));
        animator->SetAnimation("walking");
        zombie->AddComponent(animator);
        
        AddObject(zombie);
}


    for (auto& go : objectArray)
        go->Update(dt);

    for (int i = 0; i < (int)objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }

}

void State::Render() {
    for (auto& go : objectArray)
        go->Render();
}

bool State::QuitRequested() {
    return quitRequested;
}


std::weak_ptr<GameObject> State::AddObject(std::shared_ptr<GameObject> go) {
    objectArray.emplace_back(go);
    if (started) go->Start();
    return std::weak_ptr<GameObject>(go);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (auto& obj : objectArray) {
        if (obj.get() == go)
            return std::weak_ptr<GameObject>(obj);
    }
    return std::weak_ptr<GameObject>();
}
