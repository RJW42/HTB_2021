
#include "game.h"
#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "../libc/mem.h"
#include "../cpu/timer.h"
#include "sprite.h"

// Main game driver code
void run_game() {

    // Get the keys pressed 
    u8* keys = get_key_presses();

    // Init game state 
    bool done = false;

    // Init Player 
    Player *p = new_player(90, 0, 20, 20);
    u32 previous_time = get_time();

    // Game loop
    while(!done) {
        p->draw((Sprite*)p);
        //player_input(keys, p);
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