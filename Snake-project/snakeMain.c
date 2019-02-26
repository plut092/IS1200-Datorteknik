#include <stdio.h>
#include <stdlib.h>
#include "snakeHeader.h"


typedef struct Snake_segments {
  int x;
  int y;
  struct Snake_segments * next;
}snake_segment;

int main(int argc, char const *argv[]) {

  snake_segment * head = NULL;
  head = malloc(sizeof(snake_segment));
  if (head == NULL) {
    return -1;
  }
/*
  head->x = 2;
  head->y = 1;
  head->next = malloc(sizeof(snake_segment));
  head->next->x = 2;
  head->next->y = 2;
  head->next->next = NULL;

  add_snake_segment(&head, 1, 1);
  add_snake_segment(&head, 0, 1);

  printf("Before remove_last_snake_segment\n");
  print_list(head);

  remove_last_snake_segment(head);

  printf("After remove_last_snake_segment\n");

  print_list(head);
*/

  return 0;
}
