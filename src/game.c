#include "game.h"
#include "string.h"

// initialize the game board to all BLANK
TileType board[BOARD_HEIGHT][BOARD_WIDTH];

void boardInitialise(void) {
    memset(board, BLANK, sizeof(board));
}