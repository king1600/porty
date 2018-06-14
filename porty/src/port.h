#ifndef _PT_PORT_H
#define _PT_PORT_H

#include "pt.h"

#define PT_PORT_ACTOR 0
#define PT_PORT_TCP   1
#define PT_PORT_UDP   2
#define PT_PORT_SSL   3
#define PT_PORT_TTY   4
#define PT_PORT_PIPE  5
#define PT_PORT_SOCK  6

typedef struct {
    uint64_t id; // [type:8, metadata:24, descriptor:32]
} pt_port_t;

struct pt_actor_t {
    pt_port_t port;
};

#endif // _PT_PORT_H