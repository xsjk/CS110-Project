#include "game_display.h"
#include "game.h"
#include "display.h"
#include "assets.h"
#include "defines.h"
#include "systick.h"

PushAnimationData pushAnimationData;

#define CASE(NAME) case NAME: drawBlock(i, j, IMG_##NAME); break;

void drawBoard(void) {
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++) {
            switch (gameState.board[i][j]) {
                CASE(CST)
                CASE(GK)
                CASE(CAGE)
                CASE(GK_IN_CAGE)
                CASE(CST_ON_CAGE)
                CASE(TREE)
                case BLANK: break;
            }
        }
}

#undef CASE

void displayWelcome(void) {
    clear();
    drawString(60, 25, "Welcome!", WHITE);
    refresh();
}


bool moveUpdate(void) {

    if (pushAnimationData.action == STOP)
        return true;


    static int t = 0;
    const PushAnimationData *data = &pushAnimationData;

    int x[5], y[5];
    x[0] = data->j * BLOCK_WIDTH;
    y[0] = data->i * BLOCK_HEIGHT;

    switch (data->action) {
        case UP:
            x[1] = x[0]; y[1] = y[0] - BLOCK_HEIGHT;
            x[2] = x[0]; y[2] = y[0] - BLOCK_HEIGHT * 2;
            x[3] = x[0]; y[3] = y[0] - t;
            x[4] = x[0]; y[4] = y[1] - t;
            break;
        case DOWN:
            x[1] = x[0]; y[1] = y[0] + BLOCK_HEIGHT;
            x[2] = x[0]; y[2] = y[0] + BLOCK_HEIGHT * 2;
            x[3] = x[0]; y[3] = y[0] + t;
            x[4] = x[0]; y[4] = y[1] + t;
            break;
        case LEFT:
            x[1] = x[0] - BLOCK_WIDTH; y[1] = y[0];
            x[2] = x[0] - BLOCK_WIDTH * 2; y[2] = y[0];
            x[3] = x[0] - t; y[3] = y[0];
            x[4] = x[1] - t; y[4] = y[0];
            break;
        case RIGHT:
            x[1] = x[0] + BLOCK_WIDTH; y[1] = y[0];
            x[2] = x[0] + BLOCK_WIDTH * 2; y[2] = y[0];
            x[3] = x[0] + t; y[3] = y[0];
            x[4] = x[1] + t; y[4] = y[0];
            break;
        case STOP:
            /* this should not happen */
            return true;
    }


    /* draw the blocks in the order of upper level to lower level */
    int order[5] = {0, 1, 2, 3, 4};
    /* priority : CST > GK > CAGE > BLANK */
    for (int i = 0; i < 5; i++) {
        for (int j = i; j < 5; j++) {
            if (data->imageID[order[i]] < data->imageID[order[j]]) {
                swap(order[i], order[j]);
            }
        }
    }
    
    for (int i = 0; i < 5; i++) {
        fillArea(x[i], y[i], x[i]+BLOCK_WIDTH, y[i]+BLOCK_HEIGHT, BLACK);
    }

    for (int i = 0; i < 5; i++) {
        int id = data->imageID[order[i]];
        if (id != IMG_BLANK) {
            if (id < BLOCK_MASK_TYPE)
                drawImageMask(x[order[i]], y[order[i]], BLOCK_WIDTH, BLOCK_HEIGHT, blockImage[id], blockImageMask[id]);
            else 
                drawImage(x[order[i]], y[order[i]], BLOCK_WIDTH, BLOCK_HEIGHT, blockImage[id]);
        }
    }

    /* finally, check if the animation is completed */
    t++;
    if (t == 8) {
        t = 0;
        return true;
    }
    return false;
}


void registerPushAnimation(Action action) {
    PushAnimationData *data = &pushAnimationData;

    data->action = action;
    if (data->action == STOP)
        return;

    int i = gameState.cstRow;
    int j = gameState.cstCol;

    data->i = i;
    data->j = j;

    int i1, j1;
    switch (action) {
        case UP:    i1 = i - 1; j1 = j; break;
        case DOWN:  i1 = i + 1; j1 = j; break;
        case LEFT:  i1 = i; j1 = j - 1; break;
        case RIGHT: i1 = i; j1 = j + 1; break;
        default: break;
    }
    int i2 = i1 * 2 - i;
    int j2 = j1 * 2 - j;

    data->imageID[0] = gameState.board[i][j];
    data->imageID[1] = gameState.board[i1][j1];
    data->imageID[2] = gameState.board[i2][j2];

    switch (data->imageID[0]) {
        case CST: data->imageID[3] = IMG_CST; data->imageID[0] = IMG_BLANK; break;
        case CST_ON_CAGE: data->imageID[3] = IMG_CST; data->imageID[0] = IMG_CAGE; break;
        default: /* these should not happen */ break;
    }

    switch (data->imageID[1]) {
        case GK: data->imageID[4] = IMG_GK; data->imageID[1] = IMG_BLANK; break;
        case GK_IN_CAGE: data->imageID[4] = IMG_GK; data->imageID[1] = IMG_CAGE; break;
        case CAGE: data->imageID[4] = IMG_BLANK; data->imageID[1] = IMG_CAGE; break;
        case BLANK: data->imageID[4] = IMG_BLANK; data->imageID[1] = IMG_BLANK; break;
        default: /* these should not happen */ break;
    }

    switch (data->imageID[2]) {
        case GK: data->imageID[2] = IMG_GK; break;
        case GK_IN_CAGE: data->imageID[2] = IMG_GK_IN_CAGE; break;
        case BLANK: data->imageID[2] = IMG_BLANK; break;
        case CAGE: data->imageID[2] = IMG_CAGE; break;
        case TREE: data->imageID[2] = IMG_TREE; break;
        default: /* these should not happen */ break;
    }

}
