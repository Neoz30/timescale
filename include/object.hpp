#pragma once

#include "vec2.hpp"

enum ObjectType
{
    TERRAIN,
    PLAYER,
    BOX
};

class Object
{
    public:
    Vec2F position;
    Vec2F velocity;
    Vec2F force;
    Vec2F size;

    float mass;
    float elasticity;

    bool fixed;
    ObjectType type;

    Object(Vec2F pos, Vec2F s, float mass, float elasticity, bool fixed, ObjectType type);
};