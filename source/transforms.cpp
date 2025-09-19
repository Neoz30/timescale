#include "transforms.hpp"
#include <stdio.h>

float SCREEN_SCALE = 1;
int SCREEN_WIDTH = 1;
int SCREEN_HEIGHT = 1;
float TILE_SIZE = 1;

Vec2F screen_convertion(Vec2I position)
{
    Vec2F pos(position.x, position.y);
    pos *= TILE_SIZE;
    pos.y = pos.y * -1 + SCREEN_HEIGHT;
    return pos;
}

Vec2F screen_convertion(Vec2F position)
{
    position *= TILE_SIZE;
    position.y = position.y * -1 + SCREEN_HEIGHT;
    return position;
}

Vec2F rect_correction(Vec2F position)
{
    return position - Vec2F(0, TILE_SIZE);
}

Vec2F rect_correction(Vec2F position, float height)
{
    return position - Vec2F(0, TILE_SIZE * height);
}

void change_screen_scale(float screen_scale)
{
    SCREEN_SCALE = screen_scale;
    TILE_SIZE = min(SCREEN_WIDTH, SCREEN_HEIGHT) * SCREEN_SCALE;
}
