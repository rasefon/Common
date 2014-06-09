#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdbool.h>

typedef unsigned short  tUshort;
typedef unsigned char   tUchar;

#define _BITS_PER_CELL   16
#define _BITS_INDEX(x)     ((unsigned)(x) >> 4) // index of bits, for example, index of '20' is bits[1].  
#define _BITS_OFFSET(x)    ((x) & 0x0f) // offset of bits, for example, offset of '20' is 4 (same as x % 16) 
#define _DEF_CELL_NUM    16 // 16 * 2 bytes -> 0~255 (256 bits)
#define _DEF_BITS_NUM    (_DEF_CELL_NUM * _BITS_PER_CELL)

typedef struct _bitmap_
{
   tUshort  cell_num;
   tUshort  bits_num;
   tUchar   *pBits;
   tUchar   bits[_DEF_CELL_NUM];
} BITMAP;

extern BITMAP* new_bitmap();

#endif
