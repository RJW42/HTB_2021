#ifndef GAME_H_
#define GAME_H_

#include "../cpu/types.h"

typedef struct Sprite {
    void (*draw)(struct Sprite *self);
    int x;
    int y;
    bool (*collision)(int x, int y, int width, int height);
} Sprite;

typedef struct Square {
    void (*draw)(Sprite *self);
    int x;
    int y;
    bool (*collision)(int x, int y, int width, int height);
    int height;
    int width;
} Square;


void _draw_square(Sprite *self);
Square* new_square(int height, int width);

 
#endif