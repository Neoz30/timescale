#include "physic.hpp"

PhysicWorld::PhysicWorld(float dt)
{
    delta_time = dt;
}

void PhysicWorld::add_collider(Collider *collider)
{
    colliders.push_back(collider);
}

void PhysicWorld::add_colliders(vector<Collider *> colliders)
{
    for (Collider *collider: colliders)
    {
        add_collider(collider);
    }
}

void PhysicWorld::clear()
{
    while (!colliders.empty())
    {
        colliders.pop_back();
    }
}

#include <stdio.h>
void PhysicWorld::move_collider(Collider *collider)
{
    float len = collider->velocity.length();

    collider->acceleration -= collider->velocity.normalize() * 0.5 * air_friction * (len * len);
    collider->acceleration += gravity;

    collider->velocity += collider->acceleration * delta_time;
    collider->position += collider->velocity * delta_time;

    collider->acceleration.x = 0.f;
    collider->acceleration.y = 0.f;
}

bool PhysicWorld::collision_detection(Collider *collider1, Collider *collider2)
{
    return
    collider1->position.x < collider2->position.x + collider2->size.x &&
    collider1->position.x + collider1->size.x > collider2->position.x &&
    collider1->position.y < collider2->position.y + collider2->size.y &&
    collider1->position.y + collider1->size.y > collider2->position.y;
}

void PhysicWorld::collision_resolution(Collider *collider1, Collider *collider2)
{
    if (!collision_detection(collider1, collider2)) return;

    Vec2F delta(
        (collider2->position.x + collider2->size.x / 2) - (collider1->position.x + collider1->size.x / 2),
        (collider2->position.y + collider2->size.y / 2) - (collider1->position.y + collider1->size.y / 2)
    );

    float dist;
    Vec2F reduced;

    if (abs(delta.x) > abs(delta.y))
    {
        reduced.x = (delta.x > 0) ? 1 : -1;
        dist = abs(delta.x) - collider1->size.x / 2 - collider2->size.x / 2;
    }
    else
    {
        reduced.y = (delta.y > 0) ? 1 : -1;
        dist = abs(delta.y) - collider1->size.x / 2 - collider2->size.x / 2;
    }

    dist /= 2;

    collider1->position += -reduced * -dist;
    collider1->velocity += -reduced * abs(reduced.dot(collider2->velocity));

    collider2->position += reduced * -dist;
    collider2->velocity += reduced * abs(reduced.dot(collider2->velocity));
}

void PhysicWorld::step()
{
    for (Collider *collider : colliders)
    {
        move_collider(collider);
    }

    for (int i = 1; i < colliders.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            collision_resolution(colliders[i], colliders[j]);
        }
    }
}
