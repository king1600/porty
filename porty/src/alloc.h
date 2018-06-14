#ifndef _PT_ALLOC_H
#define _PT_ALLOC_H

#include <stddef.h>

// allocator functions
#define PT_FREE rpfree
#define PT_MALLOC rpmalloc
#define PT_CALLOC rpcalloc
#define PT_REALLOC rprealloc
#define PT_MEM_FREE rpmalloc_finalize
#define PT_MEM_INIT rpmalloc_initialize
#define PT_MEM_THREAD_FREE rpmalloc_thread_finalize
#define PT_MEM_THREAD_INIT rpmalloc_thread_initialize

// builtins
#define PT_CACHE_LOW  0
#define PT_CACHE_MED  1
#define PT_CACHE_HIGH 2
#define PT_THREAD_LOCAL __thread
#define PT_FIRST_BIT(x) __builtin_ffsll(x)
#define PT_UNREACHABLE() __builtin_unreachable()
#define PT_MALLOC_ATTR __attribute__((__malloc__))
#define PT_LIKELY(expr) __builtin_expect(!!(expr), 1)
#define PT_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#define PT_FORCE_INLINE __attribute__((always_inline)) inline
#define PT_NEXT_POW2(x) (1ULL << (64ULL - __builtin_clzl((x) - 1ULL)))
#define PT_PREFETCH_READ(addr, locality) __builtin_prefetch(addr, 0, locality)
#define PT_PREFETCH_WRITE(addr, locality) __builtin_prefetch(addr, 1, locality)

// rpmalloc symbols
void rpmalloc_finalize();
void rpmalloc_initialize();
void rpmalloc_thread_collect();
void rpmalloc_thread_finalize();
void rpmalloc_thread_initialize();
void rpfree(void* ptr);
void* rprealloc(void* ptr, size_t size);
void* rpmalloc(size_t bytes) PT_MALLOC_ATTR;
void* rpcalloc(size_t nitems, size_t size) PT_MALLOC_ATTR;

#endif // _PT_ALLOC_H