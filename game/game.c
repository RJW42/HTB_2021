
#include "game.h"
#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "../libc/mem.h"
#include "../cpu/timer.h"
#include "sprite.h"

// Init functions 
void wait_until(u32 time);
void player_input(u8* keys, Player *p, int *movement_cooldown);
void wave_update(Wave *wave);

// Main game driver code
void run_game() {
    // Get the keys pressed 
    u8* keys = get_key_presses();

    // Init game state 
    bool done = false;

    // Init Player 
    Player *p = new_player(20, 90, 20, 20);

    u32 previous_time = get_time();

    Enemy *enemy1 = new_enemy(200, 70, 20, 20);
    Enemy *enemy2 = new_enemy(200, 110, 20, 20);

    Move *move1 = new_move(-1, 2);
    Move *move2 = new_move(-1, 0);
    Move *move3 = new_move(-1, -2);


    int enemy_len = 2;
    int move_len = 3;

    Enemy *enemies[2] = {enemy1, enemy2};

    Move *moves[3] = {move1, move2, move3};

    Wave *wave = new_wave(enemies, enemy_len, moves, move_len);

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

        for (int i = 0; i < enemy_len; i++){
            enemies[i]->draw((Sprite *)enemies[i]);
        }
        

        p->draw((Sprite*)p);

        player_input(keys, (Player*)p, &movement_cooldown);

        wave_update(wave);

        flush_buffer();

      

    }
}

void wave_update(Wave *wave) {
    static int counter = 100;
    if (--counter <= 0) {
        counter = 100;
        wave->make_move(wave);
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