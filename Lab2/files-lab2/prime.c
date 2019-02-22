/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <math.h>

int is_prime(int n){
  if (n < 2) { // if n is less than 2 it's not prime (return 0)
    return 0;
  }
  for (int i = 2; i <= sqrt(n); i++) {
    if (n%i == 0) { // if remainder (n%i) then i is not a factor
      return 0;
    }
  }
  return 1; // if no number i up to sqrt(n) is a factor n is prime
}

int main(void){
  printf("%d\n", is_prime(2));  // 1 is a prime.      Should print 1.
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(25)); // 987 is not a prime. Should print 0.
}
