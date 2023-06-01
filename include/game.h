#pragma once

#include <stdint.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 20

typedef enum {BLANK, CST, GK, CAGE, GK_IN_CAGE, TREE} TileType;

typedef TileType Board[BOARD_HEIGHT][BOARD_WIDTH];

extern Board board;