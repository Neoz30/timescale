#include <iostream>
using namespace std;

#include <libmath/vec2.hpp>
#include <game/game.hpp>
#include <graphics/graphics.hpp>


int main(int argc, char* argv[])
{    
    bool quit = false;
    SDL_Event event;

    Graphism gamescreen;

    TileMap map;

    Player player(Vec2(16, 16), 1, 1);

    AwayMob firstmob(Vec2(4, 32));
    
    for (int i = 0; i < 64; i++) {
        map.tiles[i][0].id = 1;
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
                if (mouse & SDL_BUTTON(1)) map.tiles[tile_pos[0]][tile_pos[1]].id = 1;
                if (mouse & SDL_BUTTON(3)) map.tiles[tile_pos[0]][tile_pos[1]].id = 0;
            }
        }

        // Player control
        player.controller[1] = keys[SDL_SCANCODE_D];
        player.controller[3] = keys[SDL_SCANCODE_A];
        player.controller[4] = keys[SDL_SCANCODE_SPACE];


        player.update(dt, &map);

        Vec2 toplayer = player.position - firstmob.position;
        firstmob.update(dt, toplayer, &map);

        if (time-graphiclastframe > 1000.0/gamescreen.FPS) {
            gamescreen.cam.step(player.position);

            gamescreen.fill_black();
            gamescreen.draw_background();
            
            gamescreen.draw_player(player.position, player.hitbox.w, player.hitbox.h);
            gamescreen.draw_awaymob(firstmob.position, firstmob.hitbox.w, firstmob.hitbox.h);

            gamescreen.draw_terrain(&map);

            gamescreen.update();
            graphiclastframe = time;
        }

        SDL_Delay(8);
        dt = (float)(SDL_GetTicks()-time)/1000;
    }

    return 0;
}
