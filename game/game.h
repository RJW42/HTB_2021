#ifndef GAME_H_
#define GAME_H_

#include "../cpu/types.h"

struct sprite_struct_ {
    void (*draw)(struct sprite_struct_ *self);
    int x;
    int y;
}__attribute__((packed));

typedef struct sprite_struct_ sprite;

void run_game();

#endif