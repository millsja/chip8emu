#include <stdint.h>
#include "stack.h"

void stk_push(struct stk_stack* stack, uint16_t value)
{
    stack->stack[++(stack->top)] = value;
}

uint16_t stk_pop(struct stk_stack* stack)
{
    return stack->stack[(stack->top)--];
}
