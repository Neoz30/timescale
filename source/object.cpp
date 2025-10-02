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

void Object::update(vector<Object *> *objects, float delta) {}

Player::Player(Vec2F position): Object(position, Vec2F(0.85), 1, 0.8, false, PLAYER) {}

Terrain::Terrain(Vec2F position, Vec2F size): Object(position, size, INFINITY, 0, true, TERRAIN) {}

Box::Box(Vec2F position, Vec2F size, float mass): Object(position, size, mass, 0.5, false, BOX) {}

Button::Button(Vec2F position): Object(position, Vec2F(0.8, 0.2), INFINITY, 0, true, BUTTON)
{
    pressed = false;
}

void Button::update(vector<Object *> *objects, float delta)
{
    pressed = false;
    for (Object *object: *objects)
    {
        if (object->fixed) continue;
        if (!overlap_detection(object->position, object->size, position, size)) continue;
        pressed = true;
        break;
    }
}

Gate::Gate(Vec2F position, bool *o): Object(position, Vec2F(0.5, 2), INFINITY, 0, true, GATE)
{
    open = o;
}

void Gate::update(vector<Object *> *objects, float delta)
{
    if (*open)
    {
        size.y = max(0.0, size.y - 8.0 * delta);
    }
    else
    {
        size.y = min(2.0, size.y + 8.0 * delta);
    }
}
