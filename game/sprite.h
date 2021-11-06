#ifndef SPRITE_H_
#define SPRITE_H_
#define BULLETS 25
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

struct Bullet {
    void (*draw)(struct Sprite *self);
    int x;
    int y;
    int frame;
    int width;
    int height;
    bool (*collision)(struct Sprite *self, struct Sprite *other);
    bool invisible;
 } __attribute__((packed));

struct Player {
    void (*draw)(struct Sprite *self);
    int x;
    int y;
    int frame;
    int width;
    int height;
    bool (*collision)(struct Sprite *self, struct Sprite *other);
    struct Bullet** bullets;
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



struct Move {
    int x;
    int y;
} __attribute__((packed));

struct Wave {
    int move_repetitions;
    int repetitions_till_next;
    int next_move;
    int enemies_length;
    int path_length;
    struct Enemy** enemies;
    struct Move** path;
    void (*make_move)(struct Wave *self);
} __attribute__((packed));

typedef struct Sprite Sprite;
typedef struct Enemy Enemy;
typedef struct Player Player;
typedef struct Move Move;
typedef struct Wave Wave;
typedef struct Bullet Bullet;

Player* new_player(int x, int y, int width, int height);
Enemy* new_enemy(int x, int y, int width, int height);
Wave* new_wave(Enemy** enemies, int enemies_length, Move** path, int path_length);
Move* new_move(int x, int y);

#endif