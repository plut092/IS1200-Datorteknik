#include "stdio.h"
/*
Written by Johan Engström
2019-01-23

The program extracts bits from x and y and stores them to z.
17:13 from variable x to 5:0 in z
3:0 from y to 7:5 in z
Expected result with default input is
0000 0000 0000 0000 0000 0000 1111 1111 or
0x000000ff
*/
void bitExtract(int *x, int *y, int *z){
  *z=((*z & 0xFFFFFF00)|((*x>>13)&0x0000001F)|((*y<<5)&0x000000E0));
}

int main() {
  int x = 0x0003E000; //0000 0000 0000 0011 1110 0000 0000 0000
  int y = 0x00000007; //0000 0000 0000 0000 0000 0000 0000 0111
  int z = 0;          //0000 0000 0000 0000 0000 0000 0000 0000

  printf("%#010x\n", z );
  bitExtract(&x, &y, &z);
  printf("%#010x\n", z );

  return 0;
}
