#include <stdint.h>
#include <stdio.h>
#include "../core/asmio.h"
#include "../core/resources.h"
#include "../utilities/stack.h"
#include "../sdl/sdlr.h"
#include "operations.h"

void ch8_jump(struct ch8_resources* resources, uint16_t address)
{
    uint16_t dest = ch8_read_with_offset(resources->memory, address, 0) & 0xfff;
    resources->registers[R_PC] = dest - 2;
}

void ch8_jump_reg(struct ch8_resources* resources, uint16_t address)
{
    uint16_t jmp_offset = ch8_read_with_offset(resources->memory, address, 0) & 0xfff;
    uint16_t dest = resources->registers[R_V0] + jmp_offset;
    resources->registers[R_PC] = dest - 2;
}

void ch8_run_sub(struct ch8_resources* resources, uint16_t address)
{
    stk_push(&(resources->stack), address);
    ch8_jump(resources, address);
}

void ch8_zero(
        struct ch8_resources* resources,
        struct sdlr_resources* sdl_resources,
        uint16_t address,
        void (*clear_screen)(struct sdlr_resources*))
{
	uint16_t second_nibble = ch8_read_with_offset(resources->memory, address, 8) & 0xf;

        if (second_nibble >= 1)
        {
            // NOT YET IMPLEMENTED
            return;
        }
        
	uint16_t second_byte = ch8_read_with_offset(resources->memory, address, 0) & 0xff;
        if (second_byte == 0xEE)
        {
            uint16_t popped_address = stk_pop(&(resources->stack));
            resources->registers[R_PC] = popped_address - 2;
            return;
        }

        (*clear_screen)(sdl_resources);
        return;
}

static void branch(struct ch8_resources* resources, uint16_t a, uint16_t b, int branch_if_neq)
{
    if ((a == b) && !branch_if_neq)
    {
        resources->registers[R_PC] += 2;
    }
    else if ((a != b) && branch_if_neq)
    {
        resources->registers[R_PC] += 2;
    }
}

void ch8_branch_imm(struct ch8_resources* resources, uint16_t address, int branch_if_neq)
{
    uint16_t reg = ch8_read_with_offset(resources->memory, address, 8) & 0xf;
    uint16_t imm = ch8_read_with_offset(resources->memory, address, 0) & 0xff;
    branch(resources, resources->registers[reg], imm, branch_if_neq);
}

void ch8_branch_reg(struct ch8_resources* resources, uint16_t address, int branch_if_neq)
{
    uint16_t reg_0 = ch8_read_with_offset(resources->memory, address, 8) & 0xf;
    uint16_t reg_1 = ch8_read_with_offset(resources->memory, address, 4) & 0xf;
    branch(
            resources,
            resources->registers[reg_0],
            resources->registers[reg_1],
            branch_if_neq);
}

void ch8_move_imm(struct ch8_resources* resources, uint16_t address, int add_and_store)
{
    uint16_t reg = ch8_read_with_offset(resources->memory, address, 8) & 0xf;
    uint16_t imm = ch8_read_with_offset(resources->memory, address, 0) & 0xff;
    uint16_t add_value = add_and_store ? resources->registers[reg] : 0;
    resources->registers[reg] = imm + add_value;
}

void ch8_move_rnd(struct ch8_resources* resources, uint16_t address)
{
    uint16_t ran = rand() % 0xff;
    uint16_t reg = ch8_read_with_offset(resources->memory, address, 8) & 0xf;
    uint16_t imm = ch8_read_with_offset(resources->memory, address, 0) & 0xff;
    resources->registers[reg] = ran & imm;
}

void ch8_operate(struct ch8_resources* resources, uint16_t address)
{
    uint16_t dst = ch8_read_with_offset(resources->memory, address, 8) & 0xf;
    uint16_t src = ch8_read_with_offset(resources->memory, address, 4) & 0xf;
    uint16_t operation = ch8_read_with_offset(resources->memory, address, 0) & 0xf;
    uint16_t d_val = resources->registers[dst];
    uint16_t s_val = resources->registers[src];

    int output = 0;
    switch(operation)
    {
        case OP_NONE:
            resources->registers[dst] = s_val;
            break;
        case OP_OR:
            resources->registers[dst] = d_val | s_val;
            break;
        case OP_AND:
            resources->registers[dst] = d_val & s_val;
            break;
        case OP_XOR:
            resources->registers[dst] = d_val ^ s_val;
            break;
        case OP_ADD:
            output = d_val + s_val;
            resources->registers[dst] = output & 0xff;
            resources->registers[R_VF] = output > 0xff;
            break;
        case OP_SUB:
            output = d_val - s_val;
            resources->registers[dst] = output & 0xff;
            resources->registers[R_VF] = output < 0;
            break;
        case OP_SHIFT_R:
            resources->registers[R_VF] = resources->registers[dst] & 0x1;
            resources->registers[dst] = d_val >> 1;
            break;
        case OP_SUB_REV:
            output = s_val - d_val;
            resources->registers[dst] = output & 0xff;
            resources->registers[R_VF] = output < 0;
            break;
        case OP_SHIFT_L:
            resources->registers[R_VF] = (resources->registers[dst] >> 14) & 0x1;
            resources->registers[dst] = d_val << 1;
            break;
        default:
            fprintf(stderr, "Operate mode not implemented: %x\n", operation);
            break;
    }
}

void ch8_draw_sprite(
        struct ch8_resources* resources,
        struct sdlr_resources* sdl_resources,
        uint16_t address,
        int (*draw_sprite)(uint32_t*, int, int, uint8_t),
        void (*update_screen)(struct sdlr_resources*))
{
    uint16_t x_coord = ch8_read_with_offset(resources->memory, address, 8) & 0xf;
    uint16_t y_coord = ch8_read_with_offset(resources->memory, address, 4) & 0xf;
    uint16_t height = ch8_read_with_offset(resources->memory, address, 0) & 0xf;

    int pixel_flipped = 0;
    uint8_t sprite_row = 0;
    for (int i = 0; i < height + 1; i++)
    {
        sprite_row = ch8_read_byte(
                resources->memory,
                resources->i_pointer + i);
        pixel_flipped |= (*draw_sprite)(sdl_resources->texture_pixels, x_coord, y_coord + i, sprite_row);
    }

    resources->registers[R_VF] = pixel_flipped;
    (*update_screen)(sdl_resources);
}

