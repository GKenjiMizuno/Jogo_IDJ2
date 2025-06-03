#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    Animation() : frameStart(0), frameEnd(0), frameTime(0.0f) {}  // ✅ construtor padrão

    Animation(int frameStart, int frameEnd, float frameTime) :
        frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime) {}

    int frameStart;
    int frameEnd;
    float frameTime; // tempo por frame em segundos (float)
};

#endif
