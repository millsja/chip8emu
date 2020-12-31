#include <stdio.h>
#include <stdint.h>
#include "../core/ch8resources.h"
#include "../operations/operations.h"
#include "../asmio/asmio.h"

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

    perform_add_imm(resources.registers, resources.memory, resources.registers[R_PC]);
    uint16_t found = resources.registers[R_V0];
    free(resources.memory);

    printf("Expected = %d, ", expected);
    printf("found = %d\n\n", found);

    return expected == found;
}

int main(int argc, char* argv[])
{
    test_immediate_add();
}
