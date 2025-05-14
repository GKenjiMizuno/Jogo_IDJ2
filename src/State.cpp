#include "State.h"
#include "SDL_include.h"

State::State() : bg("resources/img/Background.png"), music("resources/audio/BGM.wav"), quitRequested(false) {
    music.Play(-1);
}

void State::LoadAssets() {
    // já carregado nos construtores
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}
