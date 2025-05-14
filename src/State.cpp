#include "State.h"
#include "SDL_include.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Animator.h"
#include "Animation.h"


State::State() : quitRequested(false) {
    // Criar background
    GameObject* background = new GameObject();
    background->box = Rect(0, 0, 1200, 900);
    SpriteRenderer* bgSprite = new SpriteRenderer(*background, "resources/img/Background.png");
    background->AddComponent(bgSprite);
    AddObject(background);

    // Criar zombie
    GameObject* zombie = new GameObject();
    zombie->box = Rect(600, 450, 0, 0); // tamanho ajustado pelo sprite
    Zombie* zombieComponent = new Zombie(*zombie);
    zombie->AddComponent(zombieComponent);

    // Adicionar Animator para o Zombie
    Animator* animator = new Animator(*zombie);
    animator->AddAnimation("walking", Animation(0, 3, 0.1f)); // frameTime em segundos
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    animator->SetAnimation("walking");
    zombie->AddComponent(animator);

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
