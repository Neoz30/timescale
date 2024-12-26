#include <iostream>
#include "vec2.hpp"

// Vec2
Vec2::Vec2(float xi, float yi) {x = xi, y = yi;}

// Overloading Vec2 Operator+
Vec2 Vec2::operator+(Vec2& other) {return Vec2(x+other.x, y+other.y);}
Vec2 Vec2::operator+(float other) {return Vec2(x+other, y+other);}
Vec2 Vec2::operator+(int other) {return Vec2(x+other, y+other);}
Vec2 operator+(float other, Vec2& self) {return self+other;}
Vec2 operator+(int other, Vec2& self) {return self+other;}

// Overloading Vec2 Operator-
Vec2 Vec2::operator-(Vec2& other) {return Vec2(x-other.x, y-other.y);}
Vec2 Vec2::operator-(float other) {return Vec2(x-other, y-other);}
Vec2 Vec2::operator-(int other) {return Vec2(x-other, y-other);}
Vec2 Vec2::operator-() {return Vec2(-x, -y);}

// Overloading Vec2 Operator*
Vec2 Vec2::operator*(float other) {return Vec2(x*other, y*other);}
Vec2 Vec2::operator*(int other) {return Vec2(x*other, y*other);}
Vec2 operator*(float other, Vec2 self) {return self*other;}
Vec2 operator*(int other, Vec2 self) {return self*other;}

// Overloading Vec2 Operator/
Vec2 Vec2::operator/(float other) {return Vec2(x/other, y/other);}
Vec2 Vec2::operator/(int other) {return Vec2(x/other, y/other);}

// Overloading Vec2 Operator+=
Vec2& Vec2::operator+=(Vec2& other) {
    x += other.x; y += other.y;
    return *this;
}
Vec2& Vec2::operator+=(float other) {
    x += other; y += other;
    return *this;
}
Vec2& Vec2::operator+=(int other) {
    x += other; y += other;
    return *this;
}

// Overloading Vec2 Operator-=
Vec2& Vec2::operator-=(Vec2& other) {
    x -= other.x; y -= other.y;
    return *this;
}
Vec2& Vec2::operator-=(float other) {
    x -= other; y -= other;
    return *this;
}
Vec2& Vec2::operator-=(int other) {
    x -= other; y -= other;
    return *this;
}

// Overloading Vec2 Operator*=
Vec2& Vec2::operator*=(float other) {
    x *= other; y *= other;
    return *this;
}
Vec2& Vec2::operator*=(int other) {
    x *= other; y *= other;
    return *this;
}

// Overloading Vec2 Operator/=
Vec2& Vec2::operator/=(float other) {
    x /= other; y /= other;
    return *this;
}
Vec2& Vec2::operator/=(int other) {
    x /= other; y /= other;
    return *this;
}

// Vector function
float Vec2::length() {
    return sqrt(x*x + y*y);
}
Vec2& Vec2::normalize() {
    float len = length();
    if (len == 0 ) {return *this;}
    x /= len; y /= len;
    return *this;
}
