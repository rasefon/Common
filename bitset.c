#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitset.h"


#define _INIT_STRUCT(p,type)  p = (type*)malloc(sizeof(type));\
                              if (!p) { \
                                 fprintf(stderr, "Can't allocate memory.\n"); \
                                 exit(EXIT_FAILURE); \
                              } \
                              memset(p,0,sizeof(type));

BITSET* new_bitset()
{
   BITSET *pbs = (BITSET*)malloc(sizeof(BITSET));
   _INIT_STRUCT(pbs, BITSET);
   pbs->bits_num = _DEF_BITS_NUM;
   pbs->cell_num = _DEF_CELL_NUM;
   pbs->bytes_num = _DEF_BYTE_NUM;

   return pbs;
}

void free_bitset(BITSET* pbs)
{
   if (pbs) {
      free(pbs);
   }
}

BITSET* dup_bitset(BITSET *pbs)
{
   assert(pbs);

   BITSET* p_new_bs;
   _INIT_STRUCT(p_new_bs, BITSET);
   p_new_bs->bits_num = pbs->bits_num;
   p_new_bs->cell_num = pbs->cell_num;
   p_new_bs->bytes_num = pbs->bytes_num;
   memcpy(p_new_bs->bits, pbs->bits, pbs->bytes_num);

   return p_new_bs;
}

int bitset_count(BITSET *pbs)
{
   static tUchar bits_per_char[] = {
      /*   0-15  */	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
      /*  16-31  */	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      /*  32-47  */	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      /*  48-63  */	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      /*  64-79  */	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      /*  80-95  */	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      /*  96-111 */	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      /* 112-127 */	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      /* 128-143 */	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      /* 144-159 */	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      /* 160-175 */	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      /* 176-191 */	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      /* 192-207 */	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      /* 208-223 */	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      /* 224-239 */	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      /* 240-255 */	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
   };
   
   int count = 0;
   tUchar *p = (tUchar*)pbs->bits;
   // original width of per cell is 2 bytes, now because i use only 1 byte pointer, I must engarge up
   // bound of iteration.
   int up_bound = pbs->cell_num << 1;
   for(int i = 0; i < up_bound; ++i) {
      count += bits_per_char[*p++];
   }
   
   return count;
}

void reset_bitset(BITSET *pbs)
{
   assert(pbs);
   memset(pbs->bits, 0, pbs->bytes_num);
}

bool bitset_any(BITSET* pbs)
{
   bool any = false;
   for (int i = 0; i < pbs->cell_num; ++i) {
      if(pbs->bits[i] && 0xffff) {
         any = true;
         break;
      }
   }

   return any;
}

bool bitset_none(BITSET* pbs)
{
   return !bitset_any(pbs);
}

bool bitset_test(BITSET *pbs, tUshort n)
{
   assert(pbs && n < pbs->bits_num);

   return pbs->bits[_BITS_INDEX(n)] & (1 << _BITS_OFFSET(n));
}

void bitset_add(BITSET *pbs, tUshort n)
{
   assert(pbs && n < pbs->bits_num);

   pbs->bits[_BITS_INDEX(n)] |= (1 << _BITS_OFFSET(n));
}

void bitset_remove(BITSET *pbs, tUshort n)
{
   assert(pbs && n < pbs->bits_num);

   pbs->bits[_BITS_INDEX(n)] &= ~(1 << _BITS_OFFSET(n));
}

void bitset_flip(BITSET* pbs)
{
   assert(pbs);
   
   for(int i = 0; i < pbs->cell_num; i++) {
      pbs->bits[i] = ~pbs->bits[i];
   }
}

bool bitset_is_subset(BITSET* pbs, BITSET* p_sub_bs)
{
   assert(pbs && p_sub_bs);

   int same_cell_num = pbs->cell_num;
   if (pbs->cell_num > p_sub_bs->cell_num) {
      same_cell_num = p_sub_bs->cell_num;
   }

   for(int i = 0; i < same_cell_num; ++i) {
      if ((pbs->bits[i] & p_sub_bs->bits[i]) != p_sub_bs->bits[i]) {
         return false;
      }
   }

   if (pbs->cell_num < p_sub_bs->cell_num) {
      int remained =  p_sub_bs->cell_num - pbs->cell_num;
      for (int i = 0; i < remained; ++i) {
         if (!p_sub_bs->bits[same_cell_num+i]) {
            return false;
         }
      }
   }

   return true;
}
