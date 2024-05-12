#include "snake.h"
#include <stdio.h>
#include "memory_allocator/memory_allocator.h"
#include <stdlib.h>

static DIRECTION opposite_direction(DIRECTION direction) {
    switch (direction) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
    }
}

static SnakeNode* add_new_node(Snake* snake, Pixel pixel, DIRECTION direction) {
    SnakeNode* new_head = malloc(sizeof(SnakeNode));
    new_head->pixel = pixel;
    new_head->direction = direction;
    new_head->next = snake->head;
    new_head->prev = NULL;
    if (snake->head) {
        snake->head->prev = new_head;
    }
    snake->head = new_head;
    if (!(int)snake->tail) {
        snake->tail = new_head;
    }
    return new_head;
}

static void remove_tail(Snake* snake) {
    if (!(int)snake->tail) {
        return;
    }
    SnakeNode* old_tail = snake->tail;
    snake->tail = old_tail->prev;
    if (snake->tail) {
        snake->tail->next = NULL;
    }
    free(old_tail);
}

static void update_pixel_position(Pixel* pixel, const DIRECTION direction, const int amount) {
    switch (direction) {
        case UP:
            pixel->y -= amount;
            break;
        case DOWN:
            pixel->y += amount;
            break;
        case LEFT:
            pixel->x -= amount;
            break;
        case RIGHT:
            pixel->x += amount;
            break;
    }
}

static bool is_equal_pixels(Pixel pixel1, Pixel pixel2){
    return pixel1.x == pixel2.x && pixel1.y == pixel2.y;
}

Snake* initialize_snake(const Pixel initial_position, const DIRECTION initial_direction, const int length) {
    Snake* snake = malloc_track_global(sizeof(Snake));

    Pixel head_position = initial_position;
    Pixel tail_position = initial_position;
    update_pixel_position(&tail_position, opposite_direction(initial_direction), length);

    add_new_node(snake, tail_position, opposite_direction(initial_direction));
    add_new_node(snake, head_position, initial_direction);

    snake->is_growing = false;
    return snake;
}

void free_snake(const Snake* snake) {
    SnakeNode* current = snake->head;
    while (current) {
        SnakeNode* next = current->next;
        free(current);
        current = next;
    }
}

void snake_move_in_current_direction(Snake* snake) {
    update_pixel_position(&snake->head->pixel, snake->head->direction, 1);
    if (snake->is_growing){
        return;
    }
    update_pixel_position(&snake->tail->pixel, snake->tail->direction, 1);
    if (is_equal_pixels(snake->tail->pixel, snake->tail->prev->pixel)){
        remove_tail(snake);
    }
}

void snake_change_direction(Snake* snake, const DIRECTION new_direction) {
    if (opposite_direction(snake->head->direction) == new_direction) {
        return;
    }
    if (snake->head->direction == new_direction) {
        return;
    }
    snake->head->direction = new_direction;
    add_new_node(snake, snake->head->pixel, new_direction);
}

void snake_grow(Snake* snake) {
    snake->is_growing = true;
}