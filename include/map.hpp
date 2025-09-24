#pragma once

#include <vector>
#include "collider.hpp"

using namespace std;

vector<Collider> map1 = {
    Collider(Vec2F(0, 0), Vec2F(8, 2)),
    Collider(Vec2F(0, 16), Vec2F(8, 2))
};

vector<Collider> map2 = {
    {Vec2F(0, 0), Vec2F(4, 4)}
};

vector<Collider> map3 = {
    {Vec2F(8, 8), Vec2F(8, 8)}
};