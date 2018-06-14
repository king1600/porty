#include "port.h"
#include <string.h>

pt_hash_t pt_hash(pterm_t value) {
    switch (PT_TYPE(value)) {
        case PT_TYPE_DATA:
        case PT_TYPE_PORT:
        case PT_TYPE_FUNC:
        case PT_TYPE_BINARY:
        case PT_TYPE_ARRAY:
        case PT_TYPE_LIST:
        case PT_TYPE_MAP:
        case PT_TYPE_ATOM:
        case PT_TYPE_INT:
        case PT_TYPE_FLOAT:
        default:
            return -1;
    }
}

// -1: bad types, 0: equal, 1: good types, not equal
int pt_compare(pterm_t left, pterm_t right) {
    const uint8_t left_type = PT_TYPE(left);
    const uint8_t right_type = PT_TYPE(right);

    if (left_type != right_type)
        return -1;
    
    switch (left_type) {
        case PT_TYPE_DATA:
            return left.uptr != right.uptr;
        case PT_TYPE_PORT:
            return ((pt_port_t*)left.uptr)->id == ((pt_port_t*)right.uptr)->id;
        case PT_TYPE_FUNC:

        case PT_TYPE_BINARY:
        case PT_TYPE_ARRAY:
        case PT_TYPE_LIST:
        case PT_TYPE_MAP:
        case PT_TYPE_ATOM:
        case PT_TYPE_INT:
        case PT_TYPE_FLOAT:
        default:
            return -1;
    }
}