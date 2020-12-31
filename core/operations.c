#include <stdint.h>
#include <stdio.h>
#include "../core/asmio.h"
#include "../core/resources.h"

void ch8_add_imm(struct ch8_resources* resources, uint16_t address)
{
	uint16_t dest = ch8_read_with_offset(resources->memory, address, 8) & 0x7;
	uint16_t immediate = ch8_read_with_offset(resources->memory, address, 0);
	immediate = immediate & 0xff;
	resources->registers[dest] = resources->registers[dest] + immediate;
}

// void perform_zero(uint16_t registers[], uint16_t memory[], uint16_t address)
// {
// 	uint16_t second_word = read_with_offset(memory, address, 8) & 0xf;
// 
//         if (second_word >= 1)
//         {
//             return;
//         }
//         
// 	uint16_t second_byte = read_with_offset(memory, address, 0) & 0xff;
//         if (second_byte == 0xEE)
//         {
//             return;
//         }
// 
//         return;
// }
