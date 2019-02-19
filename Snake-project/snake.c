#include <stdlib.h>
#include <stdio.h>


typedef struct Snake_segments {
  int x;
  int y;
  struct Snake_segments * next;
} snake_segment;

void print_list(snake_segment * head) {
  snake_segment * current = head;

  while (current != NULL) {
    printf("%d\t%d\n", current->x, current->y);
    current = current->next;
  }
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

int main(int argc, char const *argv[]) {

  snake_segment * head = NULL;
  head = malloc(sizeof(snake_segment));
  if (head == NULL) {
    return -1;
  }

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



  return 0;
}
