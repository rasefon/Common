#ifndef _BITSET_H_
#define _BITSET_H_

#include <stdbool.h>

typedef unsigned short  tUshort;
typedef unsigned char   tUchar;

#define _BITSET_BITS_PER_CELL     16
// index of bits, for example, index of '20' is bits[1].  
#define _BITSET_BITS_INDEX(x)     ((unsigned)(x) >> 4) 
// offset of bits, for example, offset of '20' is 4 (same as x % 16) 
#define _BITSET_BITS_OFFSET(x)    ((x) & 0x0f) 
#define _BITSET_DEF_CELL_NUM      16 // 16 * 2 bytes -> 0~255 (256 bits)
#define _BITSET_DEF_BYTE_NUM      (_BITSET_DEF_CELL_NUM * sizeof(tUshort))
#define _BITSET_DEF_BITS_NUM      (_BITSET_DEF_CELL_NUM * _BITSET_BITS_PER_CELL)
// test result for 2 bitsets.
#define _BITSET_EQUAL      0
#define _BITSET_DISJOINT   1
#define _BITSET_INTERSECT  2

typedef struct _bitset_
{
   //tUshort  cell_num;
   //tUshort  bits_num;
   //tUshort  bytes_num;
   tUshort  bits[_BITSET_DEF_CELL_NUM];
} BITSET;

//==========================functions declaration=================================
extern BITSET* new_bitset();

extern BITSET* dup_bitset(BITSET*);

extern void free_bitset();

//Resets bits to zero.
extern void reset_bitset();

//Returns the number of bits in the bitset that are set.
extern int bitset_count(BITSET*);

//Returns whether any of the bits is set.
extern bool bitset_any(BITSET*);

//Returns whether none of the bits is set.
extern bool bitset_none(BITSET*);

extern bool bitset_contains(BITSET*, tUshort);

extern void bitset_add(BITSET*, tUshort);

extern void bitset_remove(BITSET*, tUshort);

extern void bitset_flip(BITSET*);

extern bool bitset_is_subset(BITSET *pbs, BITSET *p_sub_bs);

extern void bitset_union(BITSET *pbs_a, BITSET *pbs_b, BITSET **ppbs_out);

extern void bitset_intersect(BITSET *pbs_a, BITSET *pbs_b, BITSET **ppbs_out);

extern void bitset_assign(BITSET *pbs_dest, BITSET *pbs_src);

extern int bitset_test(BITSET *pa, BITSET *pb);
//================================================================================

//==========================useful macros=========================================
#define BITSET_IS_EQUAL(a,b)        (_BITSET_EQUAL == bitset_test(a,b))
#define BITSET_IS_DISJOINT(a,b)     (_BITSET_DISJOINT == bitset_test(a,b))
#define BITSET_IS_INTERSECT(a,b)    (_BITSET_INTERSECT == bitset_test(a,b))
//================================================================================

#endif
