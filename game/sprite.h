#ifndef SPRITE_H_
#define SPRITE_H_

#include "../cpu/types.h"

struct Sprite {
    void (*draw)(struct Sprite *self);
    int x;
    int y;
    int frame;
    int width;
    int height;
    bool (*collision)(struct Sprite *self, struct Sprite *other);
} __attribute__((packed));

struct Player {
    void (*draw)(struct Sprite *self);
    int x;
    int y;
    int frame;
    int width;
    int height;
    bool (*collision)(struct Sprite *self, struct Sprite *other);
} __attribute__((packed));

struct Enemy {
    void (*draw)(struct Sprite *self);
    int x;
    int y;
    int frame;
    int width;
    int height;
    bool (*collision)(struct Sprite *self, struct Sprite *other);
} __attribute__((packed));


typedef struct Sprite Sprite;
typedef struct Enemy Enemy;
typedef struct Player Player;

Player* new_player(int x, int y, int width, int height);
Enemy* new_enemy(int x, int y, int width, int height);


#endif