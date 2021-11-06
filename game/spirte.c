#include "game.h"
#include "sprite.h"
#include "../libc/mem.h"
#include "../cpu/types.h"
#include "../drivers/vga.h"
#include "text.h"

/* ***** Player ***** */
void _draw_player(Sprite* self);
bool _collision_player(Sprite* self, Sprite* other);
bool _collision_bullet(Sprite *s, Sprite *other);
Bullet* new_bullet();
void _draw_bullet(Sprite* s);

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
    self->bullets = (Bullet**)malloc(sizeof(Bullet)*BULLETS);

    // Creating the bullets
    for(int i = 0; i < BULLETS; i ++) {
        self->bullets[i] = new_bullet();
    }
    return self;
}

Bullet* new_bullet() {
    Bullet* self = (Bullet*) malloc(sizeof(Bullet));
    static y = 0;
    // Init vars
    self->x = 0;
    self->y = y;
    self->width = 6;
    self->height = 3;
    self->draw = _draw_bullet;
    self->collision = _collision_bullet;
    self->invisible = true;
    y+= 4;
    return self;
}

void _draw_bullet(Sprite* self) {
    Bullet* b = (Bullet*)self;

    for(int x = self->x; x < self->x + self->width && x<320; x++){
        for(int y = self->y; y < self->y + self->height && y<200; y++){
            put_buffer_exact(x, y, (u8)40);
        }
    }
}

bool _collision_bullet(Sprite *s, Sprite *other) {
    return false;
}

