#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "../cpu/isr.h"
#include "../libc/mem.h"
#include "../game/game.h"

void draw2(sprite *self, u8 x_coord, u8 y_coord);

// Main game driver code
void run_game() {

    // Get the keys pressed 
    u8* keys = get_key_presses();

    u8 done = 0;

    // Random sprite
    sprite *box = (sprite*)malloc(sizeof(sprite));

    // zeroing memory
    memory_set((u8*)box, 0, sizeof(sprite)); 

    box->draw=&draw2;
    box->height=50;
    box->width=50;


    // Game loop
    while(!done) {
        // if(keys[KEY_1]){
        //     for(int x = 0; x < 320; x++)
        //         for(int y = 0; y < 200; y++)
        //             put_pixel(x, y, 0, 50, 0);
        // }else{
        //     for(int x = 0; x < 320; x++)
        //         for(int y = 0; y < 200; y++)
        //             put_pixel(x, y, 50, 0, 0);
        // }
        (*box->draw)(box, 30, 30);
    }

}

// Function to draw a sprite to the screen, currently box remove later
void draw2(sprite *self, u8 x_coord, u8 y_coord) {
    for(int x = x_coord; x < x_coord + self->width; x++)
        for(int y = y_coord; y < y_coord + self->height; y++)
            put_pixel(x, y, 0, 50, 0);
}