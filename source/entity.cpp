#include "entity.hpp"

Entity::Entity(Vec2F start_pos, float w, float h)
{
    position = start_pos;
    width = w;
    height = h;
    active = true;
}

Entity::Entity()
{
    width = 1.f;
    height = 1.f;
    active = false;
}

void Entity::step(float dt)
{
    if (!active) return;

    float len = velocity.length();
    acceleration -= velocity.normalize() * 0.5 * (len * len);

    velocity += acceleration * dt;
    position += velocity * dt;

    acceleration.x = 0.f;
    acceleration.y = 0.f;
}

void Entity::draw(SDL_Renderer *renderer)
{
    if (!active) return;

    Vec2F screen_transform = rect_correction(screen_convertion(position), height);
    SDL_FRect rect = {
        screen_transform.x,
        screen_transform.y,
        width * TILE_SIZE,
        height * TILE_SIZE
    };

    SDL_SetRenderDrawColor(renderer, 255, 127, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
