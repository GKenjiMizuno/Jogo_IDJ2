// InputManager.cpp
#include "InputManager.h"
#include <SDL2/SDL.h>

InputManager::InputManager() : mouseX(0), mouseY(0), updateCounter(0), quitRequested(false) {
    for (int i = 0; i < 6; ++i) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::~InputManager() {
    // Nada a destruir manualmente
}


void InputManager::Update() {
    SDL_Event event;
    updateCounter++;
    quitRequested = false;

    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quitRequested = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                }
                break;

            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyUpdate[key] == updateCounter && keyState[key];
}

bool InputManager::KeyRelease(int key) {
    return keyUpdate[key] == updateCounter && !keyState[key];
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseUpdate[button] == updateCounter && mouseState[button];
}

bool InputManager::MouseRelease(int button) {
    return mouseUpdate[button] == updateCounter && !mouseState[button];
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() const {
    return mouseX;
}

int InputManager::GetMouseY() const {
    return mouseY;
}

bool InputManager::QuitRequested() const {
    return quitRequested;
}
