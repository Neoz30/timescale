#include "physic.hpp"

bool collision_detection(Vec2I tile, Entity *entity)
{
    return
    entity->position.x < tile.x + 1 &&
    entity->position.x + entity->width > tile.x &&
    entity->position.y < tile.y + 1 &&
    entity->position.y + entity->height > tile.y;
}

bool collision_detection(Entity *entity1, Entity *entity2)
{
    return
    entity1->position.x < entity2->position.x + entity2->width &&
    entity1->position.x + entity1->width > entity2->position.x &&
    entity1->position.y < entity2->position.y + entity2->height &&
    entity1->position.y + entity1->height > entity2->position.y;
}

void entity_collision(Entity *entity1, Entity *entity2)
{
    if (!collision_detection(entity1, entity2)) return;

    Vec2F delta(
        (entity2->position.x + entity2->width / 2) - (entity1->position.x + entity1->width / 2),
        (entity2->position.y + entity2->height / 2) - (entity1->position.y + entity1->height / 2)
    );

    float dist;
    Vec2F reduced;

    if (abs(delta.x) > abs(delta.y))
    {
        reduced.x = (delta.x > 0) ? 1 : -1;
        dist = abs(delta.x) - entity1->width / 2 - entity2->width / 2;
    }
    else
    {
        reduced.y = (delta.y > 0) ? 1 : -1;
        dist = abs(delta.y) - entity1->width / 2 - entity2->width / 2;
    }

    dist /= 2;

    entity1->position += -reduced * -dist;
    entity1->velocity += -reduced * abs(reduced.dot(entity2->velocity.normalize())) * entity2->velocity.length();

    entity2->position += reduced * -dist;
    entity2->velocity += reduced * abs(reduced.dot(entity2->velocity.normalize())) * entity2->velocity.length();
}

void map_collision(Map *map, Entity *entity)
{
    Vec2I downleft(entity->position.x, entity->position.y);
    Vec2I topright(entity->position.x, entity->position.y);
    downleft -= Vec2I(2);
    topright += Vec2I(4);

    for (int x = downleft.x; x < topright.x; x++)
    {
        if (x < 0 || x >= MAP_WIDTH) continue;
        for (int y = downleft.y; y < topright.y; y++)
        {
            if (y < 0 || y >= MAP_HEIGHT) continue;
            if (map->tiles[x][y] == VOID) continue;
            if (!collision_detection(Vec2I(x, y), entity)) continue;

            Vec2F delta(
                (entity->position.x + entity->width / 2) - (x + 0.5),
                (entity->position.y + entity->height / 2) - (y + 0.5)
            );

            float dist;
            Vec2F reduced;

            if (abs(delta.x) > abs(delta.y))
            {
                reduced.x = (delta.x > 0) ? 1 : -1;
                dist = abs(delta.x) - entity->width / 2 - 0.5;
            }
            else
            {
                reduced.y = (delta.y > 0) ? 1 : -1;
                dist = abs(delta.y) - entity->height / 2 - 0.5;
            }

            entity->position += reduced * -dist;
            entity->velocity += reduced * abs(reduced.dot(entity->velocity.normalize())) * entity->velocity.length();
        }
    }
}

void collision_resolution(Map *map, Entity *entities, int length)
{
    for (int i = 1; i < length; i++)
    {
        Entity *entity1 = &entities[i];
        if (!entity1->active) continue;

        for (int j = 0; j < i; j++)
        {
            Entity *entity2 = &entities[j];
            if (!entity2->active) continue;
            
            entity_collision(entity1, entity2);
        }
    }

    for (int i = 0; i < length; i++)
    {
        Entity *entity = &entities[i];
        if (!entity->active) return;

        map_collision(map, entity);
    }
}
