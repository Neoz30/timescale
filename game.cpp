#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int main(int argc, const char* argv[])
{    
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int Width = DM.w * 0.75;
    int Height = DM.h * 0.75;
    auto midWidth = Width / 2;
    auto midHeight = Height / 2;

    int fps = 60;

    SDL_Window* window = SDL_CreateWindow("SDL2 TimeScale Beta",
        0, 0, Width, Height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect player;
    player.x = midWidth;
    player.y = midHeight;
    player.w = 50;
    player.h = 50;

    float x = midWidth;
    float y = midHeight;

    float vx = 0;
    float vy = 0;

    float ax = 0;
    float ay = 0;

    bool UP = false;
    bool RIGHT = false; 
    bool DOWN = false; 
    bool LEFT = false;

    bool lastUP = false;

    float scale;

    Uint32 time;
    Uint32 lasttime = SDL_GetTicks();
    float dt = 1.0/60;

    while (!quit)
    {
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

        ax = 0;
        ay = 0;

        // Move rect
        scale = 1 - (x + player.w/2 - midWidth) / midWidth;
        scale = min(1.0f, max(scale, 0.00005f));
        if (!lastUP && UP){ay -= 2;}
        if (RIGHT){x += 20*scale;}
        if (LEFT){x -= 20*scale;}

        lastUP = UP;

        if (player.y+player.h < Height) {
            ay += 0.1;
        }

        vx += ax;
        vy += ay;

        x += vx*dt*scale;
        y += vy*dt*scale;

        if (player.y+player.h > Height) {
            vy = 0;
            y = Height-player.h;
        }
        if (player.y < -1) {
            vy = 0;
            y = 0; 
        }
        if (player.x+player.w > Width) {
            vx = 0;
            x = Width-player.w; 
        }
        if (player.x < -1) {
            vx = 0;
            x = 0; 
        }

        player.x = (int)x;
        player.y = (int)y;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Show time field
        for (int i = 0; i <= midWidth; i++) {
            float ratio = (float)i/midWidth;
            SDL_SetRenderDrawColor(renderer, 34*ratio, 139*ratio, 34*ratio, 255);
            SDL_RenderDrawLine(renderer, i+midWidth, 0, i+midWidth, Height);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player);

        SDL_RenderPresent(renderer);

        lasttime = SDL_GetTicks();

        SDL_Delay(max((1000.0/60-(float)(lasttime-time)), 0.0));
        dt = SDL_GetTicks()-time;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
