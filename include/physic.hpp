#pragma once

#include <vector>
#include "vec2.hpp"
#include "object.hpp"

using namespace std;

class PhysicWorld
{
    public:
    vector<Object *> objects;
    
    const Vec2F gravity = Vec2F(0.f, 0.f);
    const float air_friction = 0.05;
    const float friction = 0.2;
    float delta_time;

    PhysicWorld(float dt);

    void add_collider(Object *object);
    void add_colliders(vector<Object *> objects);
    void clear();

    void move_collider(Object *object);

    bool collision_detection(Object *object1, Object *objects2);
    void collision_resolution(Object *object1, Object *objects2);

    void step();
};