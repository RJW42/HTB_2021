#include "game.h"
#include "../libc/mem.h"
#include "../cpu/types.h"
#include "../drivers/vga.h"


void _draw_square(Sprite *s){
    // Cast s to square 
    Square *self = (Square*)s;

    for(int x = 0; x < self->height; x++){
        for(int y = 0; y < self->width; y++){
            put_pixel(x, y, 0, 50, 0);
        }
    }
}

Square* new_square(int height, int width){
    Square* self = (Square*)malloc(sizeof(Square));
    self-> x = 0;
    self-> y = 0;
    self->height = height;
    self->width = width;
    self->draw = _draw_square;
    return self;
}
