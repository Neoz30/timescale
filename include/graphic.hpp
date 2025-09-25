#pragma once

#include <SDL3/SDL.h>
#include "vec2.hpp"
#include "object.hpp"
#include "physic.hpp"

using namespace std;

void showSDLError();

struct Camera
{
    Vec2F position;
    Object *followed;

    Camera();

    void set_tracking_on(Object *object);

    void step();
};

struct GraphicView
{
    int width, height;
    float scale, unit_size;
    float t;
    Camera camera;

    const SDL_DisplayMode *DM;
    SDL_Window *window;
    SDL_Renderer *renderer;

    GraphicView(float scale);
    ~GraphicView();

    Vec2F screen_convertion(Vec2F position);
    Vec2F rect_correction(Vec2F position, float height);

    void set_interpolation_value(float t);

    void draw_physic_objects(PhysicWorld *physic);

    void render();
};