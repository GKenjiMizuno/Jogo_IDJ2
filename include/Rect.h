#ifndef RECT_H
#define RECT_H
#include "Vec2.h"

class Rect{

    public:
        float x, y, w, h;
        Rect();
        Rect(float x, float y, float w, float h);
        Vec2 Center() const;
        bool Contains(const Vec2& point) const;
        float Distance(const Rect& rect) const;
        Rect operator+(const Vec2& v) const;

};

#endif