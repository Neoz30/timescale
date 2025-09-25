#pragma once

#include <vector>
#include <math.h>
#include "object.hpp"

using namespace std;

vector<Object> map1 = {
    Object(Vec2F(0, 0), Vec2F(16, 2), INFINITY, 0, true),
    Object(Vec2F(0, 2), Vec2F(2, 14), INFINITY, 0, true),
    Object(Vec2F(4, 4), Vec2F(2, 2), 25, 0.2, false)
};

vector<Object> map2 = {
    Object(Vec2F(0, 0), Vec2F(4, 4), INFINITY, 0, true)
};

vector<Object> map3 = {
    Object(Vec2F(8, 8), Vec2F(8, 8), INFINITY, 0, true)
};