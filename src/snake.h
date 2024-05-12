#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "pixel.h"

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} DIRECTION;

typedef struct SnakeNode {
    Pixel pixel;
    DIRECTION direction;
    struct SnakeNode *next;
    struct SnakeNode *prev;
} SnakeNode;

typedef struct {
    bool is_growing;
    SnakeNode *head;
    SnakeNode *tail;
} Snake;


Snake* initialize_snake(Pixel initial_position, DIRECTION initial_direction, int length);
void free_snake(Snake* snake);
void snake_move_in_current_direction(Snake* snake);
void snake_change_direction(Snake* snake, DIRECTION new_direction);
void snake_grow(Snake* snake);

#endif //SNAKE_H
