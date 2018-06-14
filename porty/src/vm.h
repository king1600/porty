#ifndef _PT_VM_H
#define _PT_VM_H

#include "map.h"

typedef struct pt_func_t pt_func_t;
typedef struct pt_module_t pt_module_t;
typedef union union { pt_binary_t bin; uint16_t index; } pt_const_data_t;
typedef struct { uint8_t type; pt_const_data_t value; } pt_const_t;

struct pt_func_t {
    pt_module_t* module;
    pt_binary_t name;
    uint8_t num_args;
    uint8_t num_locals;
    pt_func jit_code;
    uint8_t* byte_code;
};

struct pt_module_t {
    pt_binary_t name;
    pt_map_t funcs;
};

struct pt_vm_t {
    uint32_t num_actors;
    pt_map_t atoms;
};

#endif // _PT_VM_H