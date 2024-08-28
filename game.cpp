#include <iostream>
#include <SDL.h>
#include "vec2.h"

using namespace std;

struct Hitbox {
    float w, h;
};

class Player {
        public:
            SDL_Rect rect;
            Hitbox hitbox;
            vec2f position;
            vec2f oldposition;
            vec2f acceleration = {0, 0};
            float friction = 0.8;
            bool onground = false;

            Player(vec2f basepos, int width, int height) {
                position = basepos;
                oldposition = basepos;
                hitbox.w = width;
                hitbox.h = height;
            }

            bool touchground() {
                return (position.y-hitbox.h/2 <= 0) ? true : false; 
            }

            void key_movement(const Uint8* keys) {
                float move = onground ? 16 : 1.6;
                if (onground && keys[SDL_SCANCODE_SPACE]){acceleration.y += 38;}
                if (keys[SDL_SCANCODE_D]){acceleration.x += move;}
                if (keys[SDL_SCANCODE_A]){acceleration.x -= move;}
            }

            void collision() {
                if (position.y-hitbox.h/2 < 0) position.y = hitbox.h/2;
                if (position.y+hitbox.h/2 > 64) position.y = 64-hitbox.h/2;
                if (position.x-hitbox.w/2 < 0) position.x = hitbox.w/2;
                if (position.x+hitbox.w/2 > 64) position.x = 64-hitbox.w/2;
            }

            void physic(float dt) {
                // Gravity Force
                if (!onground) {
                    acceleration.y -= 2;
                }

                //Update physic player
                vec2f velocity = position - oldposition;
                velocity.x *= onground ? 1-friction : 1;
                oldposition = position;
                position = acceleration*dt + velocity + position;
            
                collision();
            }

            void update(const Uint8* keys, float dt) {
                acceleration = {0, 0};
                onground = touchground();
                key_movement(keys);
                physic(dt);
            }

            void draw(SDL_Renderer* renderer, int* screenspace, int scale) {
                rect.x = (int)screenspace[0]-scale/2;
                rect.y = (int)screenspace[1]-scale/2;
                rect.w = (int)hitbox.w*scale;
                rect.h = (int)hitbox.h*scale;
                SDL_RenderFillRect(renderer, &rect);
            }
};

class TileMap {
    public:
        SDL_DisplayMode* display;
        int tiles[64][64];
        int tilesize = 40;

        TileMap(SDL_DisplayMode* dm) {
            display = dm;
            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {
                        tiles[i][j] = 0;
                    }

                }
        }

        void DisplayposToTilepos(int x, int y, int* result) {
            result[0] = x / tilesize;
            result[1] = (display->h - y) / tilesize;
        }
        void TileposToDislpaypos(float x, float y, int* result) {
            result[0] = (int)(x * tilesize);
            result[1] = (int)(-y * tilesize + display->h);
        }


        void draw(SDL_Renderer* renderer) {
            SDL_Rect tile;
            tile.w = tilesize;
            tile.h = tilesize;
            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {

                    if (tiles[i][j] > 0) {
                        int tile_pos[2];
                        TileposToDislpaypos((float)i, (float)j, tile_pos);
                        tile.x = tile_pos[0];
                        tile.y = tile_pos[1] - tilesize;

                        SDL_SetRenderDrawColor(renderer, 64, 128, 32, 255);
                        SDL_RenderFillRect(renderer, &tile);
                    }

                }
            }
        }
};

int main(int argc, char* argv[])
{    
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    int fps = DM.refresh_rate;

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 TimeScale Beta", 0, 0, DM.w, DM.h, SDL_WINDOW_FULLSCREEN
        );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    TileMap map(&DM);
    map.tiles[0][0] = 1;

    Player player(vec2f(16, 16), 1, 1);

    // Input handle
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    int mouse_x, mouse_y;
    Uint32 mouse = SDL_GetMouseState(&mouse_x, &mouse_y);

    Uint32 time;
    float dt = 1.0/fps;

    while (!quit) {
        time = SDL_GetTicks();

        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }

        // Mouse handle
        mouse = SDL_GetMouseState(&mouse_x, &mouse_y);

        if (mouse & SDL_BUTTON(1)) {
            if (0 <= mouse_x && mouse_x < DM.w && 0 <= mouse_y && mouse_y < DM.h) {
                int tile_pos[2];
                int mx = max(0, min(DM.w, mouse_x));
                int my = max(0, min(DM.h, mouse_y));
                map.DisplayposToTilepos(mx, my, tile_pos);
                map.tiles[tile_pos[0]][tile_pos[1]] = 1;
            }
        }
        if (mouse & SDL_BUTTON(3)) {
            if (0 <= mouse_x && mouse_x < DM.w && 0 <= mouse_y && mouse_y < DM.h) {
                int tile_pos[2];
                int mx = max(0, min(DM.w, mouse_x));
                int my = max(0, min(DM.h, mouse_y));
                map.DisplayposToTilepos(mx, my, tile_pos);
                map.tiles[tile_pos[0]][tile_pos[1]] = 0;
            }
        }

        player.update(keys, dt);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Draw the player
        int displaypos[2];
        map.TileposToDislpaypos(player.position.x, player.position.y, displaypos);
        player.draw(renderer, displaypos, map.tilesize);
        
        map.draw(renderer);

        SDL_RenderPresent(renderer);

        dt = (float)(SDL_GetTicks()-time)/1000;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
