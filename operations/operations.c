#include <stdint.h>
#include <stdio.h>
#include "../asmio/asmio.h"

void perform_add_imm(uint16_t registers[], uint16_t memory[], uint16_t address)
{
	uint16_t dest = read_with_offset(memory, address, 8) & 0x7;
	uint16_t immediate = read_from_memory(memory, address);
	immediate = immediate & 0xff;
	registers[dest] = registers[dest] + immediate;
}
