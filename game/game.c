
#include "game.h"
#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "../libc/mem.h"
#include "../cpu/timer.h"
#include "sprite.h"

// Init functions 
void wait_until(u32 time);
void player_input(u8* keys, Player *p, int *movement_cooldown);

// Main game driver code
void run_game() {
    // Get the keys pressed 
    u8* keys = get_key_presses();

    // Init game state 
    bool done = false;

    // Init Player 
    Player *p = new_player(20, 90, 20, 20);

    u32 previous_time = get_time();

//     Enemy *enemy1 = new_enemy(90, 0, 20, 40);
//     Enemy *enemy2 = new_enemy(10, 10, 20, 20);
//     Enemy *enemy3 = new_enemy(10, 10, 20, 20);

//     Move *move2 = new_move(0, 0);

//     int enemy_len = 2;
//     int move_len = 1;

//     Enemy *enemies[2] = {enemy1, enemy2};

//     Move *moves[1] = {move2};

//     Wave *wave = new_wave(enemies, enemy_len, moves, move_len);

//     // Game loop
//     while(!done) {
//         // p->draw((Sprite *) p);
//         for (int i = 0; i < enemy_len; i++){
//             enemies[i]->draw((Sprite *)enemies[i]);
//         }
    int movement_cooldown = 0;

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
        for (int i = 0; i < 320; i++) {
            for (int j = 0; j < 200; j++) {
                put_buffer_exact(i, j, 0);
            }
        }

        p->draw((Sprite*)p);

        player_input(keys, (Player*)p, &movement_cooldown);


        flush_buffer();

      

    }
}


void player_input(u8* keys, Player *p, int *movement_cooldown) {
    static int y_plus = 0;
    static int y_minus = 0;


    if(keys[KEY_K]) {
        // Up

        // Check that not going to go out of bounds 
        if (p->y <= 10) {
            return;
        }

        // Move player up
        y_minus++;
        y_plus = 0;

        if(y_minus >= 10){
            p->y -= 1;
            y_minus = 0;
        }
    } else if (keys[KEY_L]) {
        // Down

        // Check that not going to go out of bounds 
        if (p->y >= 170) {
            return;
        }

        // Move player down
        y_plus++;
        y_minus = 0;

        if(y_plus >= 10){
            p->y+=1;
            y_plus = 0;
        }
    } else if (keys[KEY_A]) {
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