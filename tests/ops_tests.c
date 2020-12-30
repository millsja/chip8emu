#include <stdio.h>
#include <stdint.h>
#include "../chip8emu/registers.h"
#include "../operations/operations.h"
#include "../asmio/asmio.h"

int test_immediate_add()
{
	uint16_t registers[R_COUNT];
	uint16_t memory[UINT16_MAX];

	uint16_t expected = 20;

	registers[R_PC] = 0x200;
	registers[R_V0] = 5;

	memory[registers[R_PC]] = 
		((OP_ADD_I & 0xf) << 12) | // opcode
		 ((R_V0 & 0xf) << 8) |     // dest
		 (15 & 0xff);              // immediate

	perform_add_imm(registers, memory, registers[R_PC]);

	printf("Expected = %d, ", expected);
	printf("found = %d\n\n", registers[R_V0]);

	return expected == registers[R_V0];
}

int main(int argc, char* argv[])
{
	test_immediate_add();
}
