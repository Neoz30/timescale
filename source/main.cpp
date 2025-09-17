#include <SDL3/SDL.h>
#include "vec2.hpp"
#include "map.hpp"

using namespace std;

int main(int argc, char** argv)
{
    bool debugmode = false;
    if (argc == 2)
    {
        if (argv[1] == "debug") debugmode = true;
    }

    SDL_Init(SDL_INIT_VIDEO);

    const SDL_DisplayMode *DM = SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay());
    if (DM == NULL) {
        SDL_Log(SDL_GetError());
        return (1);
    }
    SCREEN_WIDTH = DM->w;
    SCREEN_HEIGHT = DM->h;
    change_screen_scale(1.f / 16);

    SDL_Window *window = SDL_CreateWindow("Timescale", DM->w, DM->h, SDL_WINDOW_FULLSCREEN);
    if (window == NULL)
    {
        SDL_Log(SDL_GetError());
        return (1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        SDL_Log(SDL_GetError());
        return (1);
    }

    Map map;
    map.tiles[0][0] = STONE;

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map.draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}