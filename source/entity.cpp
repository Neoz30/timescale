#include "entity.hpp"

Entity::Entity(Vec2F start_pos, float w, float h)
{
    position = start_pos;
    width = w;
    height = h;
}

void Entity::step(float dt)
{
    velocity += acceleration * dt;
    position += velocity * dt;
}

void Entity::draw(SDL_Renderer *renderer)
{
    Vec2I screen_transform = rect_correction(screen_convertion(position));
    SDL_FRect rect = {
        (float)screen_transform.x,
        (float)screen_transform.y,
        width * TILE_SIZE,
        height * TILE_SIZE
    };

    SDL_SetRenderDrawColor(renderer, 255, 127, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
