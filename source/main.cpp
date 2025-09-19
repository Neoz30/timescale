#include <SDL3/SDL.h>
#include "vec2.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "physic.hpp"

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
    map.tiles[2][0] = GREY;
    map.tiles[3][0] = GREY;
    map.tiles[4][0] = LIGHT_GREY;
    map.tiles[5][0] = LIGHT_GREY;
    map.tiles[6][0] = WHITE;
    map.tiles[7][0] = WHITE;

    Entity entities[256];
    entities[0] = Entity(Vec2F(2, 0), 0.5, 0.5);

    bool key_dir[4] = {false, false, false, false};
    enum SDL_Scancode key_map[4] = {
        SDL_SCANCODE_W,
        SDL_SCANCODE_D,
        SDL_SCANCODE_S,
        SDL_SCANCODE_A
    };

    Uint64 previous_time = SDL_GetTicks();
    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (event.key.scancode == key_map[i]) key_dir[i] = true;
                }
            }
            if (event.type == SDL_EVENT_KEY_UP)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (event.key.scancode == key_map[i]) key_dir[i] = false;
                }
            }
        }

        Uint64 time = SDL_GetTicks();
        if (time - previous_time > 20)
        {
            float dt = 1.f / 50;

            Vec2F want = {0.f, 0.f};
            if (key_dir[0]) want.y += 1.f;
            if (key_dir[1]) want.x += 1.f;
            if (key_dir[2]) want.y -= 1.f;
            if (key_dir[3]) want.x -= 1.f;

            entities[0].acceleration += want.normalize() * 10.f;

            for (int i = 0; i < 256; i++)
            {
                entities[i].step(dt);
            }
            
            collision_resolution(&map, entities, 256);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map.draw(renderer);

        for (int i = 0; i < 256; i++)
        {
            entities[i].draw(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}