
#include "timer.h"
#include "../drivers/vga.h"
#include "../drivers/ports.h"
#include "isr.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
    for(int x = 0; x < 320; x++)
        for(int y = 0; y < 200; y++)
            if(tick){
                put_pixel(x, y, 20, 40, 10);
            }else{
                put_pixel(x, y, 50, 50, 50);
            }

    tick = !tick;
}

void init_timer(u32 freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}