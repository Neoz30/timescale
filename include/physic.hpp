#pragma once

#include <vector>
#include "vec2.hpp"
#include "collider.hpp"

using namespace std;


class PhysicWorld
{
    public:
    vector<Collider *> colliders;
    
    const Vec2F gravity = Vec2F(0.f, 0.f);
    const float air_friction = 0.05;
    const float friction = 0.2;
    float delta_time;

    PhysicWorld(float dt);

    void add_collider(Collider *collider);
    void add_colliders(vector<Collider *> colliders);
    void clear();

    void move_collider(Collider *collider);

    bool collision_detection(Collider *collider1, Collider *collider2);
    void collision_resolution(Collider *collider1, Collider *collider2);

    void step();
};