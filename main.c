#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdl/sdlr.h"
#include "core/sprite.h"
#include "core/resources.h"
#include "core/operations.h"
#include "core/asmio.h"

int DEBUG_MODE = 0;

void set_up_main(
        struct ch8_resources* resources,
        struct sdlr_resources* sdl_resources,
        int argc,
        char* argv[])
{
    srand(time(0));
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            ch8_load_image(argv[i], resources->memory);
        }
    }
}

int execute_main(struct ch8_resources* resources, struct sdlr_resources* sdl_resources)
{
    uint16_t op = ch8_read_with_offset(
            resources->memory,
            resources->registers[R_PC],
            12) & 0xf;

    switch (op)
    {
            case INSTR_ADD_I:
                    ch8_move_imm(resources, resources->registers[R_PC], 1);
                    break;
            case INSTR_JMP_I:
                    ch8_jump(resources, resources->registers[R_PC]);
                    break;
            case INSTR_JMP_R:
                    ch8_jump_reg(resources, resources->registers[R_PC]);
                    break;
            case INSTR_RUN:
                    ch8_run_sub(resources, resources->registers[R_PC]);
                    break;
            case INSTR_ZER:
                    ch8_zero(
                            resources,
                            sdl_resources,
                            resources->registers[R_PC],
                            sdlr_clear_screen);
                    break;
            case INSTR_BEQ_I:
                    ch8_branch_imm(resources, resources->registers[R_PC], 0);
                    break;
            case INSTR_BNE_I:
                    ch8_branch_imm(resources, resources->registers[R_PC], 1);
                    break;
            case INSTR_BEQ_R:
                    ch8_branch_reg(resources, resources->registers[R_PC], 0);
                    break;
            case INSTR_MOV_I:
                    ch8_move_imm(resources, resources->registers[R_PC], 0);
                    break;
            case INSTR_BNE_R:
                    ch8_branch_reg(resources, resources->registers[R_PC], 1);
                    break;
            case INSTR_OPR:
                    ch8_operate(resources, resources->registers[R_PC]);
                    break;
            case INSTR_RND:
                    ch8_move_rnd(resources, resources->registers[R_PC]);
                    break;
            case INSTR_DRW:
                    ch8_draw_sprite(
                            resources,
                            sdl_resources,
                            resources->registers[R_PC],
                            ch8_load_sprite_row,
                            sdlr_update_screen);
                    break;
            default:
                    if (DEBUG_MODE)
                    {
                        fprintf(stderr, "Unsupported opcode %x: ", op);
                        op = ch8_read_with_offset(
                                resources->memory,
                                resources->registers[R_PC],
                                0);
                        fprintf(stderr, "%x\n", op);
                    }
                    break;
    }
    
    if (DEBUG_MODE)
    {
        fprintf(stderr, "Instr %x: ", op);
        op = ch8_read_with_offset(
                resources->memory,
                resources->registers[R_PC],
                0);
        fprintf(stderr, "%x\n", op);
    }

    resources->registers[R_PC] += 2;
    return 0;
}

int main( int argc, char* argv[] )
{
    if (argc < 2)
    {
            fprintf(stderr, "Expected image file arguments...\n");
            return 1;
    }

    if (argc > 2)
    {
        if (strcmp(argv[1], "-d") || strcmp(argv[2], "-d"))
        {
            DEBUG_MODE = 1;
            fprintf(stderr, "Starting in DEBUG MODE...\n");
        }
    }

    struct sdlr_screen screen_info = { "chip8emu", 64, 32, 640, 320 };

    ch8_execute(&screen_info, set_up_main, execute_main, argc, argv);
}
