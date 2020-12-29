#include "sdlr.h"
#include <SDL2/SDL.h>

struct sdlr_resources* sdlr_init(struct sdlr_screen* screen_info)
{
    struct sdlr_resources* resources = malloc(sizeof(struct sdlr_resources));

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
            fprintf(stderr, "SDL init failed: %s\n", SDL_GetError());
            return NULL;
    }

    resources->window = NULL;
    resources->window = SDL_CreateWindow(
                    screen_info->title,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    screen_info->actual_width,
                    screen_info->actual_height,
                    SDL_WINDOW_SHOWN);

    if(resources->window == NULL)
    {
            fprintf(stderr, "SDL window init failed: %s\n", SDL_GetError());
            SDL_Quit();
            free(resources);
            return NULL;
    }

    resources->renderer = NULL;
    resources->renderer = SDL_CreateRenderer(resources->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(
            resources->renderer,
            screen_info->logical_width,
            screen_info->logical_height);

    if (resources->renderer == NULL)
    {
            fprintf(stderr, "Renderer could not be created. Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(resources->window);
            SDL_Quit();
            free(resources);
            return NULL;
    }

    resources->window_surface = NULL;
    resources->window_surface = SDL_GetWindowSurface(resources->window);

    SDL_FillRect(
                    resources->window_surface,
                    NULL,
                    SDL_MapRGB(resources->window_surface->format, 0x00, 0x00, 0x00));
    
    SDL_UpdateWindowSurface(resources->window);

    return resources;
}

void sdlr_clean_up(struct sdlr_resources* resources)
{
    SDL_FreeSurface(resources->window_surface);
    SDL_DestroyRenderer(resources->renderer);
    SDL_DestroyWindow(resources->window);
    free(resources);
    SDL_Quit();
}
