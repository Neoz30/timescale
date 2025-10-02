#pragma once

#include "object.hpp"

Player player(Vec2F(1, 1));
Box box(Vec2F(4, 1), Vec2F(1), 2);
Button button(Vec2F(6, 1));
Gate gate(Vec2F(8.5, 1), &button.pressed);
Terrain terrain1(Vec2F(-16, -15), Vec2F(39, 16));
Terrain terrain2(Vec2F(11, 1), Vec2F(12, 16));
Terrain terrain3(Vec2F(8, 3), Vec2F(3, 1));
Terrain terrain4(Vec2F(-16, 1), Vec2F(16, 16));
Terrain terrain5(Vec2F(0, 9), Vec2F(11, 8));

vector<Object *> map1 = {&player, &box, &button, &gate, &terrain1, &terrain2, &terrain3, &terrain4, &terrain5};