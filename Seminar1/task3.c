#include "stdio.h"
/*
Written by Johan Engström.
*/

void adder(const int *x, const int *y, int *z){
  *z = *x + *y;
}

int foo(int a){
  const int k = 10;
  return a + k;
}

int main(int argc, char const *argv[]) {
  int a = 4;
  int b = 6;
  int c = 0;
  int d = 7;

  adder(&a, &b, &c);
  printf("%d + %d = %d\n", a, b, c);

  printf("%d + 10 = %d\n", d, foo(d));

  return 0;
}
