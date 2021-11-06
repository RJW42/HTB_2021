#include "../drivers/vga.h"
#include "../cpu/gdt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../game/game.h"
#include "../game/sprite.h"

void init();
void openGame();
void gameOver();

void main() {
    // Initilise The OS 
    init();

    // Display Start
    openGame();

    u8* keys = get_key_presses();

    while(!keys[KEY_ENTER]){

    }

    // Run game
    run_game();

    // Game Over
    gameOver();
    /*
    for(int x = 0; x < 63; x++){
        put_pixel_exact(x, 0, x);
        put_pixel_exact(x, 1, x);
        put_pixel_exact(x, 2, x);
        put_pixel_exact(x, 3, x);
        put_pixel_exact(x, 4, x);
        put_pixel_exact(x, 5, x);
        put_pixel_exact(x, 6, x);
        put_pixel_exact(x, 7, x);
    }*/
}


void init(){
    // Init the global discriptor tbale 
    gdt_install();
    
    // Init the interrupt service routine 
    isr_install();
    
    // Init Time 
    asm volatile("sti");
    // Increase num => increase framerate 
    // Decrease num <= decrease framerate 
    // Big num go fast 
    init_timer(1000);
    
    // Init keyboard
    init_keyboard();
    
    // Set the CPU into graphics mode. Width = 320, Height = 200, ColorDepth = 8
    set_vga_mode(320, 200, 8);

    // Clear screen to black 
    for(int x = 0; x < 320; x++)
        for(int y = 0; y < 200; y++)
            put_pixel_exact(x, y, 0);
}

void openGame(){

    Text *Title = new_text(30,50,0,0,"SPACEHAWK!",10);
    Text *SubHeader1 = new_text(30,80,0,0,"YOU ARE ON YOUR OWN.",20);
    Text *SubHeader2 = new_text(30,100,0,0,"GET OUT OF THERE!",17);
    Text *SubHeader3 = new_text(30,140,0,0,"PRESS ENTER TO BEGIN!...",24);

    Helper *helper = new_helper(70,250,0,0);

    Title->draw((Sprite *) Title);
    SubHeader1->draw((Sprite *) SubHeader1);
    SubHeader2->draw((Sprite *) SubHeader2);
    SubHeader3->draw((Sprite *) SubHeader3);

    helper->draw((Sprite *) helper);

    flush_buffer();
}


void gameOver(){
    for(int x = 0; x < 320; x++){
        for(int y = 0; y < 200; y++){
            put_buffer_exact(x, y, 0);
        }
    }

    Text *Title = new_text(152,96,0,0,"GAME OVER!",10);

    Title->draw((Sprite *) Title);

    flush_buffer();
}

