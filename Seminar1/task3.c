#include "stdio.h"
/*
Written by Johan Engström.
2019-01-23

Write the code for the incomplete functions adder() (that was empty)
and foo() (only containing const int k = 10;).
The function adder() is of the sort void and should take in three
int pointers (x, y, z) and add x and y values to z.

The function foo() has one parameter int a and should add
the constant k to a and return the value by using the function adder().
*/

void adder(const int *x, const int *y, int *z){
  *z = *x + *y;
}

int foo(int a){
  const int k = 10;
  int sum;
  adder(&a, &k, &sum);
  return sum;
}

int main() {
  int a = 4;
  int b = 6;
  int c = 0;
  int d = 7;

  adder(&a, &b, &c);
  printf("%d + %d = %d\n", a, b, c);

  printf("%d + 10 = %d\n", d, foo(d));

  return 0;
}
