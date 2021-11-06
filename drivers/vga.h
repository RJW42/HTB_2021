#ifndef VGA_H_
#define VGA_H_
#include "../cpu/types.h"

int set_vga_mode(u32 width, u32 height, u32 color_depth);

void put_pixel_exact(u32 x, u32 y, u8 color_value);
void put_pixel(u32 x, u32 y, u8 r, u8 g, u8 b);

void put_buffer_exact(u32 x, u32 y, u8 color_value);
void flush_buffer();

#endif