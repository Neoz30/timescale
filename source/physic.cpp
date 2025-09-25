#include "physic.hpp"

PhysicWorld::PhysicWorld(float dt)
{
    delta_time = dt;
}

void PhysicWorld::add_collider(Object *object)
{
    objects.push_back(object);
}

void PhysicWorld::add_colliders(vector<Object *> objects)
{
    for (Object *object: objects)
    {
        add_collider(object);
    }
}

void PhysicWorld::clear()
{
    while (!objects.empty())
    {
        objects.pop_back();
    }
}

void PhysicWorld::move_collider(Object *object)
{
    float len = object->velocity.length();

    object->force -= object->velocity.normalize() * 0.5 * air_friction * (len * len);

    object->velocity += (object->force / object->mass + gravity) * delta_time;
    object->position += object->velocity * delta_time;

    object->force.x = 0.f;
    object->force.y = 0.f;
}

bool PhysicWorld::collision_detection(Object *object1, Object *object2)
{
    return
    object1->position.x < object2->position.x + object2->size.x &&
    object1->position.x + object1->size.x > object2->position.x &&
    object1->position.y < object2->position.y + object2->size.y &&
    object1->position.y + object1->size.y > object2->position.y;
}

void PhysicWorld::collision_resolution(Object *object1, Object *object2)
{
    if (!collision_detection(object1, object2)) return;

    Vec2F delta(
        (object2->position.x + object2->size.x / 2) - (object1->position.x + object1->size.x / 2),
        (object2->position.y + object2->size.y / 2) - (object1->position.y + object1->size.y / 2)
    );

    float dist;
    Vec2F n;

    if (Vec2F(abs(delta.x), abs(delta.y)).det(object1->size * object2->size) > 0)
    {
        n.x = (delta.x > 0) ? 1 : -1;
        dist = object1->size.x / 2 + object2->size.x / 2 - abs(delta.x);
    }
    else
    {
        n.y = (delta.y > 0) ? 1 : -1;
        dist = object1->size.y / 2 + object2->size.y / 2 - abs(delta.y);
    }

    Vec2F relative_vel = object2->velocity - object1->velocity;
    float rvel_dot = relative_vel.dot(n);

    if (rvel_dot > 0) return;
    
    float invM1 = (object1->mass) ? 1.f / object1->mass : 0.f;
    float invM2 = (object2->mass) ? 1.f / object2->mass : 0.f;

    Vec2F correction = n * max(dist - 0.01f, 0.f) / (invM1 + invM2) * 0.5;
    object1->position -= correction * invM1;
    object2->position += correction * invM2;

    float elasticity = min(object1->elasticity, object2->elasticity);
    float j = (-(1 + elasticity) * rvel_dot) / (invM1 + invM2);

    Vec2F impulse = n * j;
    object1->velocity -= impulse * invM1;
    object2->velocity += impulse * invM2;
}

void PhysicWorld::step()
{
    for (Object *object : objects)
    {
        if (!object->fixed) move_collider(object);
    }

    for (int i = 1; i < objects.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            collision_resolution(objects[i], objects[j]);
        }
    }
}
