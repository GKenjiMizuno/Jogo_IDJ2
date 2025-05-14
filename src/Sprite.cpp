#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : texture(nullptr), width(0), height(0), frameCountW(1), frameCountH(1), currentFrame(0) {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH)
    : texture(nullptr), frameCountW(frameCountW), frameCountH(frameCountH), currentFrame(0) {
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
    SetFrame(0);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x, y, w, h};
}

void Sprite::SetFrame(int frame) {
    int frameX = frame % frameCountW;
    int frameY = frame / frameCountW;
    int frameWidth = width / frameCountW;
    int frameHeight = height / frameCountH;

    if (frameX < 0 || frameX >= frameCountW || frameY < 0 || frameY >= frameCountH) return;

    SetClip(frameX * frameWidth, frameY * frameHeight, frameWidth, frameHeight);
    currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCountW_, int frameCountH_) {
    frameCountW = frameCountW_;
    frameCountH = frameCountH_;
    SetFrame(0);
}

void Sprite::Render(int x, int y, int w, int h) {
    SDL_Rect dstRect = {x, y, w, h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

void Sprite::Render(int x, int y) {
    Render(x, y, clipRect.w, clipRect.h);
}

int Sprite::GetWidth() {
    return width / frameCountW;
}

int Sprite::GetHeight() {
    return height / frameCountH;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}
