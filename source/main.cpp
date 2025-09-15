#include <SDL3/SDL.h>
#include "vec2.hpp"
using namespace std;

int main(int argc, char** argv)
{
    bool debugmode = false;
    if (argc == 2)
    {
        if (argv[1] == "debug") debugmode = true;
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Timescale", 960, 540, 0);
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

    Vec2 pos(50.f);
    SDL_FRect rect((float)pos.x, (float)pos.y, 50.f, 50.f);

    bool running = true;
    while (running)
    {
        SDL_Event *event;
        while (SDL_PollEvent(event))
        {
            if (event->type == SDL_EVENT_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}