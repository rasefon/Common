#include <stdio.h>
#include "bitset.h"
// for testing.
int main(int argc, char** argv)
{
   BITSET *p = new_bitset();
   printf("%d\n", p->cell_num);
   return 1;
}

