#ifndef _PT_JIT_H
#define _PT_JIT_H

#include "pt.h"

typedef enum {
    PT_BYTE  = 0,
    PT_WORD  = 1,
    PT_DWORD = 2,
    PT_QWORD = 4
} pt_jit_size_t;

typedef enum {
    PT_EAX = 0,
    PT_ECX = 1,
    PT_EDX = 2,
    PT_EBX = 3,
    PT_ESP = 4,
    PT_EBP = 5,
    PT_ESI = 6,
    PT_EDI = 7,
    PT_R8  = 8,
    PT_R9  = 9,
    PT_R10 = 10,
    PT_R11 = 11,
    PT_R12 = 12,
    PT_R13 = 13,
    PT_R14 = 14,
    PT_R15 = 15,
    _PT_REG_END = 0xff
} pt_jit_reg_t;

typedef enum {
    PT_MOV = 0,
    PT_ADD,
    PT_SUB,
    PT_MUL,
    PT_DIV,
    PT_PUSH,
    PT_POP,
    PT_TEST,
    PT_CMP,
    PT_CALL,
    PT_RET,
    PT_AND,
    PT_OR,
    PT_XOR,
    PT_SHL,
    PT_SHR,
    PT_JMP
}

typedef struct {
    uint8_t type;
    union {
        int64_t imm;
        uint64_t umm;
        struct { uint8_t r; int32_t disp; } reg;
    } value;
} pt_jit_arg_t;

typedef struct pt_jit_inst_t {
    int op;
    pt_jit_arg_t src;
    pt_jit_arg_t dst;
    pt_jit_size_t isize;
    struct pt_jit_inst_t* next;
} pt_jit_inst_t;

typedef struct {
    void* code;
    size_t size;
    pt_jit_inst_t* head;
    pt_jit_inst_t* tail;
} pt_jit_ctx_t;

pt_jit_arg_t pt_jit_reg(int reg);

pt_jit_arg_t pt_jit_ptr(int reg);

pt_jit_arg_t pt_jit_optr(int reg, uint32_t offset);

pt_jit_arg_t pt_jit_label(pt_label_t)

void pt_jit_inst1(pt_jit_ctx_t* ctx, int op, pt_jit_arg_t arg, pt_jit_size_t isize);

void pt_jit_inst(pt_jit_ctx_t* ctx, int op, pt_jit_arg_t dst, pt_jit_arg_t src, pt_jit_size_t isize);

#endif // _PT_JIT_H
