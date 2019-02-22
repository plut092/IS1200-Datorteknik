/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
int cc_print_number = 0;  //column count global variable for print_number()

int is_prime(int n){
  if (n < 2) { // if n is less than 2 it's not prime (return 0)
    return 0;
  }
  for (int i = 2; i <= sqrt(n); i++) {
    if ((n % i) == 0) { // if remainder (n%i) then i is not a factor
      return 0;
    }
  }
  return 1; // if no number i up to sqrt(n) is a factor n is prime
}

void print_number(int n) {
  cc_print_number++; // cc = column count
  printf("%10d ", n);
  if (cc_print_number == COLUMNS) {
    printf("\n");
    cc_print_number = 0;
  }
}

void print_primes(int n){
  // Should print out all prime numbers up to 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  for (int i = 2; i <= n; i++) {
    if (is_prime(i)) { // printing i = 2 up to n if they are prime
      print_number(i);
    }
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");

  return 0;
}
