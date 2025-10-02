#pragma once

#include "vec2.hpp"
#include "common.hpp"

enum ObjectType
{
    PLAYER,
    TERRAIN,
    BOX,
    BUTTON,
    GATE
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

    virtual void update(vector<Object *> *objects, float delta);
};

class Player: public Object
{
    public:
    Player(Vec2F pos);
};

class Terrain: public Object
{
    public:
    Terrain(Vec2F position, Vec2F size);
};

class Box: public Object
{
    public:
    Box(Vec2F position, Vec2F size, float mass);
};

class Button: public Object
{
    public:
    bool pressed;
    
    Button(Vec2F position);

    void update(vector<Object *> *objects, float delta) override;
};

class Gate: public Object
{
    public:
    bool *open;
    Gate(Vec2F position, bool *open);

    void update(vector<Object *> *objects, float delta) override;
};