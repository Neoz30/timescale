#pragma once
#include "vec2.hpp"
#include "map.hpp"
#include "entity.hpp"
using namespace std;

bool collision_detection(Vec2I tile, Entity *entity);
bool collision_detection(Entity *entity1, Entity *entity2);

void entity_collision(Entity *entity1, Entity *entity2);
void map_collision(Map *map, Entity *entity);
void collision_resolution(Map *map, Entity *entities, int length);