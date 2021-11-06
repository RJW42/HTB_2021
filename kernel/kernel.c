#include "../drivers/vga.h"
#include "../cpu/gdt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"


void init();


void main() {
    // Initilise The OS 
    init();

    // Print a graphic to the screen
    for(int x = 0; x < 320; x++)
        for(int y = 0; y < 200; y++){
            if(x % 2 == 0){
                put_pixel(x, y, 50, 50, 0);
            }else{
                put_pixel(x, y, 50, 0, 0);
            }
        }

    u8* keys = get_key_presses();
   
    while(1 == 1){
        if(keys[KEY_1]){
            for(int x = 0; x < 320; x++)
                for(int y = 0; y < 200; y++)
                    put_pixel(x, y, 0, 50, 0);
        }else{
            for(int x = 0; x < 320; x++)
                for(int y = 0; y < 200; y++)
                    put_pixel(x, y, 50, 0, 0);
        }
    }
}


void init(){
    // Init the global discriptor tbale 
    gdt_install();
    
    // Init the interrupt service routine 
    isr_install();
    
    // Init Time 
    asm volatile("sti");
    init_timer(50);
    
    // Init keyboard
    init_keyboard();
    
    // Set the CPU into graphics mode. Width = 320, Height = 200, ColorDepth = 8
    set_vga_mode(320, 200, 8);
}
