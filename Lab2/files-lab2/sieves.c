#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6

char column_count = 0;

void print_number(int n) {
  column_count++;
  printf("%10d ", n);
  if (column_count == COLUMNS) {
    printf("\n");
    column_count = 0;
  }
}

void print_sieves(int n){
  // init bool array with value true, 2 up to n (indicies are -2 of the number)
  bool prime_list[n];
  for (int i = 0; i < n; i++) {
    prime_list[i] = true;
  }
  // algoritm Sieve of Eratosthenes
  for (int i = 2; i <= sqrt(n); i++) {
    if (prime_list[i - 2]) {
      for (int j = i * i; j <= n; j += i) {
        prime_list[j - 2] = false;
      }
    }
  }
  // print primes up to n
  for (int i = 2; i <= n; i++) {
    if (prime_list[i - 2]) {
      print_number(i);
    }
  }
}

int main(int argc, char *argv[]){
  clock_t begin = clock();

  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time: %.10f s\n", time_spent);
  return 0;
}

// within 2 seconds:  n = 770 000
// within 10 seconds: n = ~2 044 000 more gives
//                        segmentation fault (out of memory on stack)
