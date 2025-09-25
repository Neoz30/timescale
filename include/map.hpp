#pragma once

#include <vector>
#include <math.h>
#include "object.hpp"

using namespace std;

vector<Object> map1 = {
    Object(Vec2F(0, 0), Vec2F(64, 2), INFINITY, 0, true, TERRAIN),
    Object(Vec2F(4, 2), Vec2F(0.8), 4, 0.2, false, BOX)
};

vector<Object> map2 = {
    Object(Vec2F(0, 0), Vec2F(4, 4), INFINITY, 0, true, TERRAIN)
};

vector<Object> map3 = {
    Object(Vec2F(8, 8), Vec2F(8, 8), INFINITY, 0, true, TERRAIN)
};