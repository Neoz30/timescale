#pragma once
#include <SDL3/SDL.h>
#include "vec2.hpp"
#include "transforms.hpp"

class Entity
{
    public:
    Vec2F position;
    Vec2F velocity;
    Vec2F acceleration;

    float width;
    float height;

    Entity(Vec2F start_pos, float w, float h);
    void step(float dt);
    void draw(SDL_Renderer *renderer);
};