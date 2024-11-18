#include <iostream>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>

#include <libmath/vec2.hpp>

using namespace std;



const float CS45 = sqrt(2)/2;

Vec2 camerapos(0, 0);

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

                    if (tiles[i][j]) {
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
            Vec2 position;
            Vec2 oldposition;
            Vec2 acceleration = {0, 0};
            bool onground = false;

            Player(Vec2 basepos, int width, int height) {
                position = basepos;
                oldposition = basepos;
                hitbox.w = width;
                hitbox.h = height;
            }

            bool touchground(TileMap* map) {
                int underblock[2] = {position.x, position.y-1};
                int offset = (position.x-underblock[0] < 0.5) ? -1 : 1;
                if (position.x-underblock[0] == 0.5) offset = 0;
                int underblock2[2] = {position.x+offset, position.y-1};
                if (map->tiles[underblock[0]][underblock[1]] == 0 && map->tiles[underblock2[0]][underblock2[1]] == 0) {
                    return false;
                }

                float deltaY = position.y-(underblock[1]+0.5);
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

            bool block_detection(int blockX, int blockY) {
                return position.x-hitbox.w/2 < blockX+1 && position.x+hitbox.w/2 > blockX &&
                position.y-hitbox.h/2 < blockY+1 && position.y+hitbox.h/2 > blockY;
            }

            void block_collision(TileMap* map) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        Vec2 player = {(int)position.x, (int)position.y};
                        int block[2] = {player.x+dx, player.y+dy};
                        if (block[0] < 0 || block[0] > 63 || block[1] < 0 || block[1] > 63) {
                            continue;
                        }

                        unsigned int blockstate = map->tiles[block[0]][block[1]];

                        if (blockstate == 1 && block_detection(block[0], block[1])) {                          
                            Vec2 delta = {(float)block[0]-position.x+0.5f, (float)block[1]-position.y+0.5f};
                            Vec2 dir = Vec2(delta).normalize();

                            if (dir.x > CS45+0.05) {position.x -= hitbox.w/2+0.5 - delta.x;}
                            if (dir.x < -CS45-0.05) {position.x += hitbox.w/2+0.5 + delta.x;}
                            if (dir.y > CS45+0.05) {position.y -= hitbox.h/2+0.5 - delta.y;}
                            if (dir.y < -CS45-0.05) {position.y += hitbox.h/2+0.5 + delta.y;}
                        }
                    }
                }
            }

            void physic(float dt, TileMap* map) {
                // Gravity Force
                acceleration.y -= 64;

                //Update physic player
                Vec2 velocity = position - oldposition;
                
                Vec2 inverse_speed = velocity/-dt;
                float speedfriction = 0.1f*pow(inverse_speed.length(), 2);
                Vec2 kineticfriction = Vec2(inverse_speed).normalize()*speedfriction;
                acceleration = kineticfriction + acceleration;
                cout << kineticfriction.x << " " << kineticfriction.y << endl;
                if (onground) {
                    Vec2 staticfriction = inverse_speed.normalize()*16;
                    acceleration = staticfriction + acceleration;
                }

                cout << acceleration.x << " " << acceleration.y << endl;
                oldposition = position;
                position = acceleration*dt*dt + velocity + position; // This line make crash the game ???
            
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

    Player player(Vec2(16, 16), 1, 1);
    
    for (int i = 0; i < 64; i++) {
        map.tiles[i][0] = 1;
    }

    Vec2 camerasize((float)DM.w/map.tilesize, (float)DM.h/map.tilesize);

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
