#include <stdint.h>
#include <stdio.h>
#include "../core/asmio.h"
#include "../core/resources.h"
#include "../utilities/stack.h"
#include "../sdl/sdlr.h"

void ch8_add_imm(struct ch8_resources* resources, uint16_t address)
{
    uint16_t dest = ch8_read_with_offset(resources->memory, address, 8) & 0x7;
    uint16_t immediate = ch8_read_with_offset(resources->memory, address, 0);
    immediate = immediate & 0xff;
    resources->registers[dest] = resources->registers[dest] + immediate;
}

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
