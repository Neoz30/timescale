#pragma once
#include <SDL3/SDL.h>
#include "transforms.hpp"

using namespace std;

const int MAP_WIDTH = 256;
const int MAP_HEIGHT = 256;

enum Tile
{
    VOID,
    GREY,
    LIGHT_GREY,
    WHITE,
};

extern SDL_Color COLORS[4];

class Map
{
    public:
    enum Tile tiles[MAP_WIDTH][MAP_HEIGHT];

    Map();
    void draw(SDL_Renderer *renderer);
};