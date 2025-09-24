#pragma once

#include "vec2.hpp"

class Object
{
    public:
    Vec2F position;
    Vec2F velocity;
    Vec2F force;
    Vec2F size;
    float mass;

    Object(Vec2F pos, Vec2F s, float mass);
};