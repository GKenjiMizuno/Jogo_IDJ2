#ifndef GAME_H
#define GAME_H

#include "SDL_include.h"
#include "State.h"

class Game {
public:
    ~Game();
    void Run();
    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetState();
    float GetDeltaTime();
    int GetWidth();
    int GetHeight();

private:
    Game(const char* title, int width, int height);
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    void CalculateDeltaTime();
    int frameStart;
    float dt;
    int width;
    int height;


};

#endif
