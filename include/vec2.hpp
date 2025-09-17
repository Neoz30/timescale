#pragma once
#include <math.h>

template <typename T> class Vec2
{
    public:

    T x, y;

    Vec2(T a, T b)
    {
        x = a;
        y = b;
    }
    Vec2(T a)
    {
        x = a;
        y = a;
    }
    Vec2()
    {
        x = 0;
        y = 0;
    }

    Vec2 operator+(Vec2 other)
    {
        return Vec2(x + other.x, y + other.y);
    }
    Vec2 operator-(Vec2 other)
    {
        return Vec2(x - other.x, y - other.y);
    }
    Vec2 operator*(Vec2 other)
    {
        return Vec2(x * other.x, y * other.y);
    }
    Vec2 operator/(Vec2 other)
    {
        return Vec2(x / other.x, y / other.y);
    }

    Vec2 &operator+=(Vec2 other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec2 &operator-=(Vec2 other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vec2 &operator*=(Vec2 other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    Vec2 &operator/=(Vec2 other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    T length()
    {
        return sqrt(x * x + y * y);
    }

    Vec2 normalize()
    {
        T len = length();
        if (len) return Vec2(x / len, y / len);
        return Vec2(x, y);
    }
};

using Vec2I = Vec2<int>;
using Vec2L = Vec2<long>;
using Vec2F = Vec2<float>;
using Vec2D = Vec2<double>;
