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

Player::Player(Vec2F position): Object(position, Vec2F(0.85), 5, 0.8, false, PLAYER) {}

Terrain::Terrain(Vec2F position, Vec2F size): Object(position, size, INFINITY, 0, true, TERRAIN) {}

Box::Box(Vec2F position, Vec2F size, float mass): Object(position, size, mass, 0.5, false, BOX) {}

Button::Button(Vec2F position): Object(position, Vec2F(0.8, 0.2), INFINITY, 0, true, BUTTON)
{
    pressed = false;
}

Gate::Gate(Vec2F position, bool *o): Object(position, Vec2F(0.5, 2), INFINITY, 0, true, GATE)
{
    open = o;
}