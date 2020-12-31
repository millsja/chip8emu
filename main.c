#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>

#include "sdl/sdlr.h"
#include "core/ch8resources.h"
#include "operations/operations.h"
#include "asmio/asmio.h"
#include "core/sprite.h"

void mess_with_pixels(uint32_t* pixels)
{
    uint8_t sprite[] = {0x3c, 0x62, 0xc0, 0xc0, 0xde, 0xd2, 0xc2, 0x66, 0x3c, 0x00, 0x00};
    ch8_draw_sprite(pixels, 0, 0, sprite, 11);
}

int main( int argc, char* argv[] )
{
    // if (argc < 2)
    // {
    //         fprintf(stderr, "Expected image file arguments...\n");
    //         return 1;
    // }

    struct ch8_resources resources;
    resources.memory = malloc(CH8_INSTALLED_MEMORY);

    // load image(s) into memory
    // for (int i = 1; i < argc; i++)
    // {
    //         load_image(argv[i], resources.memory);
    // }

    resources.registers[R_PC] = 0x200;

    struct sdlr_screen screen_info = { "chip8emu", 64, 32, 640, 320 };
    struct sdlr_resources* sdl_resources = sdlr_init(&screen_info);

    // mess_with_pixels(sdl_resources->texture_pixels);
    // sdlr_update_screen(sdl_resources);

    if (sdl_resources != NULL)
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

            // uint16_t op = read_with_offset(resources.memory, resources.registers[R_PC], 12);

            // switch (op)
            // {
            //         case OP_REG:
            //                 perform_add_imm(
            //                         &resources,
            //                         resources.registers[R_PC]);
            //                 return 0;
            //                 break;
            //         default:
            //                 break;
            // }
            
            // resources.registers[R_PC]++;
        }

        sdlr_clean_up(sdl_resources);
    }

    free(resources.memory);
    return 0;
}
