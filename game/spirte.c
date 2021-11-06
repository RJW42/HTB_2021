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

    return self;
}


void _draw_player(Sprite* s){
    // Get Player object
    Player* self = (Player*)s;

    // Draw player 
    for(int x = self->x; x < self->x + self->width && x<320; x++){
        for(int y = self->y; y < self->y + self->height && y<200; y++){
            put_pixel_exact(x, y, (u8)40);
        }
    }
}

bool _collision_player(Sprite *s, Sprite *other){
    // Get Player Object 
    Player *self = (Player*)s;

    return false;
}

/* ***** Enemy ***** */
Enemy* new_enemy(int x, int y, int width, int height){
    return (Enemy*)0;
}