#include <iostream>
#include <SDL.h>

using namespace std;

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

    struct Player {
        SDL_Rect rect;
        float x, y;
        float velx, vely;
        float accx, accy;
        bool onground;
    };

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
        }

        player.accx = 0;
        player.accy = 0;

        // player in air
        if (player.y+player.rect.h >= Height) {
            player.onground = true;
        } else {
            player.onground = false;
        }

        // Move rect
        if (player.onground && UP){player.accy -= 2000;}
        if (RIGHT){player.x += 1200*dt;}
        if (LEFT){player.x -= 1200*dt;}

        if (!player.onground) {
            player.accy += 98;
        }

        player.velx += player.accx;
        player.vely += player.accy;

        player.x += player.velx*dt;
        player.y += player.vely*dt;

        if (player.y+player.rect.h > Height) {
            player.vely = 0;
            player.y = Height-player.rect.h;
        }
        if (player.y < 0) {
            player.vely = 0;
            player.y = 0; 
        }
        if (player.x+player.rect.w > Width) {
            player.velx = 0;
            player.x = Width-player.rect.w; 
        }
        if (player.x < 0) {
            player.velx = 0;
            player.x = 0; 
        }

        player.rect.x = (int)player.x;
        player.rect.y = (int)player.y;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player.rect);

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
