#pragma once

#include <vector>
#include <math.h>
#include "object.hpp"

using namespace std;

vector<Object> map1 = {
    Object(Vec2F(0, 0), Vec2F(8, 2), INFINITY),
    Object(Vec2F(0, 16), Vec2F(8, 2), INFINITY)
};

vector<Object> map2 = {
    {Vec2F(0, 0), Vec2F(4, 4), INFINITY}
};

vector<Object> map3 = {
    {Vec2F(8, 8), Vec2F(8, 8), INFINITY}
};