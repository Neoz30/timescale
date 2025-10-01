#pragma once

#include <vector>
#include "object.hpp"

using namespace std;

Player player(Vec2F(16, 3));
Box box(Vec2F(20, 3), Vec2F(1), 2);
Terrain terrain1(Vec2F(0, 0), Vec2F(64, 2));
Button button(Vec2F(12, 2));
Gate gate(Vec2F(14, 2), &button.pressed);

vector<Object *> map1 = {&player, &box, &terrain1, &button, &gate};