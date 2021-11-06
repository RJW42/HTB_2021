
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
    // Player *p = new_player(90, 0, 20, 20);
    u32 previous_time = get_time();

    // Game loop
    while(!done) {

    }

}