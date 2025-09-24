#pragma once

#include <SDL3/SDL.h>
#include "vec2.hpp"
#include "collider.hpp"
#include "physic.hpp"

using namespace std;

void initSDL();

void quitSDL();

void showSDLError();

struct GraphicView
{
    int width, height;
    float scale, unit_size;

    const SDL_DisplayMode *DM;
    SDL_Window *window;
    SDL_Renderer *renderer;

    GraphicView(float scale);
    ~GraphicView();

    Vec2F screen_convertion(Vec2F position);
    Vec2F rect_correction(Vec2F position, float height);

    void draw_physic_colliders(PhysicWorld *physic);

    void render();
};