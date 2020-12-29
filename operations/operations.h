#ifndef OPERATIONS_H
#define OPERATIONS_H

typedef enum operandsenum_t
{
	OP_ZER = 0,
	OP_JMP_I,
	OP_EXE,
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

void perform_add_imm(uint16_t registers[], uint16_t memory[], uint16_t address);

#endif
