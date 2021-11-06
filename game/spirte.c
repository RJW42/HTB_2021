#include "game.h"
#include "sprite.h"
#include "../libc/mem.h"
#include "../cpu/types.h"
#include "../drivers/vga.h"

/* ***** Player ***** */
void _draw_player(Sprite* self);
bool _collision_player(Sprite* self, Sprite* other);

Player* new_player(int x, int y, int width, int height){
    // Malloc Player Mem 
    Player* self = (Player*) malloc(sizeof(Player));

    // Init vars
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->draw = _draw_player;
    self->collision = _collision_player;
    self->cooldown = 0;

    return self;
}


void _draw_player(Sprite* s){
    // Get Player object
    Player* self = (Player*)s;

    // Draw player 
    for(int x = self->x; x < self->x + self->width && x<320; x++){
        for(int y = self->y; y < self->y + self->height && y<200; y++){
            put_buffer_exact(x, y, (u8)40);
        }
    }
}

void _draw_enemy(Sprite* s){
    // Get Player object
    Enemy* self = (Enemy*)s;

    // Draw player 
    for(int x = self->x; x < self->x + self->width && x<320; x++){
        for(int y = self->y; y < self->y + self->height && y<200; y++){
            put_buffer_exact(x, y, (u8)40);
        }
    }
}

bool _collision_player(Sprite *s, Sprite *other){
    // Get Player Object
    Player *self = (Player*)s;

    return false;
}

void _wave_make_move(Wave *self){

    Move *m = self->path[self->next_move];

    for (int i = 0; i < self->enemies_length; i++){
        Enemy *e = self->enemies[i];
        e->x = e->x + m->x;
        e->y = e->y + m->y;

        if (e->x <= 0) {
            e->x = 320;
        }
    }

    // Increment to next move in path
    if (self->repetitions_till_next <= 0) {
        
        self->repetitions_till_next = self->move_repetitions;
        self->next_move = self->next_move + 1;
          
        if (self->next_move >= self->path_length) {
            self->next_move = 0;
        }
    } else {
        self->repetitions_till_next = self->repetitions_till_next - 1;
    }
  
}

/* ***** Enemy ***** */
Enemy* new_enemy(int x, int y, int width, int height){

    Enemy* self = (Enemy*) malloc(sizeof(Enemy));

    // Init vars
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->draw = _draw_player;
    self->collision = _collision_player;
    
    self->draw = _draw_enemy;
    self->collision = _collision_player;

    return self;
}

Wave* new_wave(Enemy** enemies, int enemies_length, Move** path, int path_length) {
    // Allocate memory for object
    Wave* self = (Wave*) malloc(sizeof(Wave));

    self->move_repetitions = 10;
    self->repetitions_till_next = self->move_repetitions;

    // Next move index is start of path
    self->next_move = 0;
    self->make_move = _wave_make_move;

    // Set pointers for enemy and path arrays
    self->enemies_length = enemies_length;
    self->enemies = enemies;
    self->path_length = path_length;
    self->path = path;
    
    return self;
}

Move* new_move(int x, int y) {
    // Allocate memory for object
    Move* self = (Move*) malloc(sizeof(Move));

    // Set direction attributes
    self->x = x;
    self->y = y;

    return self;
}
