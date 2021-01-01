#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>

#include "sdl/sdlr.h"
#include "core/resources.h"
#include "core/operations.h"
#include "core/asmio.h"
#include "core/sprite.h"

void mess_with_pixels(uint32_t* pixels)
{
    uint8_t sprite[] = {0x3c, 0x62, 0xc0, 0xc0, 0xde, 0xd2, 0xc2, 0x66, 0x3c, 0x00, 0x00};
    ch8_draw_sprite(pixels, 0, 0, sprite, 11);
}

int main( int argc, char* argv[] )
{
    if (argc < 2)
    {
            fprintf(stderr, "Expected image file arguments...\n");
            return 1;
    }

    struct ch8_resources resources;
    resources.memory = malloc(CH8_INSTALLED_MEMORY);
    resources.stack.top = -1;

    // load image(s) into memory
    for (int i = 1; i < argc; i++)
    {
            ch8_load_image(argv[i], resources.memory);
    }

    resources.registers[R_PC] = 0x200;

    struct sdlr_screen screen_info = { "chip8emu", 64, 32, 640, 320 };
    struct sdlr_resources* sdl_resources = sdlr_init(&screen_info);

    sdlr_clear_screen(sdl_resources);

    // mess_with_pixels(sdl_resources->texture_pixels);
    // sdlr_update_screen(sdl_resources);
    // resources.memory[resources.registers[R_PC]] =
    //         ((OP_ZER & 0xf) << 12) | // opcode
    //          (0x0e0 & 0xfff);          // immediate
    // ch8_zero(
    //         &resources,
    //         sdl_resources,
    //         resources.registers[R_PC],
    //         sdlr_clear_screen);

    if (sdl_resources != NULL)
    {
        SDL_Event e;
        int quit = 0;
        while (!quit)
        {
            while(SDL_PollEvent(&e))
            {
                printf("Event popped from buffer...");
                if(e.type == SDL_QUIT)
                {
                        quit = 1;
                }
            }

            uint16_t op = ch8_read_with_offset(resources.memory, resources.registers[R_PC], 12);

            switch (op)
            {
                    case OP_ADD_I:
                            ch8_add_imm(&resources, resources.registers[R_PC]);
                            break;
                    case OP_JMP_I:
                            ch8_jump(&resources, resources.registers[R_PC]);
                            break;
                    case OP_RUN:
                            ch8_run_sub(&resources, resources.registers[R_PC]);
                            break;
                    case OP_ZER:
                            ch8_zero(
                                    &resources,
                                    sdl_resources,
                                    resources.registers[R_PC],
                                    sdlr_clear_screen);
                            break;
                    default:
                            break;
            }
            
            resources.registers[R_PC]++;
        }

        sdlr_clean_up(sdl_resources);
    }

    free(resources.memory);
    return 0;
}
