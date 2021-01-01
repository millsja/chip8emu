#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include "../sdl/sdlr.h"
#include "resources.h"

void ch8_execute(
        struct sdlr_screen* screen_info,
        void (*set_up)(struct ch8_resources*, struct sdlr_resources*, int, char**),
        int (*execute)(struct ch8_resources*, struct sdlr_resources*),
        int argc,
        char* argv[])
{
    struct ch8_resources resources;
    resources.memory = malloc(CH8_INSTALLED_MEMORY);
    resources.stack.top = -1;
    resources.registers[R_PC] = 0x200;
    struct sdlr_resources* sdl_resources = sdlr_init(screen_info);
    sdlr_clear_screen(sdl_resources);

    if (set_up != NULL)
    {
        (*set_up)(&resources, sdl_resources, argc, argv);
    }

    if (sdl_resources != NULL)
    {
        SDL_Event e;
        int quit = 0;
        int user_quit = 0;
        while (!(quit || user_quit))
        {
            while(SDL_PollEvent(&e))
            {
                printf("Event popped from buffer...");
                if(e.type == SDL_QUIT)
                {
                        user_quit = 1;
                }
            }

            if (execute != NULL && !user_quit)
            {
                (*execute)(&resources, sdl_resources);
            }
        }

        sdlr_clean_up(sdl_resources);
    }

    free(resources.memory);
}
