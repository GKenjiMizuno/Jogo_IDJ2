#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#include <SDL_include.h>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT


class InputManager {
public:
    static InputManager& GetInstance();

    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX() const;
    int GetMouseY() const;

    bool QuitRequested() const;

private:
    InputManager();
    ~InputManager();

    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool mouseState[6];       // SDL usa índices 1 a 5
    int mouseUpdate[6];

    int updateCounter;
    bool quitRequested;

    int mouseX;
    int mouseY;
};

#endif // INPUT_MANAGER_H
