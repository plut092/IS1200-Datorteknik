#include <stdlib.h>
#include <stdio.h>
#include "snakeheader.h"


void print_list(snake_segment * head) {
  snake_segment * current = head;

  while (current != NULL) {
    printf("%d\t%d\n", current->x, current->y);
    current = current->next;
  }
}

snake_segment * init_snake_segment() {
  snake_segment * new_snake_segment = NULL;
  new_snake_segment = malloc(sizeof(snake_segment));
  if (new_snake_segment == NULL) {
    return 0;
  }

  new_snake_segment->x = 0;
  new_snake_segment->y = 0;
  new_snake_segment->next = NULL;
  return new_snake_segment;
}

void add_snake_segment(snake_segment ** head, int x, int y) {
  snake_segment * new_snake_segment;
  new_snake_segment = malloc(sizeof(snake_segment));

  new_snake_segment->x = x;
  new_snake_segment->y = y;
  new_snake_segment->next = *head;
  *head = new_snake_segment;
}

void remove_last_snake_segment(snake_segment * head) {
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        free(head);
    }

    /* get to the second to last node in the list */
    snake_segment * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    free(current->next);
    current->next = NULL;
}
