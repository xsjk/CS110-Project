#pragma once

#include <stdint.h>
#include <stdbool.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 20

typedef enum {CST, GK, CAGE, GK_IN_CAGE, CST_ON_CAGE, TREE, BLANK} TileType;
typedef TileType Board[BOARD_HEIGHT][BOARD_WIDTH];
typedef enum {UP, DOWN, LEFT, RIGHT, STOP} Action;
typedef struct {
    uint8_t cstRow, cstCol, step;
    Board board;
    Action lastAction;
} GameState;

extern GameState gameState;

/**
 * @brief initialize the game with the given level
 * @param level the level of the game
 * @param boxex the number of boxes
*/
void gameInitialize(uint8_t level, uint8_t boxes);

/**
 * @brief move cst and change the gameState
 * @param action the action to move
 * @return 1 if the game is over, 0 otherwise
*/
bool gameMoveCST(Action action);

/**
 * @brief move gk and change the gameState
 * @param action the action to move
*/
void gameMoveGK(Action action);