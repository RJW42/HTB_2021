
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

    Enemy *enemy1 = new_enemy(90, 0, 20, 40);
    Enemy *enemy2 = new_enemy(10, 10, 20, 20);
    Enemy *enemy3 = new_enemy(10, 10, 20, 20);

    Move *move2 = new_move(0, 0);

    int enemy_len = 2;
    int move_len = 1;

    Enemy *enemies[2] = {enemy1, enemy2};

    Move *moves[1] = {move2};

    Wave *wave = new_wave(enemies, enemy_len, moves, move_len);

    // Game loop
    while(!done) {
        // p->draw((Sprite *) p);
        for (int i = 0; i < enemy_len; i++){
            enemies[i]->draw((Sprite *)enemies[i]);
        }
    }

}