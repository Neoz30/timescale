#pragma once
#include "vec2.hpp"
#include "map.hpp"
#include "entity.hpp"
using namespace std;

enum DIRECTION
{
    NONE,
    TOP,
    RIGHT,
    DOWN,
    LEFT
};

void collision_resolution(Map *map, Entity *entities, int length);
bool collision_detection(Vec2I tile, Entity *entity);