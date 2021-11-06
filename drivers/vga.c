#include "./ports.h"
#include "./vga.h"
#include "../cpu/types.h"


// VGA Ports
#define VGA_MISC_PORT 0x3c2
#define CRTC_INDEX_PORT 0x3d4
#define CRTC_DATA_PORT 0x3d5
#define SEQUENCER_INDEX_PORT 0x3c4
#define SEQUENCER_DATA_PORT 0x3c5
#define GRAPHICS_CONTROLLER_INDEX_PORT 0x3ce
#define GRAPHICS_CONTROLLER_DATA_PORT 0x3cf
#define ATTRIBUTE_CONTROLLER_INDEX_PORT 0x3c0
#define ATTRIBUTE_CONTROLLER_READ_PORT 0x3c1
#define ATTRIBUTE_CONTROLLER_WRITE_PORT 0x3c0
#define ATTRIBUTE_CONTROLLER_RESET_PORT 0x3da

#define UNSET (u8*)42


// Define gloabls 
u8* frame_buffer_segment = UNSET;


// Define hidden functions 
int supports_mode(u32 width, u32 height, u32 color_depth);

void write_vga_registers(u8* registers);

u8* get_frame_buffer_segment();
u8* get_preset_frame_buffer_segment();



// Define functions 
int set_vga_mode(u32 width, u32 height, u32 color_depth){
    // Check if the mode is unsuported 
    if(!supports_mode(width, height, color_depth)){
        return 0;
    }

    // Set the onde mode 
    u8 g_320x200x256[] = {
        /* MISC */
            0x63,
        /* SEQ */
            0x03, 0x01, 0x0F, 0x00, 0x0E,
        /* CRTC */
            0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
            0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
            0xFF,
        /* GC */
            0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
            0xFF,
        /* AC */
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x41, 0x00, 0x0F, 0x00,	0x00
    };


    write_vga_registers(g_320x200x256);

    return 1; // True as if reached here then all good 
}


void put_pixel_exact(u32 x, u32 y, u8 color_value){
    u8 *p = ((u8*)0xA0000) + 320 * y + x;
    //u8 *p = (get_frame_buffer_segment()) + 320 * y + x;
    *p = color_value; 
}

void put_pixel(u32 x, u32 y, u8 r, u8 g, u8 b){
    u8 color_value = (r * 6/256) * 36 + (g * 6/256) + (b * 6/256);
    put_pixel_exact(x, y, color_value);
}


int supports_mode(u32 width, u32 height, u32 color_depth){
    // Only Support One Mode 
    return width == 320 && height == 200 && color_depth == 8;
}


void write_vga_registers(u8 * registers){
    // Misc 1 
    port_byte_out(VGA_MISC_PORT, *(registers++));
    
    // SEQ 5
    for(u8 i = 0; i < 5; i++){
        port_byte_out(SEQUENCER_INDEX_PORT, i); // Set index 
        port_byte_out(SEQUENCER_DATA_PORT, *(registers++)); // Set Value 
    }

    // CRTC 25 
    // Need to unlock cathod before sending data 
    port_byte_out(CRTC_INDEX_PORT, 0x03);
    port_byte_out(CRTC_DATA_PORT, port_byte_in(CRTC_DATA_PORT) | 0x80); 
    port_byte_out(CRTC_INDEX_PORT, 0x11);
    port_byte_out(CRTC_DATA_PORT, port_byte_in(CRTC_DATA_PORT) & ~0x80); 

    registers[0x03] = registers[0x03] | 0x80; // Prevent locking 
    registers[0x11] = registers[0x11] | ~0x80;

    for(u8 i = 0; i < 25; i++){
        port_byte_out(CRTC_INDEX_PORT, i); // Set Index 
        port_byte_out(CRTC_DATA_PORT, *(registers++)); // Set Value
    }

    // GC 9
    for(u8 i = 0; i < 9; i++){
        port_byte_out(GRAPHICS_CONTROLLER_INDEX_PORT, i); // Set Index
        port_byte_out(GRAPHICS_CONTROLLER_DATA_PORT, *(registers++)); // Set Value
    }

    // AC 21 
    for(u8 i = 0; i < 21; i++){
        port_byte_in(ATTRIBUTE_CONTROLLER_RESET_PORT); // Reset before send data. Reading triggers a reset 
        port_byte_out(ATTRIBUTE_CONTROLLER_INDEX_PORT, i); // Set Index 
        port_byte_out(ATTRIBUTE_CONTROLLER_WRITE_PORT, *(registers++)); // Set Value
    }

    port_byte_in(ATTRIBUTE_CONTROLLER_RESET_PORT); // Reset again 
    port_byte_out(ATTRIBUTE_CONTROLLER_INDEX_PORT, 0x20);
}


u8* get_preset_frame_buffer_segment(){
    // Check if set 
    if(frame_buffer_segment == UNSET){
        frame_buffer_segment = get_frame_buffer_segment();
    }

    return frame_buffer_segment;
}


u8* get_frame_buffer_segment(){
    port_byte_out(GRAPHICS_CONTROLLER_INDEX_PORT, 0x06);
    u8 seg_number = ((port_byte_in(GRAPHICS_CONTROLLER_DATA_PORT) >> 2) & 0x03);

    switch(seg_number){
        default:
        case 0: return (u8*)0x00000;
        case 1: return (u8*)0xA0000;
        case 2: return (u8*)0xB0000;
        case 3: return (u8*)0xB8000;
    }
}