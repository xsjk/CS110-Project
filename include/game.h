#pragma once

#include <stdint.h>
#include <stdbool.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 20

typedef enum {BLANK, CST, GK, CAGE, GK_IN_CAGE, CST_ON_CAGE, TREE} TileType;
typedef TileType Board[BOARD_HEIGHT][BOARD_WIDTH];
typedef struct {
    uint8_t cstRow, cstCol, step;
    Board board;
} GameState;
typedef enum {UP, DOWN, LEFT, RIGHT} Action;

extern GameState gameState;

// initialize the game with the given level
void gameInitialize(uint8_t level);

// move cst and change the gameState,
// returns 1 if the game is over, 0 otherwise
bool gameMoveCST(Action action);