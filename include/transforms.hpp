#pragma once
#include "vec2.hpp"
using namespace std;

extern float SCREEN_SCALE;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float TILE_SIZE;

Vec2F screen_convertion(Vec2I position);
Vec2F screen_convertion(Vec2F position);

Vec2F rect_correction(Vec2F position);
Vec2F rect_correction(Vec2F position, float height);

void change_screen_scale(float screen_scale);