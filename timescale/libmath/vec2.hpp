#ifndef VEC2_MATH

#define VEC2_MATH 1
#include <math.h>

class Vec2 {
    // i for "input"
    public:
        float x, y;

        Vec2(float xi = 0, float yi = 0);

        Vec2 operator+(Vec2& other);
        Vec2 operator+(float other);
        Vec2 operator+(int other);

        Vec2 operator-(Vec2& other);
        Vec2 operator-(float other);
        Vec2 operator-(int other);
        Vec2 operator-();

        Vec2 operator*(float other);
        Vec2 operator*(int other);

        Vec2 operator/(float other);
        Vec2 operator/(int other);

        Vec2& operator+=(Vec2& other);
        Vec2& operator+=(float other);
        Vec2& operator+=(int other);

        Vec2& operator-=(Vec2& other);
        Vec2& operator-=(float other);
        Vec2& operator-=(int other);

        Vec2& operator*=(float other);
        Vec2& operator*=(int other);

        Vec2& operator/=(float other);
        Vec2& operator/=(int other);

        float length();
        Vec2& normalize();
};

Vec2 operator+(float other, Vec2& self);
Vec2 operator+(int other, Vec2& self);
Vec2 operator*(float other, Vec2 self);
Vec2 operator*(int other, Vec2 self);

#endif
