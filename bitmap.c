#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitmap.h"


#define _INIT_STRUCT(p,type)  p = (type*)malloc(sizeof(type));\
                              if (!p) { \
                                 fprintf(stderr, "Can't allocate memory.\n"); \
                                 exit(EXIT_FAILURE); \
                              } \
                              memset(p,0,sizeof(type));\

BITMAP* new_bitmap()
{
   BITMAP *pBitmap = (BITMAP*)malloc(sizeof(BITMAP));
   _INIT_STRUCT(pBitmap, BITMAP);
   pBitmap->cell_num = _DEF_CELL_NUM;
   pBitmap->bits_num = _DEF_BITS_NUM;
   pBitmap->pBits = pBitmap->bits;
}

void free_bitmap(BITMAP* pBitmap)
{
   if (pBitmap) {
      if (pBitmap->pBits != pBitmap->bits) {
         free(pBitmap->pBits);
      }
      free(pBitmap);
   }
}

BITMAP *dup_bitmap(BITMAP *pBm)
{
   BITMAP* pNew_bm;
   _INIT_STRUCT(pNew_bm, BITMAP);
   pNew_bm->cell_num = pBm->cell_num;
   pNew_bm->bits_num = pBm->bits_num;

   if (pBm->pBits == pBm->bits) {
      pNew_bm->pBits = pNew_bm->bits;
      memcpy(pNew_bm->pBits, pBm->pBits, _DEF_CELL_NUM*sizeof(tUshort));
   }
   else {
      pNew_bm->pBits = (tUchar*)malloc(pBm->cell_num*sizeof(tUshort));
      if (!pNew_bm) {
         fprintf(stderr, "Can't allocate memory.\n");
         exit(EXIT_FAILURE);
      }
      else {
         memcpy(pNew_bm->bits, pBm->bits, pBm->bits_num);
      }
   }
   return pNew_bm;
}