void _draw_player(Sprite* s){
    // Get Player object
    Player* self = (Player*)s;

    // // Draw player 
    // for(int x = self->x; x < self->x + self->width && x<320; x++){
    //     for(int y = self->y; y < self->y + self->height && y<200; y++){
    //         put_buffer_exact(x, y, (u8)40);
    //     }
    // }

    int arr[20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 63, 63, 63, 63, 63, 63, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 63, 63, 9, 63, 63, 63, 36, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 36, 36, 63, 63, 63, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 36, 36, 36, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 63, 63, 63, 63, 36, 36, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 63, 63, 63, 63, 63, 36, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0}, 
        {0, 63, 63, 63, 63, 63, 63, 63, 36, 36, 63, 63, 63, 63, 63, 63, 63, 9, 9, 0},
        {0, 63, 63, 63, 63, 63, 63, 63, 36, 36, 63, 63, 63, 63, 63, 63, 63, 9, 9, 0},
        {0, 0, 0, 63, 63, 63, 63, 63, 36, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 63, 63, 63, 63, 36, 36, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 36, 36, 36, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 36, 36, 63, 63, 63, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 63, 63, 9, 63, 63, 63, 36, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 63, 63, 63, 63, 63, 63, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    for(int x = self->x; x < self->x + self->width && x<320; x++){
        for(int y = self->y; y < self->y + self->height && y<200; y++){
            put_buffer_exact(x, y,(u8) arr[y - self->y][x-self->x]);
        }
    }
}

    
void _draw_enemy(Sprite* s){
    // Get Enemy object
    Enemy* self = (Enemy*)s;

    // Draw Enemy 
    /*
    for(int x = self->x; x < self->x + self->width && x<320; x++){
        for(int y = self->y; y < self->y + self->height && y<200; y++){
            put_buffer_exact(x, y, (u8)40);
        }
    } */

    int arr[9][10] = {
        {11, 11, 0, 0, 0, 11, 11, 11, 11, 11},
        {0, 0, 11, 0, 11, 11, 11, 11, 11, 11},
        {0, 62, 32, 62, 11, 11, 0, 0, 0, 0},
        {0, 32, 32, 62, 62, 32, 32, 62, 32, 0},
        {62, 62, 62, 62, 62, 32, 32, 62, 32, 32},
        {0, 32, 32, 62, 62, 32, 32, 62, 32, 0},
        {0, 62, 32, 62, 11, 11, 0, 0, 0, 0},
        {0, 0, 11, 0, 11, 11, 11, 11, 11, 11},
        {11, 11, 0, 0, 0, 11, 11, 11, 11, 11}
    };

    for(int x = self->x; x < self->x + 10 && x<320; x++){
        for(int y = self->y; y < self->y + 9 && y<200; y++){
            put_buffer_exact(x, y,(u8) arr[y - self->y][x-self->x]);
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
    self->width = 10;
    self->height = 10;
    self->draw = _draw_player;
    self->collision = _collision_player;

    return self;
}

/* ***** Text ***** */
void _draw_text(Sprite* self);
bool _collision_text(Sprite* self, Sprite* other);
void text_loop(int letter[][8], int currentLetter, int posX, int posY);


Text* new_text(int x, int y, int width, int height, char* text, int textLength){
    // Malloc text Mem 
    Text* self = (Text*) malloc(sizeof(Text));

    // Init vars
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->draw = _draw_text;
    self->collision = _collision_text;
    self->text = text;
    self->textLength = textLength;
    return self;
}

void text_loop(int letter[][8], int currentLetter, int posX, int posY){
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            for (int x = 0; x < 2; x++){
                for (int y = 0; y < 2; y++){
                    if (letter[j][i]){
                        put_pixel_exact(posX + (i * 1) + x + (currentLetter * 9), posY + (j * 1) + y, 63);
                    } else {
                        put_pixel_exact(posX + (i * 1) + x + (currentLetter * 9), posY + (j * 1) + y, 0);
                    }
                    
                }
            }
        }
    }
}

void _draw_text(Sprite* s){
    //get text object
    Text *self = (Text*)s;

    int posX = self->x;
    int posY = self->y;
    

    for (int currentLetter = 0; currentLetter < self->textLength; currentLetter++){
        switch(self->text[currentLetter]){
            case 'A': ;
                int letter_A[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,0,0,0},{0,1,1,0,1,1,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,1,1,1,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0}};
                text_loop(letter_A, currentLetter, posX, posY);
                break;
            case 'B': ;
                int letter_B[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,1,1,1,1,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,1,1,1,1,0,0}};
                text_loop(letter_B, currentLetter, posX, posY);
                break;
            case 'C': ;
                int letter_C[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,1,0,0,1,1,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{0,1,1,0,0,1,1,0},{0,0,1,1,1,1,0,0}};
                text_loop(letter_C, currentLetter, posX, posY);
                break;
            case 'D': ;
                int letter_D[8][8] = {{0,0,0,0,0,0,0,0}, {1,1,1,1,1,0,0,0},{1,1,0,0,1,1,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,1,1,0,0},{1,1,1,1,1,0,0,0}};
                text_loop(letter_D, currentLetter, posX, posY);
                break;
            case 'E': ;
                int letter_E[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,0},{1,1,0,0,0,0,0,0},{1,1,1,0,0,0,0,0},{1,1,1,1,1,0,0,0},{1,1,1,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,1,1,1,1,0,0}};
                text_loop(letter_E, currentLetter, posX, posY);
                break;
            case 'F': ;
                int letter_F[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,0},{1,1,0,0,0,0,0,0},{1,1,1,1,1,0,0,0},{1,1,1,1,1,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0}};
                text_loop(letter_F, currentLetter, posX, posY);
                break;
            case 'G': ;
                int letter_G[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0},{0,1,1,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,1,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,0,1,1,1,1,1,0}};
                text_loop(letter_G, currentLetter, posX, posY);
                break;
            case 'H': ;
                int letter_H[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,1,1,1,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0}};
                text_loop(letter_H, currentLetter, posX, posY);
                break;
            case 'I': ;
                int letter_I[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{1,1,1,1,1,1,1,0}};
                text_loop(letter_I, currentLetter, posX, posY);
                break;
            case 'J': ;
                int letter_J[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,1,1,1,0,0}};
                text_loop(letter_J, currentLetter, posX, posY);
                break;
            case 'K': ;
                int letter_K[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,1,1,0,0},{1,1,0,1,1,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,0,1,1,1,0,0},{1,1,0,0,1,1,1,0}};
                text_loop(letter_K, currentLetter, posX, posY);
                break;
            case 'L': ;
                int letter_L[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,1,0,0,0,0,0},{1,1,1,1,1,1,1,0}};
                text_loop(letter_L, currentLetter, posX, posY);
                break;
            case 'M': ;
                int letter_M[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,1,1,1,1,0},{1,1,0,1,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0}};
                text_loop(letter_M, currentLetter, posX, posY);
                break;
            case 'N': ;
                int letter_N[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,1,0,0,1,1,0},{1,1,1,1,0,1,1,0},{1,1,1,1,1,1,1,0},{1,1,0,1,1,1,1,0},{1,1,0,0,1,1,1,0},{1,1,0,0,0,1,1,0}};
                text_loop(letter_N, currentLetter, posX, posY);
                break;
            case 'O': ;
                int letter_O[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,1,1,1,0,0}};
                text_loop(letter_O, currentLetter, posX, posY);
                break;
            case 'P': ;
                int letter_P[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,1,1,1,1,0,0},{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0}};
                text_loop(letter_P, currentLetter, posX, posY);
                break;
            case 'Q': ;
                int letter_Q[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,1,1,1,1,0},{1,1,0,0,1,1,0,0},{0,1,1,1,1,0,1,0}};
                text_loop(letter_Q, currentLetter, posX, posY);
                break;
            case 'R': ;
                int letter_R[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,1,1,1,0},{1,1,1,1,1,0,0,0},{1,1,0,1,1,1,0,0},{1,1,0,0,1,1,1,0}};
                text_loop(letter_R, currentLetter, posX, posY);
                break;
            case 'S': ;
                int letter_S[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,0,0,0},{1,1,0,0,1,1,0,0},{1,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,1,1,0,0,0}};
                text_loop(letter_S, currentLetter, posX, posY);
                break;
            case 'T': ;
                int letter_T[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0}};
                text_loop(letter_T, currentLetter, posX, posY);
                break;
            case 'U': ;
                int letter_U[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,1,1,1,0,0}};
                text_loop(letter_U, currentLetter, posX, posY);
                break;
            case 'V': ;
                int letter_V[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{0,1,1,1,1,1,0,0},{0,0,1,1,1,0,0,0},{0,0,0,1,0,0,0,0}};
                text_loop(letter_V, currentLetter, posX, posY);
                break;
            case 'W': ;
                int letter_W[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,1,0,1,1,0},{1,1,1,1,1,1,1,0},{1,1,1,1,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,0,0,0,1,1,0}};
                text_loop(letter_W, currentLetter, posX, posY);
                break;
            case 'X': ;
                int letter_X[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,1,0,1,1,1,0},{0,1,1,1,1,1,0,0},{0,0,1,1,1,0,0,0},{0,1,1,1,1,1,0,0},{1,1,1,0,1,1,1,0},{1,1,0,0,0,1,1,0}};
                text_loop(letter_X, currentLetter, posX, posY);
                break;
            case 'Y': ;
                int letter_Y[8][8] = {{0,0,0,0,0,0,0,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,1,1,1,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,0}};
                text_loop(letter_Y, currentLetter, posX, posY);
                break;
            case 'Z': ;
                int letter_Z[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,0},{0,0,0,0,1,1,1,0},{0,0,0,1,1,1,0,0},{0,0,1,1,1,0,0,0},{0,1,1,1,0,0,0,0},{1,1,1,0,0,0,0,0},{1,1,1,1,1,1,1,0}};
                text_loop(letter_Z, currentLetter, posX, posY);
                break;
            case '1': ;
                int letter_1[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{1,1,1,1,1,1,1,0}};
                text_loop(letter_1, currentLetter, posX, posY);
                break;
            case '2': ;
                int letter_2[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{1,1,0,0,0,1,1,0},{0,0,0,0,1,1,1,0},{0,0,1,1,1,1,0,0},{0,1,1,1,1,0,0,0},{1,1,1,0,0,0,0,0},{1,1,1,1,1,1,1,0}};
                text_loop(letter_2, currentLetter, posX, posY);
                break;
            case '3': ;
                int letter_3[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,1,1,1,0,0}};
                text_loop(letter_3, currentLetter, posX, posY);
                break;
            case '4': ;
                int letter_4[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,1,0,0},{0,0,1,1,1,1,0,0},{0,1,1,0,1,1,0,0},{1,1,0,0,1,1,0,0},{1,1,1,1,1,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,0,1,1,0,0}};
                text_loop(letter_4, currentLetter, posX, posY);
                break;
            case '5': ;
                int letter_5[8][8] = {{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,0},{1,1,0,0,0,0,0,0},{1,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,1,1,1,0,0}};
                text_loop(letter_5, currentLetter, posX, posY);
                break;
            case '6': ;
                int letter_6[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 1 ,1, 1, 1, 0, 0},{0, 1, 1, 0, 0, 0, 0, 0},{1, 1, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 0, 0},{1, 1, 0, 0, 0, 1, 1, 0},{1, 1, 0, 0, 0, 1, 1, 0},{0, 1, 1, 1, 1, 1, 0, 0}};
                text_loop(letter_6, currentLetter, posX, posY);
                break;
            case '7': ;
                int letter_7[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 0},{1, 1, 0, 0, 0, 1, 1, 0},{0, 0, 0, 0, 1, 1, 0, 0},{0, 0, 0, 1, 1, 0, 0, 0},{0, 0, 1, 1, 0, 0, 0, 0},{0, 0, 1, 1, 0, 0, 0, 0},{0, 0, 1, 1, 0, 0, 0, 0}};
                text_loop(letter_7, currentLetter, posX, posY);
                break;
            case '8': ;
                int letter_8[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},{0, 1, 1, 1, 1, 0, 0, 0},{1, 1, 0, 0, 0, 1, 0, 0},{1, 1, 1, 0, 0, 1, 0, 0},{0, 1, 1, 1, 1, 0, 0, 0},{1, 0, 0, 1, 1, 1, 1, 0},{1, 0, 0, 0, 0, 1, 1, 0},{0, 1, 1, 1, 1, 0, 0, 0}};
                text_loop(letter_8, currentLetter, posX, posY);
                break;
            case '9': ;
                int letter_9[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},{0, 1, 1, 1, 1, 1, 0, 0},{1, 1, 0, 0, 0, 1, 1, 0},{1, 1, 0, 0, 0, 1, 1, 0},{0, 1, 1, 1, 1, 1, 1, 0},{0, 0, 0, 0, 0, 1, 1, 0},{0, 0, 0, 0, 1, 1, 0, 0},{0, 1, 1, 1, 1, 0, 0, 0}};
                text_loop(letter_9, currentLetter, posX, posY);
                break;
            case '0': ;
                int letter_0[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,0,0,0},{0,1,0,0,1,1,0,0},{1,1,0,0,1,1,1,0},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,0},{0,1,1,0,0,1,0,0},{0,0,1,1,1,0,0,0}};
                text_loop(letter_0, currentLetter, posX, posY);
                break;
            case ' ': ;
                int letter_spc[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
                text_loop(letter_spc, currentLetter, posX, posY);
                break;
            case '!': ;
                int letter_exc[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0}};
                text_loop(letter_exc, currentLetter, posX, posY);
                break;
            case '.': ;
                int letter_period[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0}};
                text_loop(letter_period, currentLetter, posX, posY);
                break;
        }
    }
}

bool _collision_text(Sprite *s, Sprite *other){
    return false;
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



/* ***** Stars ***** */
void _draw_star(Sprite* s);


Star* new_star(int y, u8 color){
    // Allocate memory 
    Star* self = (Star*) malloc(sizeof(Star));

    self->x = 315;
    self->y = y;
    self->height = 1;
    self->width = 2;
    self->color = color;
    self->draw = _draw_star;
}


void _draw_star(Sprite* s){
    // Get Star object
    Star* self = (Star*)s;

    // Draw Star 
    for(int x = self->x; x < self->x + self->width && x<320; x++){
        for(int y = self->y; y < self->y + self->height && y<200; y++){
            put_buffer_exact(x, y, self->color);
        }
    }
}