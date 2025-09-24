#pragma once

#include "vec2.hpp"

class Collider
{
    public:
    Vec2F position;
    Vec2F velocity;
    Vec2F acceleration;
    Vec2F size;

    Collider(Vec2F pos, Vec2F s);
};