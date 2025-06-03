#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& v) const {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

float Vec2::Magnitude() const {
    return sqrt(x*x + y*y);
}

Vec2 Vec2::Normalized() const {
    float mag = Magnitude();
    if (mag > 0) {
        return Vec2(x/mag, y/mag);
    }
    return Vec2(0,0);
}

float Vec2::Distance(const Vec2& v) const {
    return (*this - v).Magnitude();
}

Vec2& Vec2::operator+=(const Vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}


float Vec2::Inclination() const {
    return atan2(y, x);
}

Vec2 Vec2::Rotate(float angle) const {
    return Vec2(
        x * cos(angle) - y * sin(angle),
        x * sin(angle) + y * cos(angle)  
    );
}
