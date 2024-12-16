#include <iostream>
#include <math.h>

#include <libmath/vec2.hpp>
#include <graphics/graphics.hpp>

using namespace std;

const float CS45 = sqrt(2)/2;

class TileMap {
    public:
        unsigned int tiles[64][64];

        TileMap() {
            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {
                        tiles[i][j] = 0;
                }
            }
        }
};

struct Hitbox {
    float w, h;
};

class Player {
    public:
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
            int underblock[2] = {(int)position.x, (int)position.y-1};
            int offset = (position.x-underblock[0] < 0.5) ? -1 : 1;
            if (position.x-underblock[0] == 0.5) offset = 0;
            int underblock2[2] = {(int)position.x+offset, (int)position.y-1};
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
                    int block[2] = {(int)position.x+dx, (int)position.y+dy};
                    if (block[0] < 0 || block[0] > 63 || block[1] < 0 || block[1] > 63) {
                        continue;
                    }

                    unsigned int blockstate = map->tiles[block[0]][block[1]];

                    if (blockstate == 1 && block_detection(block[0], block[1])) {                          
                        Vec2 delta = {(float)block[0]-position.x+0.5f, (float)block[1]-position.y+0.5f};
                        //Vec2 dir = Vec2(delta).normalize();

                        if (delta.x > abs(delta.y)) {position.x -= hitbox.w/2+0.5 - delta.x;}
                        if (-delta.x > abs(delta.y)) {position.x += hitbox.w/2+0.5 + delta.x;}
                        if (delta.y > abs(delta.x)) {position.y -= hitbox.h/2+0.5 - delta.y;}
                        if (-delta.y > abs(delta.x)) {position.y += hitbox.h/2+0.5 + delta.y;}
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
            acceleration += kineticfriction;

            if (onground) {
                Vec2 staticfriction = inverse_speed.normalize()*16;
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
};

int main(int argc, char* argv[])
{    
    bool quit = false;
    SDL_Event event;

    Graphism gamescreen;

    TileMap map;

    Player player(Vec2(16, 16), 1, 1);
    
    for (int i = 0; i < 64; i++) {
        map.tiles[i][0] = 1;
    }

    // Input handle
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    int mouse_x, mouse_y;
    Uint32 mouse = SDL_GetMouseState(&mouse_x, &mouse_y);

    Uint32 time;
    float dt = 1.0/gamescreen.FPS;
    Uint32 graphiclastframe = 16;

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
        if (mouse && (0 <= mouse_x && mouse_x < gamescreen.DM.w && 0 <= mouse_y && mouse_y < gamescreen.DM.h)) {
            int tile_pos[2];
            gamescreen.screen_to_tile(
                mouse_x + gamescreen.cam.position.x*gamescreen.pxpertile,
                mouse_y + gamescreen.cam.position.y*gamescreen.pxpertile,
                tile_pos
            );

            if (0 <= tile_pos[0] && tile_pos[0] < 64 && 0 <= tile_pos[1] && tile_pos[1] < 64) {
                if (mouse & SDL_BUTTON(1)) map.tiles[tile_pos[0]][tile_pos[1]] = 1;
                if (mouse & SDL_BUTTON(3)) map.tiles[tile_pos[0]][tile_pos[1]] = 0;
            }
        }

        player.update(keys, dt, &map);

        if (time-graphiclastframe > 1000.0/gamescreen.FPS) {
            gamescreen.cam.step(player.position);

            gamescreen.fill_black();
            gamescreen.draw_background();
            
            gamescreen.draw_player(player.position, player.hitbox.w, player.hitbox.h);
            gamescreen.draw_terrain(map.tiles);

            gamescreen.update();
            graphiclastframe = time;
        }

        SDL_Delay(4);
        dt = (float)(SDL_GetTicks()-time)/1000;
    }

    return 0;
}
