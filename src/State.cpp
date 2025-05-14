#include "State.h"
#include "SDL_include.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Animator.h"
#include "Animation.h"
#include "TileSet.h"
#include "TileMap.h"
#include "GameObject.h"


State::State() : quitRequested(false) {

    // Criar background
    GameObject* background = new GameObject();
    background->box = Rect(0, 0, 1200, 900);
    SpriteRenderer* bgSprite = new SpriteRenderer(*background, "resources/img/Background.png");
    background->AddComponent(bgSprite);

    // Cria o Tileset
    TileSet* tileSet = new TileSet(64, 64, "resources/img/Tileset.png");

    // Cria o GameObject do mapa e adiciona TileMap
    GameObject* mapObject = new GameObject();
    TileMap* tileMap = new TileMap(*mapObject, "resources/map/mapf.txt", tileSet);
    mapObject->AddComponent(tileMap);

    // Definir o box do mapa com tamanho correto
    mapObject->box = Rect(
        0, 0,0,0
    );

    // Criar zombie
    GameObject* zombie = new GameObject();
    zombie->box = Rect(600, 450, 0, 0); // tamanho ajustado pelo sprite
    Zombie* zombieComponent = new Zombie(*zombie);
    zombie->AddComponent(zombieComponent);

    Animator* animator = new Animator(*zombie);
    animator->AddAnimation("walking", Animation(0, 3, 0.1f));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    animator->SetAnimation("walking");
    zombie->AddComponent(animator);

    AddObject(background);
    AddObject(mapObject);
    AddObject(zombie);

}


State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    // Implementar se desejar carregar antes
}

void State::Update(float dt) {
    for (auto& go : objectArray)
        go->Update(dt);

    for (int i = 0; i < (int)objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }

    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    for (auto& go : objectArray)
        go->Render();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}
