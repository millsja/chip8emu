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


    sdlr_clear_screen(resources);

    resources->window_texture = SDL_CreateTexture(
            resources->renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STATIC,
            screen_info->logical_width,
            screen_info->logical_height);

    resources->texture_pixels = malloc(screen_info->logical_width * screen_info->logical_height * sizeof(uint32_t));
    memset(resources->texture_pixels, 0, screen_info->logical_width * screen_info->logical_height * sizeof(uint32_t));
    resources->texture_pixels_width = screen_info->logical_width * screen_info->logical_height * sizeof(uint32_t);

    return resources;
}

void sdlr_clean_up(struct sdlr_resources* resources)
{
    SDL_DestroyTexture(resources->window_texture);
    free(resources->texture_pixels);
    SDL_DestroyRenderer(resources->renderer);
    SDL_DestroyWindow(resources->window);
    free(resources);
    SDL_Quit();
}

void sdlr_update_screen(struct sdlr_resources* resources)
{
    SDL_UpdateTexture(resources->window_texture,
            NULL,
            resources->texture_pixels,
            64 * sizeof(uint32_t));
    SDL_RenderClear(resources->renderer);
    SDL_RenderCopy(resources->renderer, resources->window_texture, NULL, NULL);
    SDL_RenderPresent(resources->renderer);
}

void sdlr_clear_screen(struct sdlr_resources* resources)
{
    SDL_Surface* window_surface = SDL_GetWindowSurface(resources->window);

    SDL_FillRect(
            window_surface,
            NULL,
            SDL_MapRGB(window_surface->format, 0x00, 0x00, 0x00));
    
    SDL_UpdateWindowSurface(resources->window);

    SDL_FreeSurface(window_surface);

    memset(resources->texture_pixels, 0, resources->texture_pixels_width);
}
