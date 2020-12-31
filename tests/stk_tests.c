#include "../utilities/stack.h"
#include <stdio.h>
#include <stdint.h>

int push_pop_test()
{
    uint16_t expected = 0x0a35;
    struct stk_stack stack = stk_empty;
    stk_push(&stack, expected);
    uint16_t found = stk_pop(&stack);


    printf("Push/pop test: expected = %d, ", expected);
    printf("found = %d\n\n", found);

    return expected == found;
}

int main(void)
{
    push_pop_test();
}
