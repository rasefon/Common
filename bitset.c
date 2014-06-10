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
                              memset(p,0,sizeof(type));\
                              p->pBits = p->bits;

BITSET* new_bitset()
{
   BITSET *pbs = (BITSET*)malloc(sizeof(BITSET));
   _INIT_STRUCT(pbs, BITSET);
   pbs->inverse = false;
   pbs->cell_num = _DEF_CELL_NUM;
   pbs->bits_num = _DEF_BITS_NUM;
}

void free_bitset(BITSET* pbs)
{
   if (pbs) {
      free(pbs);
   }
}

BITSET* dup_bitset(BITSET *pbs)
{
   assert(pbs->pBits == pbs->bits);

   BITSET* p_new_bs;
   _INIT_STRUCT(p_new_bs, BITSET);
   p_new_bs->inverse = pbs->inverse;
   p_new_bs->cell_num = pbs->cell_num;
   p_new_bs->bits_num = pbs->bits_num;
   memcpy(p_new_bs->pBits, pbs->pBits, _DEF_BYTE_NUM);

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
   tUchar *p = (tUchar*)pbs->pBits;
   // original width of per cell is 2 bytes, now because i use only 1 byte pointer, I must engarge up
   // bound of iteration.
   int up_bound = pbs->cell_num << 1;
   for(int i = 0; i < up_bound; ++i) {
      count += bits_per_char[*p++];
   }
   
   return pbs->inverse ? 256-count : count;
}

void reset_bitset(BITSET *pbs)
{
   assert(pbs->pBits == pbs->bits);
   memset(pbs->pBits, 0, _DEF_BYTE_NUM);
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

   return pbs->inverse ? !any : any;
}

bool bitset_none(BITSET* pbs)
{
   return !bitset_any(pbs);
}
