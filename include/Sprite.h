#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "SDL_include.h"

class Sprite {
public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, int w, int h);
    void Render(int x, int y);
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    int GetWidth();
    int GetHeight();
    bool IsOpen();

private:
    SDL_Texture* texture;
    int width, height;
    SDL_Rect clipRect;

    int frameCountW, frameCountH;
    int currentFrame;
};

#endif
