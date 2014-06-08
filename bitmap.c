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

// for testing.
int main(int argc, char** argv)
{
   BITMAP *p = new_bitmap();
   return 1;
}
