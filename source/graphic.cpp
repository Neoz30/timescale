#include "graphic.hpp"

void showSDLError()
{
    SDL_Log(SDL_GetError());
}

Camera::Camera()
{
    followed = NULL;
}

void Camera::set_tracking_on(Object *object)
{
    followed = object;
}

void Camera::step()
{
    if (followed == NULL) return;
    position.x += (followed->position.x - position.x) * 0.01;
}

GraphicView::GraphicView(float s)
{
    SDL_Init(SDL_INIT_VIDEO);
    DM = SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay());
    if (DM == NULL) showSDLError();

    window = SDL_CreateWindow("Timescale", DM->w, DM->h, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) showSDLError();
    SDL_SetWindowSurfaceVSync(window, SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE);

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) showSDLError();
    SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);

    width = DM->w, height = DM->h;

    scale = s;
    unit_size = min(width, height) * scale;
    t = 0;
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
    position.x += DM->w / 2;
    position.y = position.y * -1 + height;
    return position;
}

Vec2F GraphicView::rect_correction(Vec2F position, float h)
{
    return position - Vec2F(0, unit_size * h);
}

void GraphicView::set_interpolation_value(float interpolation)
{
    t = interpolation;
}

void GraphicView::draw_physic_objects(PhysicWorld *physic)
{
    SDL_FRect rect;
    for (Object *object: physic->objects)
    {
        Vec2F position = rect_correction(screen_convertion(object->position + object->velocity * t - camera.position), object->size.y);
        rect.x = position.x,                   rect.y = position.y;
        rect.w = object->size.x * unit_size, rect.h = object->size.y * unit_size;
        
        switch (object->type)
        {
            case PLAYER:
                SDL_SetRenderDrawColor(renderer, 217, 68, 70, 255);
                break;
            case TERRAIN:
                SDL_SetRenderDrawColor(renderer, 17, 124, 19, 255);
                break;
            case BOX:
                SDL_SetRenderDrawColor(renderer, 99, 73, 43, 255);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 39, 183, 245, 255);
                break;
        }

        SDL_RenderFillRect(renderer, &rect);
    }
}

void GraphicView::render()
{
    camera.step();

    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
