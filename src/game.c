#include "game.h"
#include "assets.h"
#include "string.h"

GameState gameState;

void gameInitialize(uint8_t level) {
    // initialize the game board
    if (level == 1) {
        gameState = gameLevel1;
    }
}

bool gameMoveCST(Action action) {
    uint8_t cstNextRow = action == UP ? gameState.cstRow - 1 : action == DOWN ? gameState.cstRow + 1 : gameState.cstRow,
            cstNextCol = action == LEFT ? gameState.cstCol - 1 : action == RIGHT ? gameState.cstCol + 1 : gameState.cstCol;
    if (gameState.board[cstNextRow][cstNextCol] == TREE)
        return FALSE;
}