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
    resources.stack.top = -1;
    resources.memory = malloc(CH8_INSTALLED_MEMORY);

    uint16_t expected_0 = 0xa35;

    resources.registers[R_PC] = 0x200;

    resources.memory[resources.registers[R_PC]] = 
            ((OP_JMP_I & 0xf) << 12) | // opcode
             (expected_0 & 0xfff);          // immediate

    ch8_jump(&resources, resources.registers[R_PC]);
    uint16_t found_0 = resources.registers[R_PC];
    free(resources.memory);

    printf("Jump test: expected = %d, ", --expected_0);
    printf("found = %d\n\n", found_0);

    return expected_0 == found_0;
}

int test_run_sub()
{
    struct ch8_resources resources;
    resources.stack.top = -1;
    resources.memory = malloc(CH8_INSTALLED_MEMORY);

    uint16_t expected_0 = 0xa35;

    resources.registers[R_PC] = 0x200;
    uint16_t expected_1 = resources.registers[R_PC];

    resources.memory[resources.registers[R_PC]] = 
            ((OP_RUN & 0xf) << 12) | // opcode
             (expected_0 & 0xfff);          // immediate

    ch8_run_sub(&resources, resources.registers[R_PC]);
    uint16_t found_0 = resources.registers[R_PC];
    uint16_t found_1 = stk_pop(&(resources.stack));
    free(resources.memory);

    printf("Run sub test: expected = %d, ", --expected_0);
    printf("found = %d\n", found_0);

    printf("and also: expected = %d, ", expected_1);
    printf("found = %d\n\n", found_1);

    return expected_0 == found_0 && expected_1 == found_1;
}

int main(void)
{
    test_immediate_add();
    test_jump();
    test_run_sub();
}
