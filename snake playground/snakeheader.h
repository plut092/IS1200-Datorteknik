typedef struct Snake_segments {
  int x;
  int y;
  struct Snake_segments * next;
} snake_segment;

void print_list(snake_segment * head);
void add_snake_segment(snake_segment ** head, int x, int y);
void remove_last_snake_segment(snake_segment * head);
snake_segment * init_snake_segment();
