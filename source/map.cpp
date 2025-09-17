#include "map.hpp"

SDL_Color COLORS[4] = {
    {  0,   0,   0,   0},
    { 127, 127,  127, 255},
    {191, 191, 191, 255},
    {255, 255, 255, 255}
};

Map::Map()
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            tiles[x][y] = VOID;
        }
    }
}

void Map::draw(SDL_Renderer *renderer)
{
    SDL_FRect rect = {0, 0, TILE_SIZE, TILE_SIZE};
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            Vec2I screen_transform = rect_correction(screen_convertion(Vec2I(x, y)));
            rect.x = screen_transform.x;
            rect.y = screen_transform.y;
            
            SDL_Color color = COLORS[tiles[x][y]];
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}