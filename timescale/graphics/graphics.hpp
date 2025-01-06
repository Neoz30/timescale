#pragma once

#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

#include <libmath/vec2.hpp>
#include <game/game.hpp>

const unsigned char CAM_MODE_STATIC = 0;
const unsigned char CAM_MODE_DYNAMIC = 1;

class Camera {
    public:
        Vec2 position;
        Vec2 view;
        unsigned char mode;

        Camera();

        void set_view(SDL_DisplayMode* displaymode, int pxpertile);

        void step(Vec2 player_pos);
};

class Graphism {
    public:
        SDL_DisplayMode DM;
        SDL_Window* window;
        SDL_Renderer* renderer;

        Camera cam;

        int FPS;
        int pxpertile;

        Graphism();
        ~Graphism();

        void screen_to_tile(int x, int y, int result[2]);

        void tile_to_screen(float x, float y, int result[2]);

        void fill_black();

        void update();

        void draw_background();

        void draw_terrain(TileMap* map);

        void draw_player(Vec2 player_pos, float pwidth, float pheight);

        void draw_awaymob(Vec2 position, float pwidth, float pheight);

        void draw_debugblock_border(int x, int y, SDL_Color color);

    private:
        SDL_Texture* block;
        SDL_Texture* background;

        void LoadTextures();
};