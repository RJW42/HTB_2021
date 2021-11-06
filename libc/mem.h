#ifndef MEM_H_
#define MEM_H_

#include "../cpu/types.h"

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(u8 *dest, u8 val, u32 len);
u32 malloc(u32 size);
u32 calloc(u32 size);

#endif