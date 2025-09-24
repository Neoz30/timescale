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
    Vec2F reduced;

    if (abs(delta.x) > abs(delta.y))
    {
        reduced.x = (delta.x > 0) ? 1 : -1;
        dist = abs(delta.x) - object1->size.x / 2 - object2->size.x / 2;
    }
    else
    {
        reduced.y = (delta.y > 0) ? 1 : -1;
        dist = abs(delta.y) - object1->size.x / 2 - object2->size.x / 2;
    }

    dist /= 2;

    object1->position += -reduced * -dist;
    object1->velocity += -reduced * (0.5 * reduced.dot(object2->velocity) * object2->mass / object1->mass);
    object2->velocity += reduced * (0.5 * reduced.dot(object2->velocity));

    object2->position += reduced * -dist;
    object2->velocity += reduced * (0.5 * reduced.dot(object1->velocity) * object1->mass / object2->mass);
    object1->velocity += -reduced * abs(0.5 * reduced.dot(object2->velocity));
}

void PhysicWorld::step()
{
    for (Object *object : objects)
    {
        move_collider(object);
    }

    for (int i = 1; i < objects.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            collision_resolution(objects[i], objects[j]);
        }
    }
}
