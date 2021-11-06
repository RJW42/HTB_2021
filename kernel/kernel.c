#include "../drivers/vga.h"
#include "../cpu/gdt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../game/game.h"
#include "../game/sprite.h"

void init();


void main() {
    // Initilise The OS 
    init();

    // Run game
    run_game();


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

