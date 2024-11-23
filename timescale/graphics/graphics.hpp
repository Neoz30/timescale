#pragma once

#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <libmath/vec2.hpp>

const unsigned char CAM_MODE_STATIC = 0;
const unsigned char CAM_MODE_DYNAMIC = 1;

class Camera {
    public:
        Vec2 position;
        Vec2 view;
        unsigned char mode;

        Camera() {mode = 0;}

        void set_view(SDL_DisplayMode* displaymode, int pxpertile) {
            view.x = (float)displaymode->w/pxpertile;
            view.y = (float)displaymode->h/pxpertile;
            cout << view.x << " " << view.y << endl;
        }

        void step(Vec2 player_pos) {
            switch (mode) {
            case CAM_MODE_STATIC:
                break;
            case CAM_MODE_DYNAMIC:
                float playercam = player_pos.x-(position.x+view.x/2);
                if (playercam > 0) {
                    position.x += max(
                        (10.f*(4*playercam-view.x)) / (view.x*(0.5f*view.x-playercam)), 0.f
                        );
                } else {
                    position.x -= max(
                        (10.f*(-4*playercam-view.x)) / (view.x*(0.5f*view.x+playercam)), 0.f
                        );
                }
                break;
            }
        }
};

class Graphism {
    public:
        SDL_DisplayMode DM;
        SDL_Window* window;
        SDL_Renderer* renderer;

        Camera cam;

        int FPS;
        int pxpertile;

        Graphism() {
            SDL_Init(SDL_INIT_VIDEO);
            IMG_Init(IMG_INIT_PNG);

            SDL_GetCurrentDisplayMode(0, &DM);
            FPS = DM.refresh_rate;
            window = SDL_CreateWindow(
                "SDL2 TimeScale Beta",
                0, 0, DM.w, DM.h,
                SDL_WINDOW_FULLSCREEN
            );
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            LoadTextures();
            pxpertile = 40;
            cam.set_view(&DM, pxpertile);
            cam.mode = CAM_MODE_DYNAMIC;
        }

        ~Graphism() {
            delete &DM, &cam, &FPS, &pxpertile;
            
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);

            SDL_DestroyTexture(block);
            SDL_DestroyTexture(background);

            IMG_Quit();
            SDL_Quit();
        }

        void screen_to_tile(int x, int y, int result[2]) {
            result[0] = x / pxpertile;
            result[1] = (DM.h - y) / pxpertile;
        }

        void tile_to_screen(float x, float y, int result[2]) {
            result[0] = (int)(x * pxpertile);
            result[1] = (int)(-y * pxpertile + DM.h);
        }

        void fill_black() {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        }

        void update() {
            SDL_RenderPresent(renderer);
        }

        void draw_background() {
            SDL_RenderCopy(renderer, background, NULL, NULL);
        }

        void draw_terrain(unsigned int tiles[64][64]) {
            SDL_Rect texturepos = {0, 0, 16, 16};
            SDL_Rect tile;
            tile.w = pxpertile;
            tile.h = pxpertile;
            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {

                    if (tiles[i][j]) {
                        int tile_pos[2];
                        tile_to_screen((float)i-cam.position.x, (float)j, tile_pos);
                        tile.x = tile_pos[0];
                        tile.y = tile_pos[1] - pxpertile;

                        int code = 0;
                        if (j+1 < 64) code |= tiles[i][j+1];
                        if (i+1 < 64) code |= (tiles[i+1][j] << 1);
                        if (j-1 >= 0) code |= (tiles[i][j-1] << 2);
                        if (i-1 >= 0) code |= (tiles[i-1][j] << 3);

                        texturepos.x = (0b0011 & code)*16;
                        texturepos.y = (code >> 2)*16;

                        SDL_RenderCopy(renderer, block, &texturepos, &tile);
                    }
                }
            }
        }

        void draw_player(Vec2 player_pos, float pwidth, float pheight) {
            int toscreen[2];
            tile_to_screen(player_pos.x-cam.position.x, player_pos.y, toscreen);

            SDL_Rect rect;
            rect.x = (int)toscreen[0]-pxpertile/2;
            rect.y = (int)toscreen[1]-pxpertile/2;
            rect.w = (int)pwidth*pxpertile;
            rect.h = (int)pheight*pxpertile;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

    private:
        SDL_Texture* block;
        SDL_Texture* background;

        void LoadTextures() {
            SDL_Surface* blockSurface = IMG_Load("./textures/celeste_tileset/grass.png");
            if (!blockSurface) cout << "Block textures not finded !" << endl;
            SDL_Surface* backgroundSurface = IMG_Load("./textures/mountain_background.png");
            if (!backgroundSurface) cout << "Beckground texture not finded !" << endl;

            block = SDL_CreateTextureFromSurface(renderer, blockSurface);
            background = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
            SDL_FreeSurface(blockSurface);
            SDL_FreeSurface(backgroundSurface);
        }
};
