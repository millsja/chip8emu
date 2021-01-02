#include <stdint.h>
#include <stdio.h>
#include "../core/asmio.h"
#include "../core/resources.h"
#include "../utilities/stack.h"
#include "../sdl/sdlr.h"

void ch8_jump(struct ch8_resources* resources, uint16_t address)
{
    uint16_t dest = ch8_read_with_offset(resources->memory, address, 0) & 0xfff;
    resources->registers[R_PC] = --dest;
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
	uint16_t second_word = ch8_read_with_offset(resources->memory, address, 8) & 0xf;

        if (second_word >= 1)
        {
            // NOT YET IMPLEMENTED
            return;
        }
        
	uint16_t second_byte = ch8_read_with_offset(resources->memory, address, 0) & 0xff;
        if (second_byte == 0xEE)
        {
            uint16_t popped_address = stk_pop(&(resources->stack));
            resources->registers[R_PC] = --popped_address;
            return;
        }

        (*clear_screen)(sdl_resources);
        return;
}

static void branch(struct ch8_resources* resources, uint16_t a, uint16_t b, int branch_if_neq)
{
    if ((a == b) && !branch_if_neq)
    {
        resources->registers[R_PC]++;
    }
    else if ((a != b) && branch_if_neq)
    {
        resources->registers[R_PC]++;
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
