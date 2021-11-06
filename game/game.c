#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "../cpu/isr.h"


// Main game driver code
void run_game() {

    // Get the keys pressed 
    u8* keys = get_key_presses();

    int done = 0;

    // Game loop
    while(!done) {
        if(keys[KEY_1]){
            for(int x = 0; x < 320; x++)
                for(int y = 0; y < 200; y++)
                    put_pixel(x, y, 0, 50, 0);
        }else{
            for(int x = 0; x < 320; x++)
                for(int y = 0; y < 200; y++)
                    put_pixel(x, y, 50, 0, 0);
        }
    }

}