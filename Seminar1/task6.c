#include "stdio.h"
/*
Written by Johan Engström.
2019-01-23

Given two floating point arrays x and y of length len, square the numbers
in the x array and store the value in reverse order in array y.
The function must not return any value-
*/

void square_reverse(double *x, double *y, int len){
  int i = 0;
  while(len >= 0){
    len--;
    y[len] = x[i] * x[i];
    i++;
  }
}

int main() {
  double in[] = {11.0, 20.0, 100.0};
  double out[3];

  square_reverse(in, out, 3);
  printf("out[0] = %.1f\tout[1] = %.1f\tout[2] = %.1f\n", out[0], out[1], out[2]);
  return 0;
}
