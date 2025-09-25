#include "object.hpp"

Object::Object(Vec2F pos, Vec2F s, float m, float e, bool f, ObjectType t)
{
    position = pos;
    size = s;

    mass = m;
    elasticity = e;

    fixed = f;
    if (fixed) mass = INFINITY;

    type = t;
}