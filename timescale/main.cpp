#include <iostream>
using namespace std;

#include <libmath/vec2.hpp>
#include <game/game.hpp>
#include <graphics/graphics.hpp>
#include <physics/physics.hpp>


int main(int argc, char* argv[])
{    
    bool quit = false;
    SDL_Event event;

    Graphism gamescreen;

    TileMap map;

    Player player(1.f, 1.f, Vec2(16, 16));

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
        time = SDL_GetTicks64();

        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEWHEEL:
                cout << event.wheel.y << endl;
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

            // Debug render
            int block_center[2] = {
                (int)player.position.x,
                (int)player.position.y
                };
            BoundBox BBplayer = BoundBox(4);
            BBplayer.points[0] = Vec2(player.position.x-player.hitbox.w/2, player.position.y-player.hitbox.h/2);
            BBplayer.points[1] = Vec2(player.position.x-player.hitbox.w/2, player.position.y+player.hitbox.h/2);
            BBplayer.points[2] = Vec2(player.position.x+player.hitbox.w/2, player.position.y+player.hitbox.h/2);
            BBplayer.points[3] = Vec2(player.position.x+player.hitbox.w/2, player.position.y-player.hitbox.h/2);
            for (int x = -1; x < 2; x++) {
                for (int y = -1; y < 2; y++) {
                    int bx = block_center[0] + x, by = block_center[1] + y;
                    if (bx < 0 || 63 < bx || by < 0 || 63 < by) continue;
                    if (map.tiles[bx][by].id == 0) continue; 

                    BoundBox BBblock = BoundBox(4);
                    BBplayer.points[0] = Vec2(bx  , by  );
                    BBplayer.points[1] = Vec2(bx  , by+1);
                    BBplayer.points[2] = Vec2(bx+1, by+1);
                    BBplayer.points[3] = Vec2(bx+1, by  );
                    if (detectionGJK(BBplayer, BBblock)) continue;
                    
                    gamescreen.draw_debugblock_border(bx, by, {255, 0, 255, 255});
                }
            }

            gamescreen.update();
            graphiclastframe = time;
        }

        Uint8 run_time = SDL_GetTicks64()-time;
        SDL_Delay(max(8-run_time, 0));
        dt = (float)(SDL_GetTicks64()-time)/1000;
    }

    return 0;
}
