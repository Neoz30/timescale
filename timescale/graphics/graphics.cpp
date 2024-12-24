#include <math.h>
#include "graphics.hpp"


//Camera class function
Camera::Camera() {mode = 0;}
void Camera::set_view(SDL_DisplayMode* displaymode, int pxpertile) {
    view.x = (float)displaymode->w/pxpertile;
    view.y = (float)displaymode->h/pxpertile;
}
void Camera::step(Vec2 player_pos) {
    switch (mode) {
    case CAM_MODE_STATIC:
        break;
    case CAM_MODE_DYNAMIC:
        float playercam = player_pos.x-(position.x+view.x/2);
        if (playercam > 0) {
            position.x += max(
                (10.f*(4*playercam-view.x)) / (view.x*(0.5f*view.x-playercam)), 0.f
                );
        } else {
            position.x -= max(
                (10.f*(-4*playercam-view.x)) / (view.x*(0.5f*view.x+playercam)), 0.f
                );
        }
        break;
    }
}

//Graphism class function
Graphism::Graphism() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_GetCurrentDisplayMode(0, &DM);
    FPS = DM.refresh_rate;
    window = SDL_CreateWindow(
        "SDL2 TimeScale Beta",
        0, 0, DM.w, DM.h,
        SDL_WINDOW_FULLSCREEN
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    LoadTextures();
    pxpertile = 40;
    cam.set_view(&DM, pxpertile);
    cam.mode = CAM_MODE_DYNAMIC;
}
Graphism::~Graphism() {    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyTexture(block);
    SDL_DestroyTexture(background);

    IMG_Quit();
    SDL_Quit();
}
void Graphism::screen_to_tile(int x, int y, int result[2]) {
    result[0] = x / pxpertile;
    result[1] = (DM.h - y) / pxpertile;
}
void Graphism::tile_to_screen(float x, float y, int result[2]) {
    result[0] = (int)(x * pxpertile);
    result[1] = (int)(-y * pxpertile + DM.h);
}
void Graphism::fill_black() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
void Graphism::update() {
    SDL_RenderPresent(renderer);
}
void Graphism::draw_background() {
    SDL_RenderCopy(renderer, background, NULL, NULL);
}

int remove_useless(int bitmap) {
    if (bitmap & 16 && !(bitmap & 1 && bitmap & 2)) bitmap -= 16;
    if (bitmap & 32 && !(bitmap & 2 && bitmap & 4)) bitmap -= 32;
    if (bitmap & 64 && !(bitmap & 4 && bitmap & 8)) bitmap -= 64;
    if (bitmap & 128 && !(bitmap & 8 && bitmap & 1)) bitmap -= 128;
    return bitmap;
}
void Graphism::draw_terrain(unsigned int tiles[64][64]) {
    SDL_Rect texturepos = {0, 0, 8, 8};
    SDL_Rect tile;
    tile.w = pxpertile;
    tile.h = pxpertile;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {

            if (tiles[i][j]) {
                int tile_pos[2];
                tile_to_screen((float)i-cam.position.x, (float)j, tile_pos);
                tile.x = tile_pos[0];
                tile.y = tile_pos[1] - pxpertile;

                char code = 255;
                if (j+1 < 64 && tiles[i][j+1] == 0) code &= 254;
                if (i+1 < 64 && tiles[i+1][j] == 0) code &= 253;
                if (j-1 >= 0 && tiles[i][j-1] == 0) code &= 251;
                if (i-1 >= 0 && tiles[i-1][j] == 0) code &= 247;
                if (i+1 < 64 && j+1 < 64 && tiles[i+1][j+1] == 0) code &= 239;
                if (i+1 < 64 && j-1 >= 0 && tiles[i+1][j-1] == 0) code &= 223;
                if (i-1 >= 0 && j-1 >= 0 && tiles[i-1][j-1] == 0) code &= 191;
                if (i-1 >= 0 && j+1 < 64 && tiles[i-1][j+1] == 0) code &= 127;

                code = remove_useless(code);

                int x =  (code & 3) | ((code & 48) >> 2);
                int y =  ((code & 12) >> 2) | ((code & 192) >> 4);

                switch (x & 12) {
                    case 12: x -= 8; break;
                    case 8: x -= 5; break;
                    case 4: x -= 3; break;
                    default: break;
                }
                switch (y & 12) {
                    case 12: y -= 8; break;
                    case 8: y -= 5; break;
                    case 4: y -= 3; break;
                    default: break;
                }

                if (x == 7 || y == 7) {
                    if ((y == 4 || y == 7) && (x == 4 || x == 7)) {
                        x -= 2;
                        y -= 2;
                    } else {
                        x -= 1;
                        y -= 1;
                    }
                }

                texturepos.x = 8*x;
                texturepos.y = 8*y;

                SDL_RenderCopy(renderer, block, &texturepos, &tile);
            }
        }
    }
}

void Graphism::draw_player(Vec2 player_pos, float pwidth, float pheight) {
    int toscreen[2];
    tile_to_screen(player_pos.x-cam.position.x, player_pos.y, toscreen);

    SDL_Rect rect;
    rect.w = (int)(pwidth*pxpertile);
    rect.h = (int)(pheight*pxpertile);
    rect.x = toscreen[0]-rect.w/2;
    rect.y = toscreen[1]-rect.h/2;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
void Graphism::LoadTextures() {
    SDL_Surface* blockSurface = IMG_Load("./textures/custom/diorite.png");
    if (!blockSurface) cout << "Block textures not finded !" << endl;
    SDL_Surface* backgroundSurface = IMG_Load("./textures/mountain_background.png");
    if (!backgroundSurface) cout << "Background texture not finded !" << endl;

    block = SDL_CreateTextureFromSurface(renderer, blockSurface);
    background = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(blockSurface);
    SDL_FreeSurface(backgroundSurface);
}