#include "mem.h"

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

// Next point in memory to allocate from
u32 free_mem_addr = 0x1000000;

u32 malloc(u32 size) {

    /*
     * Alignment function. If our current free address is not a multiple of our chosen
     * block size (0x1000), then round up to the next block.
     */
    if (free_mem_addr & 0xFFFFF000) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }

    // Allocate the requester to the current free address.
    u32 ret = free_mem_addr;

    // Increment the free pointer by the size, so that the memory will not be overwritten.
    free_mem_addr += size;

    // Return the allocated start address
    return ret;
}

u32 calloc(u32 size) {
    // Allocate memory
    u32 ret = malloc(size);

    // Set memory to 0
    memory_set( (u8 *) ret, 0, size);
    return ret;
}

