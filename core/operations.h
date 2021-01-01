#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "../sdl/sdlr.h"

typedef enum operandsenum_t
{
	OP_ZER = 0,
	OP_JMP_I,
	OP_RUN,
	OP_BEQ_I,
	OP_BNE_I,
	OP_BEQ_R,
	OP_STR_I,
	OP_ADD_I,
	OP_REG,
	OP_BNE_R,
	OP_STR_PC,
	OP_JMP_R,
	OP_RND,
	OP_DRW,
	OP_BKY,
	OP_OTH,
} operandsenm_t;

void ch8_add_imm(struct ch8_resources* resources, uint16_t address);

void ch8_jump(struct ch8_resources* resources, uint16_t address);

void ch8_run_sub(struct ch8_resources* resources, uint16_t address);

void ch8_zero(
        struct ch8_resources* resources,
        struct sdlr_resources* sdl_resources,
        uint16_t address,
        void (*clear_screen)(struct sdlr_resources*));

#endif
