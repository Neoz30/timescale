#include "graphic.hpp"

void initSDL()
{
    SDL_Init(SDL_INIT_VIDEO);
}

void quitSDL()
{
    SDL_Quit();
}

void showSDLError()
{
    SDL_Log(SDL_GetError());
}

GraphicView::GraphicView(float s)
{
    SDL_Init(SDL_INIT_VIDEO);
    DM = SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay());
    if (DM == NULL) showSDLError();

    window = SDL_CreateWindow("Timescale", DM->w, DM->h, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) showSDLError();

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) showSDLError();

    width = DM->w, height = DM->h;

    scale = s;
    unit_size = min(width, height) * scale;
}

GraphicView::~GraphicView()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Vec2F GraphicView::screen_convertion(Vec2F position)
{
    position *= unit_size;
    position.y = position.y * -1 + height;
    return position;
}

Vec2F GraphicView::rect_correction(Vec2F position, float h)
{
    return position - Vec2F(0, unit_size * h);
}

void GraphicView::draw_physic_colliders(PhysicWorld *physic)
{
    SDL_FRect rect;
    SDL_SetRenderDrawColor(renderer, 39, 183, 245, 255);
    for (Collider *collider: physic->colliders)
    {
        Vec2F position = rect_correction(screen_convertion(collider->position), collider->size.y);
        rect.x = position.x,                   rect.y = position.y;
        rect.w = collider->size.x * unit_size, rect.h = collider->size.y * unit_size;
        SDL_RenderFillRect(renderer, &rect);
    }
}

void GraphicView::render()
{
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
