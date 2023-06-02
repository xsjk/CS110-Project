#include "game.h"
#include "assets.h"
#include "string.h"

GameState gameState;

#define CASE(LEVEL, BOXES) if (level == LEVEL && boxes == BOXES) gameState = gameLevel##LEVEL##_##BOXES;

void gameInitialize(uint8_t level, uint8_t boxes) {
    CASE(1, 1)
    CASE(1, 2)
    CASE(1, 3)
    CASE(2, 1)
    CASE(2, 2)
    CASE(2, 3)
    CASE(3, 1)
    CASE(3, 2)
    CASE(3, 3)
}

// deal with different cst move scenario
void moveCST(uint8_t nextRow, uint8_t nextCol, bool nextPosIsCAGE) {
    gameState.board[nextRow][nextCol] = nextPosIsCAGE ? CST_ON_CAGE : CST;
    gameState.step++;
    gameState.board[gameState.cstRow][gameState.cstCol] = gameState.board[gameState.cstRow][gameState.cstCol] == CST_ON_CAGE ? CAGE : BLANK;
    gameState.cstRow = nextRow;
    gameState.cstCol = nextCol;
}

// return 1 if win otherwise 0
bool checkWin(void) {
    for (uint8_t row = 0; row < BOARD_HEIGHT; row++)
        for (uint8_t col = 0; col < BOARD_WIDTH; col++)
            if (gameState.board[row][col] == GK)
                return false;
    return true;
}

bool gameMoveCST(Action action) {
    uint8_t cstNextRow = action == UP ? gameState.cstRow - 1 : action == DOWN ? gameState.cstRow + 1 : gameState.cstRow,
            cstNextCol = action == LEFT ? gameState.cstCol - 1 : action == RIGHT ? gameState.cstCol + 1 : gameState.cstCol;
    if (gameState.board[cstNextRow][cstNextCol] == TREE)
        return false;
    if (gameState.board[cstNextRow][cstNextCol] == BLANK) {
        moveCST(cstNextRow, cstNextCol, false);
        return false;
    }
    if (gameState.board[cstNextRow][cstNextCol] == CAGE) {
        moveCST(cstNextRow, cstNextCol, true);
        return false;
    }
    if (gameState.board[cstNextRow][cstNextCol] == GK || gameState.board[cstNextRow][cstNextCol] == GK_IN_CAGE) {
        bool nextPosIsCAGE = gameState.board[cstNextRow][cstNextCol] == GK_IN_CAGE;
        uint8_t cstNextNextRow = 2 * cstNextRow - gameState.cstRow,
                cstNextNextCol = 2 * cstNextCol - gameState.cstCol;
        if (gameState.board[cstNextNextRow][cstNextNextCol] == GK || gameState.board[cstNextNextRow][cstNextNextCol] == GK_IN_CAGE || gameState.board[cstNextNextRow][cstNextNextCol] == TREE)
            return false;
        if (gameState.board[cstNextNextRow][cstNextNextCol] == BLANK) {
            gameState.board[cstNextNextRow][cstNextNextCol] = GK;
            moveCST(cstNextRow, cstNextCol, nextPosIsCAGE);
            return false;
        }
        else if (gameState.board[cstNextNextRow][cstNextNextCol] == CAGE) {
            gameState.board[cstNextNextRow][cstNextNextCol] = GK_IN_CAGE;
            moveCST(cstNextRow, cstNextCol, nextPosIsCAGE);
            return nextPosIsCAGE ? false : checkWin();
        }
    }
}