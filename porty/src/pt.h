#ifndef _PT_H
#define _PT_H

// compatibility macros
#if !defined(__GNUC__) || !defined(__clang__)
    #error "Its better to compile with either GCC or Clang"
#endif
#if defined(_WIN32) || defined(_WIN64)
    #define PT_WINDOWS
    #error "Windows is not currently supported"
#elif defined(__linux__)
    #define PT_LINUX
#else
    #error "Platform not supported"
#endif

// standard headers
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// pt typedefs
typedef uint64_t pt_hash_t;
typedef struct pt_vm_t pt_vm_t;
typedef struct pt_actor_t pt_actor_t;
typedef union { double f64; int32_t i32; uint64_t u64; uintptr_t uptr; } pterm_t;
typedef struct { pterm_t head; pterm_t tail; } pt_list_t;
typedef struct { uint32_t size; pterm_t* data; } pt_array_t;
typedef struct { uint32_t size; uint8_t* data; } pt_binary_t;
typedef struct { uint32_t index; pterm_t key; pterm_t value; void* ptr; } pt_map_iter_t;
typedef pterm_t (*pt_func) (uint8_t argc, pterm_t* argv);
typedef pterm_t (*pt_native_func) (pt_actor_t* env, int argc, pterm_t* argv);

// object types & constants
#define PT_TYPE_DATA   0
#define PT_TYPE_PORT   1
#define PT_TYPE_FUNC   2
#define PT_TYPE_BINARY 3
#define PT_TYPE_ARRAY  4
#define PT_TYPE_LIST   5
#define PT_TYPE_MAP    6
#define PT_TYPE_ATOM   7
#define PT_TYPE_INT    8
#define PT_TYPE_FLOAT  9
#define PT_NULL PT_FROM(PT_TYPE_ATOM, 0)
#define PT_TRUE PT_FROM(PT_TYPE_ATOM, 1)
#define PT_FALSE PT_FROM(PT_TYPE_ATOM, 2)

// internal conversions, accessors & values
#define PT_NAN_SHIFT 51
#define PT_NAN_BITS 0b111111111111ULL
#define PT_TERM_SIZE sizeof(pterm_t)
#define PT_TERM_BITS (PT_TERM_SIZE << 3)
#define PT_INT_BIT (1ULL << (PT_TERM_BITS - 1))
#define PT_NAN_HEADER (PT_NAN_BITS << PT_NAN_SHIFT)
#define PT_IS_NAN(v) (((v).u64 & PT_NAN_HEADER) == PT_NAN_HEADER)
#define PT_FROM(type, value) ((pterm_t){ .u64 = (((PT_NAN_BITS << 3) | type) << 48) | value })
#define PT_TYPE(v) (PT_IS_NAN(v) \
    ? PT_TYPE_FLOAT : (((v).u64 & PT_INT_BIT) \
    ? PT_TYPE_INT : (((v).u64 >> PT_NAN_SHIFT) & 0b111)))

// object type check functions
#define pt_is_float(v) (!PT_IS_NAN(v))
#define pt_is_int(v) ((v).u64 & PT_INT_BIT)
#define pt_is_data(v) (PT_TYPE(v) == PT_TYPE_DATA)
#define pt_is_port(v) (PT_TYPE(v) == PT_TYPE_PORT)
#define pt_is_func(v) (PT_TYPE(v) == PT_TYPE_FUNC)
#define pt_is_binary(v) (PT_TYPE(v) == PT_TYPE_BINARY)
#define pt_is_array(v) (PT_TYPE(v) == PT_TYPE_ARRAY)
#define pt_is_list(v) (PT_TYPE(v) == PT_TYPE_LIST)
#define pt_is_map(v) (PT_TYPE(v) == PT_TYPE_MAP)
#define pt_is_atom(v) (PT_TYPE(v) == PT_TYPE_ATOM)

// object allocators
pterm_t pt_alloc_data(size_t bytes);
pterm_t pt_alloc_array(uint32_t items);
pterm_t pt_alloc_map(bool is_probed);
pterm_t pt_alloc_binary(uint32_t bytes);
pterm_t pt_alloc_list(pterm_t head, pterm_t tail);
inline pterm_t pt_alloc_float(double number) { pterm_t v; v.f64 = number; return v; }
inline pterm_t pt_alloc_int(int32_t number) { pterm_t v = PT_FROM(PT_TYPE_INT,0); v.i32 = number; return v; }

// object accessors
bool pt_get_list(pterm_t value, pt_list_t* list);
bool pt_get_array(pterm_t value, pt_array_t* array);
bool pt_get_binary(pterm_t value, pt_binary_t* binary);
inline int32_t pt_get_int(pterm_t value) { return value.i32; }
inline double pt_get_float(pterm_t value) { return value.f64; }
void pt_map_iter_init(pterm_t map, pt_map_iter_t* it);
bool pt_map_iter_has_next(pterm_t map, pt_map_iter_t* it);
pterm_t pt_map_get(pterm_t map, uint64_t hash, pterm_t key);
pterm_t pt_map_drop(pterm_t map, uint64_t hash, pterm_t key);
pterm_t pt_map_put(pterm_t map, uint64_t hash, pterm_t key, pterm_t value);

// miscellanious
pterm_t pt_self();
void pt_gcollect(bool major);
pt_hash_t pt_hash(pterm_t value);
int pt_compare(pterm_t left, pterm_t right);
bool pt_send(pterm_t port, pterm_t value);

#endif // _PT_H