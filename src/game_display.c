#include "game_display.h"
#include "game.h"
#include "display.h"
#include "assets.h"


#define CASE(NAME) case NAME: drawBlock(i, j, IMG_##NAME); break;

void drawBoard(void) {
    clear();
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++) {
            switch (gameState.board[i][j]) {
                CASE(CST)
                CASE(GK)
                CASE(CAGE)
                CASE(GK_IN_CAGE)
                CASE(CST_ON_CAGE)
                CASE(TREE)
            }
        }
}