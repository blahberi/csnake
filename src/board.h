#ifndef BOARD_H
#define BOARD_H

#include "snake.h"

typedef struct {
    int width;
    int height;
    Pixel food;
    Snake snake;
} Board;

#endif //BOARD_H
