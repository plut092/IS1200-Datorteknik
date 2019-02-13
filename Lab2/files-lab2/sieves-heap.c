#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6
#define TRUE 0
#define FALSE 1

char column_count = 0;

void print_number(int n) {
  column_count++;
  printf("%10d ", n);
  if (column_count == COLUMNS) {
    printf("\n");
    column_count = 0;
  }
}

bool *make_prime_list (int n) {
  // init heap
  bool *prime_list = (bool *) calloc(n, sizeof(bool));

  // algoritm Sieve of Eratosthenes - indicies are -2 of the number
  for (int i = 2; i <= sqrt(n); i++) {
    if (prime_list[i - 2] == TRUE) {
      for (int j = i * i; j <= n; j += i) {
        prime_list[j - 2] = FALSE;
      }
    }
  }
  return prime_list;
}

void mean_sieves (int n) {
  bool *mean_prime_list = make_prime_list(n);
  int number_of_primes = 0;
  double prime_sum = 0;
  double prime_mean = 0;

  printf("\n");
  for (int i = 0; i < n - 1; i++) {
    if (mean_prime_list[i] == TRUE) {
      prime_sum += i + 2;
      number_of_primes++;
    }
  }
  prime_mean = prime_sum / number_of_primes;

  printf("\n\nMean value of  all primes from 1 to N: %f\n", prime_mean);
  free(mean_prime_list);
}

/*
  Init bool heap "prime_list" with value TRUE (#define: TRUE = 0 and FALSE = 1).
  Since malloc would need init with a for-loop to set every value to true
  calloc was used since it's setting values of prime_list to 0 directly.
  2 up to n gives indicies -2 of the number.
*/
void print_sieves(int n){
  // init heap
    bool *prime_list_pointer = make_prime_list(n);

  // print primes up to n
  for (int i = 2; i <= n; i++) {
    if (prime_list_pointer[i - 2] == TRUE) { // if value in prime_list[i] is false the i is prime
      print_number(i);
    }
  }
  free(prime_list_pointer); // free heap memory to avoid memory leaks
}

int main(int argc, char *argv[]){
  // start program timer for time_spent executing program
  clock_t begin = clock();
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");

  // getting mean value of prime up to n
  mean_sieves(atoi(argv[1]));

    // calculating and printing time_spent on execution of program
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nExecution time: %.10f s\n", time_spent);

  return 0;
}

// within 2 seconds:  n =    770 000
// within 10 seconds: n =  2 044 000 (segmentation fault (out of memory on stack))
// within 2 seconds:  n =  4 200 000
// within 10 seconds: n = 21 500 000
