#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../core/resources.h"
#include "../core/operations.h"
#include "../core/asmio.h"

int test_immediate_add()
{
    struct ch8_resources resources;
    resources.memory = malloc(CH8_INSTALLED_MEMORY);

    uint16_t expected = 20;

    resources.registers[R_PC] = 0x200;
    resources.registers[R_V0] = 5;

    resources.memory[resources.registers[R_PC]] =
        ((OP_ADD_I & 0xf) << 12) | // opcode
        ((R_V0 & 0xf) << 8) |     // dest
        (15 & 0xff);              // immediate

    ch8_add_imm(&resources, resources.registers[R_PC]);
    uint16_t found = resources.registers[R_V0];
    free(resources.memory);

    printf("Add test: expected = %d, ", expected);
    printf("found = %d\n\n", found);

    return expected == found;
}

int test_jump()
{
    struct ch8_resources resources;
    resources.memory = malloc(CH8_INSTALLED_MEMORY);

    uint16_t expected = 0xa35;

    resources.registers[R_PC] = 0x200;

    resources.memory[resources.registers[R_PC]] = 
            ((OP_JMP_I & 0xf) << 12) | // opcode
             (expected & 0xfff);          // immediate

    ch8_jump(&resources, resources.registers[R_PC]);
    uint16_t found = resources.registers[R_PC];
    free(resources.memory);

    printf("Add test: expected = %d, ", expected);
    printf("found = %d\n\n", found);

    return expected == found;
}

int main(void)
{
    test_immediate_add();
    test_jump();
}
