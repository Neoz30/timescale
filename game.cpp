#include <iostream>
#include <math.h>

#include "graphics.hpp"

using namespace std;

const float CS45 = sin(M_PI/4);

vec2f camerapos(0, 0);

class TileMap {
    public:
        SDL_DisplayMode* display;
        unsigned int tiles[64][64];
        int tilesize = 40;

        TileMap(SDL_DisplayMode* dm) {
            display = dm;

            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {
                        tiles[i][j] = 0;
                }
            }
            // Debug for view all map in camera
            //tilesize = 1.0/64*display->w;
        }

        void DisplayposToTilepos(int x, int y, int* result) {
            result[0] = x / tilesize;
            result[1] = (display->h - y) / tilesize;
        }
        void TileposToDislpaypos(float x, float y, int* result) {
            result[0] = (int)(x * tilesize);
            result[1] = (int)(-y * tilesize + display->h);
        }

        void draw(SDL_Renderer* renderer, SDL_Texture* texture) {
            SDL_Rect texturepos = {0, 0, 16, 16};
            SDL_Rect tile;
            tile.w = tilesize;
            tile.h = tilesize;
            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {

                    if (tiles[i][j] == 1) {
                        int tile_pos[2];
                        TileposToDislpaypos((float)i-camerapos.x, (float)j, tile_pos);
                        tile.x = tile_pos[0];
                        tile.y = tile_pos[1] - tilesize;

                        int code = 0;
                        if (j+1 < 64) code |= tiles[i][j+1];
                        if (i+1 < 64) code |= (tiles[i+1][j] << 1);
                        if (j-1 >= 0) code |= (tiles[i][j-1] << 2);
                        if (i-1 >= 0) code |= (tiles[i-1][j] << 3);

                        texturepos.x = (0b0011 & code)*16;
                        texturepos.y = (code >> 2)*16;

                        SDL_RenderCopy(renderer, texture, &texturepos, &tile);
                    }
                }
            }
        }
};

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
            bool onground = false;

            Player(vec2f basepos, int width, int height) {
                position = basepos;
                oldposition = basepos;
                hitbox.w = width;
                hitbox.h = height;
            }

            bool touchground(TileMap* map) {
                vec2i underblock(position.x, position.y-1);
                int offset = (position.x-underblock.x < 0.5) ? -1 : 1;
                if (position.x-underblock.x == 0.5) offset = 0;
                vec2i underblock2(position.x+offset, position.y-1);
                if (map->tiles[underblock.x][underblock.y] == 0 && map->tiles[underblock2.x][underblock2.y] == 0) {
                    return false;
                }

                float deltaY = position.y-(underblock.y+0.5);
                if (deltaY <= 1.05 && 0 <= deltaY) {return true;}
                return false;
            }

            void key_movement(const Uint8* keys, float dt) {
                if (onground && keys[SDL_SCANCODE_SPACE]){
                    acceleration.y += 2048;
                }
                if (keys[SDL_SCANCODE_D]){acceleration.x += 32;}
                if (keys[SDL_SCANCODE_A]){acceleration.x -= 32;}
            }

            void edge_collision() {
                if (position.y-hitbox.h/2 < 0) position.y = hitbox.h/2;
                if (position.y+hitbox.h/2 > 64) position.y = 64-hitbox.h/2;
                if (position.x-hitbox.w/2 < 0) position.x = hitbox.w/2;
                if (position.x+hitbox.w/2 > 64) position.x = 64-hitbox.w/2;
            }

            void block_collision(TileMap* map) {
                for (int dx = -2; dx <= 2; dx++) {
                    for (int dy = -2; dy <= 2; dy++) {
                        vec2i player = {(int)position.x, (int)position.y};
                        vec2i block = {player.x+dx, player.y+dy};
                        if (block.x < 0 || block.x > 63 || block.y < 0 || block.y > 63) {
                            continue;
                        }
                        unsigned int blockstate = map->tiles[block.x][block.y];
                        if (blockstate) {continue;}

                        vec2 veldir = (oldposition - position).normalize();
                        for (int i = 0; i < 4; i++) {
                            vec2f side(0, 0);
                            vec2f a(0, 0);
                            
                            if (i == 0) {
                                side.x = 0; side.y = 1;
                                a.x = block.x; a.y = block.y+1;
                            }
                            if (i == 1) {
                                side.x = 1; side.y = 0;
                                a.x = block.x+1; a.y = block.y+1;
                            }
                            if (i == 2) {
                                side.x = 0; side.y = -1;
                                a.x = block.x+1; a.y = block.y;
                            }
                            if (i == 4) {
                                side.x = -1;side.y = 0;
                                a.x = block.x; a.y = block.y;
                            }
                            
                            if (veldir.det(side) == 0 || veldir.dot(side) > 0) {continue;}
                        }
                    }
                }
            }

            void physic(float dt, TileMap* map) {
                // Gravity Force
                acceleration.y -= 64;

                //Update physic player
                vec2f velocity = position - oldposition;
                
                vec2f inverse_speed = velocity/-dt;
                float speedfriction = 0.1f*pow(inverse_speed.length(), 2);
                vec2f kineticfriction = vec2f(inverse_speed).normalize()*speedfriction;
                acceleration += kineticfriction;
                if (onground) {
                    vec2f staticfriction = inverse_speed.normalize()*16;
                    acceleration += staticfriction;
                }

                oldposition = position;
                position = acceleration*dt*dt + velocity + position;
            
                edge_collision();
                block_collision(map);
            }

            void update(const Uint8* keys, float dt, TileMap* map) {
                acceleration = {0, 0};
                key_movement(keys, dt);
                onground = touchground(map);
                physic(dt, map);
            }

            void draw(SDL_Renderer* renderer, int* screenspace, int scale) {
                rect.x = (int)screenspace[0]-scale/2;
                rect.y = (int)screenspace[1]-scale/2;
                rect.w = (int)hitbox.w*scale;
                rect.h = (int)hitbox.h*scale;
                SDL_RenderFillRect(renderer, &rect);
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
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_PNG);

    SDL_Surface* block = IMG_Load("./textures/celeste_tileset/grass.png");
    SDL_Surface* background = IMG_Load("./textures/mountain_background.png");
    if (!block || !background) cout << "TextureSet not loaded !" << endl;

    SDL_Texture* blockTexture = SDL_CreateTextureFromSurface(renderer, block);
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);

    TileMap map(&DM);

    Player player(vec2f(16, 16), 1, 1);
    
    for (int i = 0; i < 64; i++) {
        map.tiles[i][0] = 1;
    }

    vec2f camerasize((float)DM.w/map.tilesize, (float)DM.h/map.tilesize);

    // Input handle
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    int mouse_x, mouse_y;
    Uint32 mouse = SDL_GetMouseState(&mouse_x, &mouse_y);

    Uint32 time;
    float dt = 1.0/fps;
    Uint32 graphiclastframe = 16;

    while (!quit) {
        // Camera position
        float playercam = player.position.x-(camerapos.x+camerasize.x/2);
        if (playercam > 0) {
            camerapos.x += 0.01*max(abs(playercam)-10,0.f);
        } else {
            camerapos.x -= 0.01*max(abs(playercam)-10,0.f);
        }

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
        if (mouse && (0 <= mouse_x && mouse_x < DM.w && 0 <= mouse_y && mouse_y < DM.h)) {
            int tile_pos[2];
            int mx = max(0, min(DM.w, mouse_x)) + camerapos.x*map.tilesize;
            int my = max(0, min(DM.h, mouse_y)) + camerapos.y*map.tilesize;
            map.DisplayposToTilepos(mx, my, tile_pos);

            if (mouse & SDL_BUTTON(1)) map.tiles[tile_pos[0]][tile_pos[1]] = 1;
            if (mouse & SDL_BUTTON(3)) map.tiles[tile_pos[0]][tile_pos[1]] = 0;
        }

        player.update(keys, dt, &map);

        if (time-graphiclastframe > 1000.0/fps) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            // Draw the player
            int displaypos[2];
            map.TileposToDislpaypos(player.position.x - camerapos.x, player.position.y, displaypos);
            player.draw(renderer, displaypos, map.tilesize);
            
            map.draw(renderer, blockTexture);

            SDL_RenderPresent(renderer);
            graphiclastframe = time;
        }

        SDL_Delay(4);
        dt = (float)(SDL_GetTicks()-time)/1000;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_FreeSurface(block);
    SDL_DestroyTexture(blockTexture);
    SDL_FreeSurface(background);
    SDL_DestroyTexture(backgroundTexture);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
