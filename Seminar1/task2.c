#include "stdio.h"
/*
Written by Johan Engström
The program extracts bits from x and y to z.
17:13 from variable x to 5:0 in z
3:0 from y to 7:5 in z
Expected result 0000 0000 0000 0000 0000 0000 1111 1111 or
0x000000ff
(with the commented x and y value the result expected is
0000 0000 0000 0000 0000 0000 1010 1010 or 0x000000AA)
*/
void bitExtract(int *x, int *y, int *z){
  *z=((*z & 0xFFFFFF00)|((*x>>13)&0x0000001F)|((*y<<5)&0x000000E0));
}

int main() {
  //int x = 0x00014000;
  //int y = 0x00000005;
  int x = 0x0003E000; //0000 0000 0000 0011 1110 0000 0000 0000
  int y = 0x00000007; //0000 0000 0000 0000 0000 0000 0000 0111
  int z = 0;          //0000 0000 0000 0000 0000 0000 0000 0000

  printf("%#010x\n", z );
  bitExtract(&x, &y, &z);
  printf("%#010x\n", z );

  return 0;
}
