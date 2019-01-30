#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define COLUMNS 6

char column_count = 0;  // cc =

void print_number(int n) {
  column_count++; // cc = column count
  printf("%10d ", n);
  if (column_count == COLUMNS) {
    printf("\n");
    column_count = 0;
  }
}

void print_sieves(int n){
  // init bool array (true). index = number
  bool prime_list[n];
  prime_list[0] = false;
  prime_list[1] = false;

  for (int i = 2; i <= n; i++) {
    prime_list[i] = true;
  }
  // algoritm Sieve of Eratosthenes
  for (int i = 2; i <= sqrt(n); i++) {
    if (prime_list[i]) {
      for (int j = i * i; j <= n; j += i) {
        prime_list[j] = false;
      }
    }
  }
  // print primes up to n
  for (int i = 2; i <= n; i++) {
    if (prime_list[i]) {
      print_number(i);
    }
  }
}

int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");

  return 0;
}
