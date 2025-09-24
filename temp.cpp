#include "collider.hpp"
#include "physic.hpp"

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