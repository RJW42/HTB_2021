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
