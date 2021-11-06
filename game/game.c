
#include "game.h"
#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "../libc/mem.h"
#include "../cpu/timer.h"
#include "sprite.h"

// Init functions 
void wait_until(u32 time);

// Main game driver code
void run_game() {
    // Get the keys pressed 
    u8* keys = get_key_presses();

    // Init game state 
    bool done = false;

    // Init Player 
    Player *p = new_player(90, 0, 20, 20);
    u32 previous_time = get_time();
    u8 test = 0;

    // Game loop
    while(!done) {

        // Get time of last frame  then update previos time. 
        // We update previous time now as we want to record 
        // the time it took to write the game logic 
        u32 current_time = get_time();

        if(current_time - previous_time < 40){
            put_pixel_exact(0, 0, 0);
            continue;
        }

        // End of timer information. Start of game logic
        
        for(int x = 0; x < 360; x++){
            for(int y = 0; y < 200; y++){
                put_pixel_exact(x, y, test);
            }
        }
        
        test++;

    }
}


void player_input(u8* keys, Player *p) {
    if(KEY_K) {
        // Up

        // Check that not going to go out of bounds 
        if (p->y == 10) {
            return;
        }

        // Move player up
        p->y++;
    } else if (KEY_L) {
        // Down

        // Check that not going to go out of bounds 
        if (p->y == 170) {
            return;
        }

        // Move player down
        p->y--;
    } else if (KEY_A) {
        // Shoot

        // Check able to shoot
        if(p->cooldown != 0) {
            p->cooldown--;
        } else {
            // Able to shoot

            // Reset cooldown
            p->cooldown = 10;
        }

}
}