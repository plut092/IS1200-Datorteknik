/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/
#include <stdint.h>
#include <stdio.h>   /* Declarations of uint_32 and the like */
#include <windows.h>
/*
*
* Created on February 27, 2019, 10:08 AM
*/

/*
*
*/
#define DIR_NULL    4 // directon null
#define UP          0
#define RIGHT       1
#define DOWN        2
#define LEFT        3

int column = 0;
int direction = UP;
volatile int row = 1;
volatile int col = 1;
uint8_t pixel[32][128];
uint8_t snakearray[32][128];


void snake_remove_tail() {
  int row_current = row;  // 1
  int col_current = col;  // 4
  int row_next = row_current;
  int col_next = col_current;
  int has_not_removed = 1;


  if (snakearray[row_current][col_current] == DIR_NULL) { // 3
    return; // head = tail
  }
  while (has_not_removed) {
    if (snakearray[row_current][col_current] == UP) {
      row_next = row_current - 1;
    }
    if (snakearray[row_current][col_current] == RIGHT) {
      col_next = col_current + 1;
    }
    if (snakearray[row_current][col_current] == DOWN) {
      row_next = row_current + 1;
    }
    if (snakearray[row_current][col_current] == LEFT) { // 1,3=3
      col_next = col_current - 1; // 3 // 2
    }
    if (snakearray[row_next][col_next] == DIR_NULL) { // 1,3=3 false // 1,2=4
      snakearray[row_current][col_current] = DIR_NULL; // new tail
      pixel[row_next][col_next] = 0;
      has_not_removed = 0;
    }
    else {
      row_current = row_next; // 1
      col_current = col_next; // 3
    }
  }
}

void snake_move() {
  if (direction == UP) {
    row--;
  }
  if (direction == RIGHT) {
    col++;
  }
  if (direction == DOWN) {
    row++;
  }
  if (direction == LEFT) {
    col--;
  }
  pixel[row][col] = 1;
  snakearray[row][col] = ((direction + 2) % 4); // opposite direction to find last pixel
  snake_remove_tail();
}

void snake_eat() {
  if (direction == UP) {
    row--;
  }
  if (direction == RIGHT) {
    col++;
  }
  if (direction == DOWN) {
    row++;
  }
  if (direction == LEFT) {
    col--;
  }
  pixel[row][col] = 1;
  snakearray[row][col] = ((direction + 2) % 4); // opposite direction to find last pixel
}

void print_list(uint8_t list[32][128]) {
  printf("\n\n");
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 128; j++) {
      column++;

      if ((j % 8) == 0) {
        printf(" ");
      }
      printf("%d", list[i][j]);
      if (column == 128) {
        printf("\n");
        column = 0;
      }
    }
  }
}

void testrun() {
  printf("pixel1");
  print_list(pixel);
  // printf("snakearray1");
  // print_list(snakearray);

  direction = RIGHT;
  snake_eat();

  printf("pixel2");
  print_list(pixel);
  // printf("snakearray2");
  // print_list(snakearray);

  direction = RIGHT;
  snake_eat();

  printf("pixel3");
  print_list(pixel);
  // printf("snakearray3");
  // print_list(snakearray);


  snake_move();

  printf("pixel4");
  print_list(pixel);
  // printf("snakearray4");
  // print_list(snakearray);

  direction = DOWN;
  snake_eat();

  printf("pixel5");
  print_list(pixel);
  // printf("snakearray5");
  // print_list(snakearray);


  snake_move();

  printf("pixel6");
  print_list(pixel);
  // printf("snakearray6");
  // print_list(snakearray);

  snake_move();

  printf("pixel7");
  print_list(pixel);
  printf("snakearray7");
  print_list(snakearray);
}

int random(int min, int max) {
  int random_seed;
  int random_result;
  int random_time = 30918;
  int random_memory_address;
  random_seed = random_time ^ random_memory_address;
  random_result = (random_seed % (max - min) + 1);
  return random_result;
}

int main(int argc, char** argv) {

  printf("pluto random: %d\n", random(1,1000));
  printf("pluto random: %d\n", random(1,1000));
  /*  for (int i = 0; i < 32; i++) {
  for (int j = 0; j < 128; j++) {
  pixel[i][j] = 0;
  snakearray[i][j] = 4;
}
}
pixel[row][col] = 1;

// testrun();

int res = 31;

if(++res < 0) { // modulo with negative number gave -1 != 31
printf("Res = %d\n", res);
res = res + 1;
}
else {
printf("Res = %d\n", res);
res++;
}
printf("Res = %d\n", res);
*/
return 0;
}
