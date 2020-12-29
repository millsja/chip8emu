#ifndef SDLR_H
#define SDLR_H

#include <SDL2/SDL.h>

struct sdlr_resources
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* window_surface;
};

struct sdlr_screen
{
    const char* title;
    const int logical_width;
    const int logical_height;
    const int actual_width;
    const int actual_height;
};

// name: sdl_init
// description: takes struct sdlr_screen* containing information
//              about new screen configuration. initializes sdl,
//              window, renderer, etc., and returns these resources
//              in a struct sdlr_resources*
struct sdlr_resources* sdlr_init(struct sdlr_screen* screen_info);

// name: sdl_clean_up
// description: takes struct sdlr_resources and destroys them
//              frees object and quits sdl
void sdlr_clean_up(struct sdlr_resources* resources);

#endif
