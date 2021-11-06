#ifndef GAME_H_
#define GAME_H_

#include "../cpu/types.h"

struct sprite_struct_ {
    void (*draw)(sprite *self);
    int x;
    int y;
}__attribute__((packed));

typedef struct sprite_struct_ sprite;

#endif