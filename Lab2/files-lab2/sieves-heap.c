#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6

char column_count = 0;  // cc =

void print_number(int n) {
  column_count++;
  printf("%10d ", n);
  if (column_count == COLUMNS) {
    printf("\n");
    column_count = 0;
  }
}

void print_sieves(int n, bool *prime_list){
  // init bool array (true)
  printf("%d\n", n); ///////////////////////////////////////
  // bool *prime_list = (bool *) malloc(n * sizeof(bool));
  printf("%d\n", sizeof(*prime_list)); /////////////////////
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
  // free(prime_list); /////////////////////////////////////////
}

int main(int argc, char *argv[]){
  printf("ARGUMENT: %s\n", argv[1]);

  clock_t begin = clock();


  if(argc == 2){
    bool *heap = (bool*) malloc(atoi(argv[1]) * sizeof(bool));
    print_sieves(atoi(argv[1]), heap);
    free(heap);
  }

  else
    printf("Please state an interger number.\n");
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time:\t%f\n", time_spent);
  return 0;
}
/* sieves:
within 2 seconds:  n = 770 000
within 10 seconds: n = ~2 044 000 more gives
                       segmentation fault (out of memory on stack)
sieves-heap:
within 2 seconds:  n =
within 10 seconds: n =
*/
