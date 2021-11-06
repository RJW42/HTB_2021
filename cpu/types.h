#ifndef TYPES_H_
#define TYPES_H_

/* Instead of using unsiged chars shorts exct 
 * Use custom defined types */

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;

typedef char bool;
enum {false, true}; 

#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

#endif