#include <stdio.h>
#include "sdl/sdlr.h"
#include "core/resources.h"
#include "core/operations.h"
#include "core/asmio.h"

void set_up_main(
        struct ch8_resources* resources,
        struct sdlr_resources* sdl_resources,
        int argc,
        char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        ch8_load_image(argv[i], resources->memory);
    }
}

int execute_main(struct ch8_resources* resources, struct sdlr_resources* sdl_resources)
{
    uint16_t op = ch8_read_with_offset(resources->memory, resources->registers[R_PC], 12);

    switch (op)
    {
            case OP_ADD_I:
                    ch8_add_imm(resources, resources->registers[R_PC]);
                    break;
            case OP_JMP_I:
                    ch8_jump(resources, resources->registers[R_PC]);
                    break;
            case OP_RUN:
                    ch8_run_sub(resources, resources->registers[R_PC]);
                    break;
            case OP_ZER:
                    ch8_zero(
                            resources,
                            sdl_resources,
                            resources->registers[R_PC],
                            sdlr_clear_screen);
                    break;
            case OP_BEQ_I:
                    ch8_branch_imm(resources, resources->registers[R_PC], 0);
                    break;
            case OP_BNE_I:
                    ch8_branch_imm(resources, resources->registers[R_PC], 1);
                    break;
            case OP_BEQ_R:
                    ch8_branch_reg(resources, resources->registers[R_PC], 0);
                    break;
            case OP_BNE_R:
                    ch8_branch_reg(resources, resources->registers[R_PC], 1);
                    break;
            default:
                    fprintf(stderr, "Unsupported opcode...\n");
                    break;
    }
    
    resources->registers[R_PC]++;
    return 0;
}

int main( int argc, char* argv[] )
{
    if (argc < 2)
    {
            fprintf(stderr, "Expected image file arguments...\n");
            return 1;
    }

    struct sdlr_screen screen_info = { "chip8emu", 64, 32, 640, 320 };

    ch8_execute(&screen_info, set_up_main, execute_main, argc, argv);
}
