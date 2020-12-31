#ifndef STACK_H
#define STACK_H

#include <stdint.h>

struct stk_stack
{
    uint16_t stack[12];
    int top;
};

// struct stk_stack* stk_init();

void stk_push(struct stk_stack* stack, uint16_t value);

uint16_t stk_pop(struct stk_stack* stack);

#endif
