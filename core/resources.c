#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include "../sdl/sdlr.h"
#include "resources.h"

uint8_t ch8_get_key_as_hex(struct ch8_resources* resources)
{
    uint16_t key = resources->keyboard_buffer;
    if (key >= 0x30 && key <= 0x39)
    {
        return (key & 0xf);
    }

    switch (key)
    {
        case 0x61:
            return 0xa;
        case 0x62:
            return 0xb;
        case 0x63:
            return 0xc;
        case 0x64:
            return 0xd;
        case 0x65:
            return 0xe;
        case 0x66:
            return 0xf;
    }

    return 1 << 7;
}

void ch8_clear_keys(struct ch8_resources* resources)
{
    resources->keyboard_flag = 0;
}

void ch8_set_key(struct ch8_resources* resources, uint32_t key)
{
    resources->keyboard_buffer = key;
    resources->keyboard_flag = 1;
}

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
            ch8_clear_keys(&resources);
            while(SDL_PollEvent(&e))
            {
                printf("Event popped from buffer...");
                if(e.type == SDL_QUIT)
                {
                    user_quit = 1;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    ch8_set_key(&resources, e.key.keysym.sym);
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
