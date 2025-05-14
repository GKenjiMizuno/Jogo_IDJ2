#include "Game.h"
#include <iostream>

Game* Game::instance = nullptr;

Game::Game(const char* title, int width, int height) {
    if (instance != nullptr) {
        std::cerr << "Erro: Game já instanciado!" << std::endl;
        exit(1);
    }

    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "Erro SDL_Init: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erro IMG_Init: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if ((Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG) != MIX_INIT_OGG) {
        std::cerr << "Erro Mix_Init: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "Erro Mix_OpenAudio: " << SDL_GetError() << std::endl;
        exit(1);
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        std::cerr << "Erro SDL_CreateWindow: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erro SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        exit(1);
    }

    state = new State();
}

Game::~Game() {
    delete state;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Run() {
    state->LoadAssets();

    while (!state->QuitRequested()) {
        float dt = 0.033f; // 33ms ~ 30 FPS, pode melhorar usando SDL_GetTicks para delta real

        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}

Game& Game::GetInstance() {
    if (!instance)
        new Game("Jogo IDJ", 1200, 900);
    return *instance;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}
