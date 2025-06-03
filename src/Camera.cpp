#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        pos.x = focus->box.Center().x - Game::GetInstance().GetWidth() / 2;
        pos.y = focus->box.Center().y - Game::GetInstance().GetHeight() / 2;
    } else {
        InputManager& input = InputManager::GetInstance();
        speed = Vec2(0, 0);

        if (input.IsKeyDown(LEFT_ARROW_KEY))  speed.x = -200;
        if (input.IsKeyDown(RIGHT_ARROW_KEY)) speed.x =  200;
        if (input.IsKeyDown(UP_ARROW_KEY))    speed.y = -200;
        if (input.IsKeyDown(DOWN_ARROW_KEY))  speed.y =  200;

        pos += speed * dt;
    }
}
