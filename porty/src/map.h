#ifndef _PT_MAP_H
#define _PT_MAP_H

#include "pt.h"

#define PT_MAP_PROBED 0
#define PT_MAP_CHAINED 1
typedef struct pt_cell_probed_t pt_cell_probed_t;
typedef struct pt_cell_chained_t pt_cell_chained_t;

typedef struct {
    void* cells;
    uint8_t type;
    uint32_t size;
    uint32_t capacity;
} pt_map_t;

void pt_map_init(pt_map_t* map, const uint8_t type);

size_t pt_map_probe(pt_map_t* map, const pt_hash_t hash, const pterm_t key);

pterm_t pt_map_get(pt_map_t* map, const pt_hash_t hash, const pterm_t key);

pterm_t pt_map_drop(pt_map_t* map, const pt_hash_t hash, const pterm_t key);

pterm_t pt_map_put(pt_map_t* map, const pt_hash_t hash, const pterm_t key, const pterm_t value);

#endif // _PT_MAP_H