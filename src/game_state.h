#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "board.h"

typedef struct {
    int score;
    int game_over;
    Board board;
} GameState;

#endif //GAME_STATE_H
