#include <SDL2/SDL.h>
#include <stdio.h>
#include "sdl/sdlr.h"

int main( int argc, char* args[] )
{
    struct sdlr_screen screen_info = { "chip8emu", 64, 32, 640, 320 };
    struct sdlr_resources* resources = sdlr_init(&screen_info);

    if (resources != NULL)
    {
        SDL_Event e;
        int quit = 0;
        while (!quit)
        {
                while(SDL_PollEvent(&e) != 0)
                {
                        if(e.type == SDL_QUIT)
                        {
                                quit = 1;
                        }
                }

                SDL_SetRenderDrawColor(resources->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderDrawPoint(resources->renderer, 20, 20);
                SDL_RenderPresent(resources->renderer);
        }

        sdlr_clean_up(resources);
    }

    return 0;
}
