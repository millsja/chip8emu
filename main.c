#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>

#include "sdl/sdlr.h"
#include "chip8emu/registers.h"
#include "operations/operations.h"
#include "asmio/asmio.h"


int main( int argc, char* argv[] )
{
    if (argc < 2)
    {
            fprintf(stderr, "Expected image file arguments...\n");
            return 1;
    }

    uint16_t registers[R_COUNT];

    // allocate space for available memory
    uint16_t memory[UINT16_MAX];

    // load image(s) into memory
    for (int i = 1; i < argc; i++)
    {
            load_image(argv[i], memory);
    }

    registers[R_PC] = 0x200;

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

            uint16_t op = read_with_offset(memory, registers[R_PC], 12);

            switch (op)
            {
                    case OP_REG:
                            perform_add_imm(registers, memory, registers[R_PC]);
                            return 0;
                            break;
                    default:
                            break;
            }
            
            registers[R_PC]++;
            SDL_SetRenderDrawColor(resources->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderDrawPoint(resources->renderer, 20, 20);
            SDL_RenderPresent(resources->renderer);
        }

        sdlr_clean_up(resources);
    }

    return 0;
}
