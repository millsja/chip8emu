#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "../sdl/sdlr.h"

typedef enum opcode_t 
{
    INSTR_ZER = 0,
    INSTR_JMP_I,
    INSTR_RUN,
    INSTR_BEQ_I,
    INSTR_BNE_I,
    INSTR_BEQ_R,
    INSTR_MOV_I,
    INSTR_ADD_I,
    INSTR_OPR,
    INSTR_BNE_R,
    INSTR_STR_PC,
    INSTR_JMP_R,
    INSTR_RND,
    INSTR_DRW,
    INSTR_BKY,
    INSTR_OTH,
} opcode_t;

typedef enum operator_t
{
    OP_NONE = 0,
    OP_OR,
    OP_AND,
    OP_XOR,
    OP_ADD,
    OP_SUB,
    OP_SHIFT_R,
    OP_SUB_REV,
    OP_RESERVED_8,
    OP_RESERVED_9,
    OP_RESERVED_a,
    OP_RESERVED_b,
    OP_RESERVED_c,
    OP_RESERVED_d,
    OP_SHIFT_L,
    OP_RESERVED_f,
} operator_t;

void ch8_add_imm(struct ch8_resources* resources, uint16_t address);

void ch8_jump(struct ch8_resources* resources, uint16_t address);

void ch8_run_sub(struct ch8_resources* resources, uint16_t address);

void ch8_zero(
        struct ch8_resources* resources,
        struct sdlr_resources* sdl_resources,
        uint16_t address,
        void (*clear_screen)(struct sdlr_resources*));

void ch8_branch_imm(struct ch8_resources* resources, uint16_t address, int branch_if_neq);

void ch8_branch_reg(struct ch8_resources* resources, uint16_t address, int branch_if_neq);

void ch8_move_imm(struct ch8_resources* resources, uint16_t address, int add_and_store);

void ch8_move_rnd(struct ch8_resources* resources, uint16_t address);

void ch8_operate(struct ch8_resources* resources, uint16_t address);

#endif
