#pragma once
#include "vec2.hpp"
using namespace std;

extern float SCREEN_SCALE;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float TILE_SIZE;

Vec2I screen_convertion(Vec2I position);
Vec2I screen_convertion(Vec2F position);

Vec2I rect_correction(Vec2I position);
void change_screen_scale(float screen_scale);