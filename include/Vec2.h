#ifndef VEC2_H
#define VEC2_H
#include <cmath>

class Vec2 {

    public:
        float x, y;
        Vec2();
        Vec2(float x, float y);
        Vec2 operator+(const Vec2& v) const;
        Vec2 operator-(const Vec2& v) const;
        Vec2 operator*(float scalar) const;
        float Magnitude() const;
        Vec2 Normalized() const;
        float Inclination() const;
        float Distance(const Vec2& v) const;
        Vec2 Rotate(float angle) const;


};

#endif