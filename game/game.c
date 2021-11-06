
#include "game.h"
#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "../libc/mem.h"
#include "../cpu/timer.h"
#include "sprite.h"
<<<<<<< HEAD
#include "../libc/rand.h"

#define NUM_STARS 60
#define PLAYER_MOVE_COOLDOWN 15
=======
>>>>>>> 4cb0eaf45ce205348f64cad0a367953397da2f58

// Init functions 
void wait_until(u32 time);
void player_input(u8* keys, Player *p, int *movement_cooldown);
void wave_update(Wave *wave);
void all_bullet_update(Bullet** bs);
void bullet_update(Bullet* b);
bool check_enemy_contact(Player *player, Wave *wave);
void check_bullet_contact(Player *player, Wave *wave);

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
    Enemy *enemy3 = new_enemy(100, 110, 20, 20);

    Move *move1 = new_move(-1, 2);
    Move *move2 = new_move(-1, 0);
    Move *move3 = new_move(-1, -2);

    Text * score_text = new_text(5, 191, 8, 8, "SCORE 0", 7);

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
        
        score_text->draw((Sprite*)score_text);

        p->draw((Sprite*)p);

        // Draw all bullets
        for(int i = 0; i < BULLETS; i++) {
                if(!(p->bullets[i]->invisible)) {
                    // Use this bullet
                    Bullet* b = (Bullet*)(p->bullets[i]);
                    b->draw((Sprite*)b);
                    
                }
            }

        player_input(keys, (Player*)p, &movement_cooldown);

        // Draw all bullets
        all_bullet_update(p->bullets);

        wave_update(wave);

        flush_buffer();

        check_bullet_contact(p, wave);

        // Check for end condition 
        done = check_enemy_contact(p, wave);
    }
}

void all_bullet_update(Bullet** bs) {
    static int tempo = 0;

    if(++tempo <= 15) {
        
        return;
    }

    tempo = 0;
    
    for(int i = 0; i < BULLETS; i++) {
                    if(!(bs[i]->invisible)) {
                        // Use this bullet
                        Bullet* b = (Bullet*)(bs[i]);
                        bullet_update(b);
                        
                    }
                }
}

void bullet_update(Bullet* b) {
    

    if(b->x + b->width >= 360) {
        b->invisible = true;
        b->x = 0;
        b->y = 0;
        return;
    }
    b->x += 1;
}

bool check_enemy_contact(Player *player, Wave *wave) {
    // for enemy in wave: if enemy X range and player X range overlap
    // if enemy Y range and player Y range overlap
    // Then they have hit, print a random orange square
    for (int i = 0; i < wave->enemies_length; i++) {
        Enemy *enemy = wave->enemies[i];
        int offset_x = player->x + player->width;
        int offset_y = player->y + player->height;

        if (!enemy->invisible) {
        if ((player->x >= enemy->x && player->x <= (enemy->x + enemy->width)) || (offset_x >= enemy->x && offset_x <= (enemy->x + enemy->width))) {
            if ((player->y >= enemy->y && player->y <= (enemy->y + enemy->height)) || (offset_y >= enemy->y && offset_y <= (enemy->y + enemy->height))) {
                return true;
            }
        }
        }
    }

    return false;
}

void check_bullet_contact(Player *player, Wave *wave) {
    // For bullet in bullets, for enemy in wave, if both visible, if they both intersect then they both become invisible.
    for (int i = 0; i < BULLETS; i++) {
        Bullet *b = player->bullets[i];
        if (b->invisible) {
            continue;
        }
        for (int j = 0; j < wave->enemies_length; j++) {
            Enemy *e = wave->enemies[i];
            if (e->invisible) {
                continue;
            }

            int offset_x = b->x + b->width;
            int offset_y = b->y + b->height;

            if ((b->x >= e->x && b->x <= (e->x + e->width)) || (offset_x >= e->x && offset_x <= (e->x + e->width))) {
            if ((b->y >= e->y && b->y <= (e->y + e->height)) || (offset_y >= e->y && offset_y <= (e->y + e->height))) {
                b->invisible = true;
                e->invisible = true;
            }
        }

        }

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
    static int bullet_cooldown = 400;

    --bullet_cooldown;

    if(keys[KEY_K]) {
        // Up

        // Check that not going to go out of bounds 
        if (p->y <= 10) {
            return;
        }

        // Move player up
        y_minus++;
        y_plus = 0;

        if(y_minus >= PLAYER_MOVE_COOLDOWN){
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

        if(y_plus >= PLAYER_MOVE_COOLDOWN){
            p->y+=1;
            y_plus = 0;
        }
    } else if (keys[KEY_A]) {
        // Shoot

        if(bullet_cooldown <= 0) {
            // Shoot the bullet

            // Finding a bullet that is currently invisible i.e not in use
            for(int i = 0; i < BULLETS; i++) {
                if((p->bullets[i]->invisible)) {
                    // Use this bullet
                    Bullet* b = (Bullet*)(p->bullets[i]);
                    b->invisible = false;
                    b->x = p->x + p->width;
                    b->y = p->y + (p->height / 2) - 1;
                    break;
                }
            }

            // reset the counter
            bullet_cooldown = 400;
        }

        

    }
}