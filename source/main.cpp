#include "vec2.hpp"
#include "physic.hpp"
#include "map.hpp"
#include "graphic.hpp"

using namespace std;

int main(int argc, char** argv)
{
    bool debugmode = false;
    if (argc == 2)
    {
        if (argv[1] == "debug") debugmode = true;
    }

    GraphicView view(1.f / 16);
    PhysicWorld physic(1.f / 50);

    for (int i = 0; i < map1.size(); i++)
    {
        physic.add_collider(&map1[i]);
    }
    
    Collider player(Vec2F(4, 4), Vec2F(0.75));
    physic.add_collider(&player);

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

            player.acceleration += want.normalize() * 25.f;

            physic.step();
        }

        view.draw_physic_colliders(&physic);
        view.render();
    }
    return 0;
}