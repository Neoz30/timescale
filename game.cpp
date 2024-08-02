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
        int tiles[64][64];
        int tilesize = 40;
        int cam_x = 0, cam_y = 0;

        TileMap() {
            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {
                        tiles[i][j] = 0;
                    }

                }
        }

        void pos_to_tilemap(int x, int y, int* result) {
            result[0] = x / tilesize;
            result[1] = y / tilesize;
        } 

        void display(SDL_Renderer* renderer) {
            SDL_Rect tile;
            tile.w = tilesize;
            tile.h = tilesize;
            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {

                    if (tiles[i][j] > 0) {
                        tile.x = tilesize*i - cam_x;
                        tile.y = -tilesize*(j+1) + 1080 - cam_y;

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

    float displayscale = 1;

    int Width = DM.w * displayscale;
    int Height = DM.h * displayscale;
    auto midWidth = Width / 2;
    auto midHeight = Height / 2;

    int fps = 60;

    SDL_Window* window = SDL_CreateWindow("SDL2 TimeScale Beta",
        0, 0, Width, Height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TileMap map;
    map.tiles[0][0] = 1;

    Player player;
    player.rect.x = midWidth;
    player.rect.y = midHeight;
    player.rect.w = 75 * displayscale;
    player.rect.h = 75 * displayscale;

    player.x = midWidth;
    player.y = midHeight;
    player.velx = 0;
    player.vely = 0;
    player.accx = 0;
    player.accy = 0;

    player.onground = true;

    bool UP = false;
    bool RIGHT = false; 
    bool DOWN = false; 
    bool LEFT = false;

    bool Button1 = false;
    bool Button2 = false;

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
            
            // Keyboard input update
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_z:
                        UP = true;
                        break;
                    case SDLK_d:
                        RIGHT = true;
                        break;
                    case SDLK_s:
                        DOWN = true;
                        break;
                    case SDLK_q:
                        LEFT = true;
                        break;
                }
                break;
            
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_z:
                        UP = false;
                        break;
                    case SDLK_d:
                        RIGHT = false;
                        break;
                    case SDLK_s:
                        DOWN = false;
                        break;
                    case SDLK_q:
                        LEFT = false;
                        break;
                }
                break;
            // Mouse button update;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    Button1 = true;
                    break;
                
                case SDL_BUTTON_RIGHT:
                    Button2 = true;
                    break;
                
                default:
                    break;
                }
                break;
            
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    Button1 = false;
                    break;
                
                case SDL_BUTTON_RIGHT:
                    Button2 = false;
                    break;
                
                default:
                    break;
                }
                break;
        }

        if (Button1) {
            int tile_pos[2];
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            mx = max(0, min(Width, mx + map.cam_x));
            my = max(0, min(Height, Height - my + map.cam_y));
            map.pos_to_tilemap(mx, my, tile_pos);
            map.tiles[tile_pos[0]][tile_pos[1]] = 1;
        }
        if (Button2) {
            int tile_pos[2];
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            mx = max(0, min(Width, mx + map.cam_x));
            my = max(0, min(Height, Height - my + map.cam_y));
            map.pos_to_tilemap(mx, my, tile_pos);
            map.tiles[tile_pos[0]][tile_pos[1]] = 0;
        }

        player.accx = 0;
        player.accy = 0;

        // player in air
        if (player.y-player.rect.h/2 <= 0) {
            player.onground = true;
        } else {
            player.onground = false;
        }

        // Move rect
        if (player.onground && UP){player.accy += 2000;}
        if (RIGHT){player.x += 1200*dt;}
        if (LEFT){player.x -= 1200*dt;}

        if (!player.onground) {
            player.accy -= 98;
        }

        player.velx += player.accx;
        player.vely += player.accy;

        player.x += player.velx*dt;
        player.y += player.vely*dt;

        if (player.y-player.rect.h/2 < 0) {
            player.vely = 0;
            player.y = player.rect.h/2;
        }
        if (player.y+player.rect.h/2 > Height) {
            player.vely = 0;
            player.y = Height-player.rect.h/2;
        }
        if (player.x+player.rect.w/2 > Width) {
            player.velx = 0;
            player.x = Width-player.rect.w/2;
        }
        if (player.x-player.rect.w/2 < 0) {
            player.velx = 0;
            player.x = player.rect.w/2; 
        }

        map.cam_x += player.x - midWidth;
        player.x = midWidth;

        player.rect.x = (int)(player.x-player.rect.h/2);
        player.rect.y = (int)(-player.y+Height-player.rect.h/2);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player.rect);

        map.display(renderer);

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
