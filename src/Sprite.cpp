#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : texture(nullptr), width(0), height(0) {}

Sprite::Sprite(std::string file) : texture(nullptr) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture) SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
    if (texture) SDL_DestroyTexture(texture);
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (!texture) {
        SDL_Log("Erro ao carregar textura %s: %s", file.c_str(), SDL_GetError());
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect = {x, y, clipRect.w, clipRect.h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}
