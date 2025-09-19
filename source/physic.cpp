#include "physic.hpp"

void collision_resolution(Map *map, Entity *entities, int length)
{
    for (int i = 0; i < length; i++)
    {
        Entity *entity = &entities[i];
        if (!entity->active) return;

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

                map->tiles[x][y] = collision_detection(Vec2I(x, y), entity) ? WHITE : GREY;
            }
        }

    }
}

bool collision_detection(Vec2I tile, Entity *entity)
{
    return
    entity->position.x < tile.x + 1 &&
    entity->position.x + entity->width > tile.x &&
    entity->position.y < tile.y + 1 &&
    entity->position.y + entity->height > tile.y;
}
