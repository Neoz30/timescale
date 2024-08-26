#include <iostream>
#include <SDL.h>

using namespace std;

struct Player {
        SDL_Rect rect;
        float x, y;
        float velx, vely;
        float accx, accy;
        bool onground;
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

bool TileCollision(int tile_x, int tile_y, Player player) {
    float midsize = 1;
    return (player.x+midsize > tile_x && player.x-midsize < tile_x+1);
}

int main(int argc, char* argv[])
{    
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    int fps = DM.refresh_rate;

    SDL_Window* window = SDL_CreateWindow("SDL2 TimeScale Beta",
        0, 0, DM.w, DM.h, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TileMap map(&DM);
    map.tiles[0][0] = 1;

    Player player;
    player.rect.w = 80;
    player.rect.h = 80;

    player.x = 1;
    player.y = 1;
    player.velx = 0;
    player.vely = 0;
    player.accx = 0;
    player.accy = 0;

    player.onground = true;

    // Input handle
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    int mouse_x, mouse_y; 
    Uint32 mouse = SDL_GetMouseState(&mouse_x, &mouse_y);

    Uint32 time;
    Uint32 lasttime = SDL_GetTicks();
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

        player.accx = 0;
        player.accy = 0;

        // player in air
        if (player.y <= 1) {
            player.onground = true;
        } else {
            player.onground = false;
        }

        // Move rect
        if (player.onground && keys[SDL_SCANCODE_SPACE]){player.accy += 32;}
        if (keys[SDL_SCANCODE_D]){player.x += 16*dt;}
        if (keys[SDL_SCANCODE_A]){player.x -= 16*dt;}

        if (!player.onground) {
            player.accy -= 2;
        }

        player.velx += player.accx;
        player.vely += player.accy;

        player.x += player.velx*dt;
        player.y += player.vely*dt;

        if (player.y-1 < 0) {
            player.vely = 0;
            player.y = 1;
        }
        if (player.y+1 > 64) {
            player.vely = 0;
            player.y = 63;
        }
        if (player.x+1 > 64) {
            player.velx = 0;
            player.x = 63;
        }
        if (player.x-1 < 0) {
            player.velx = 0;
            player.x = 1; 
        }

        int display_player[2];
        map.TileposToDislpaypos(player.x, player.y, display_player);
        player.rect.x = (int)(display_player[0]-player.rect.w/2);
        player.rect.y = (int)(display_player[1]-player.rect.h/2);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player.rect);

        map.draw(renderer);

        SDL_RenderPresent(renderer);

        lasttime = SDL_GetTicks();
        
        SDL_Delay(max((1000.0/fps-(float)(lasttime-time)), 0.0));
        dt = (float)(SDL_GetTicks()-time)/1000;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
