#include "transforms.hpp"
#include <stdio.h>

float SCREEN_SCALE = 1;
int SCREEN_WIDTH = 1;
int SCREEN_HEIGHT = 1;
float TILE_SIZE = 1;

Vec2I screen_convertion(Vec2I position)
{
    position *= TILE_SIZE;
    position.y = position.y * -1 + SCREEN_HEIGHT;
    return position;
}

Vec2I screen_convertion(Vec2F position)
{
    position *= TILE_SIZE;
    position.y = position.y * -1 + SCREEN_HEIGHT;
    return Vec2I(position.x, position.y);
}

Vec2I rect_correction(Vec2I position)
{
    return position - Vec2I(0, TILE_SIZE);
}

void change_screen_scale(float screen_scale)
{
    SCREEN_SCALE = screen_scale;
    TILE_SIZE = min(SCREEN_WIDTH, SCREEN_HEIGHT) * SCREEN_SCALE;
}
