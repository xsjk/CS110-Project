#include "game_display.h"
#include "game.h"
#include "display.h"
#include "assets.h"
#include "defines.h"
#include "systick.h"
#include "gd32vf103_libopt.h"
#include "stdio.h"
#include "3D/display.h"
#include "3D/camera.h"

#define PERIOD 10
#define N (DELAY / PERIOD)

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


// TODO remove this function
static void drawGameObject3D(int x, int y) {
    switch (gameState.board[y][x]) {
        case GK: drawCube((Cube) { { { x, y, 0 } }, { {x + 1, y + 1, 1} } }, YELLOW); break;
        case CST: drawCube((Cube) { { { x, y, 0 } }, { {x + 1, y + 1, 1} } }, RED); break;
        case CAGE: drawRectangle3D((Rectangle3D) { { { x, y, 0 } }, { {x + 1, y + 1, 0} } }, BLUE); break;
        case GK_IN_CAGE: drawCube((Cube) { { { x, y, 0 } }, { {x + 1, y + 1, 1} } }, CYAN); break;
        case CST_ON_CAGE: drawCube((Cube) { { { x, y, 0 } }, { {x + 1, y + 1, 1} } }, MAGENTA); break;
        case TREE: drawCube((Cube) { { { x, y, 0 } }, { {x + 1, y + 1, 1} } }, GREEN); break;
        case BLANK: break;
    }
}

void drawBoard3D(void) {
    for (int y = 0; y < BOARD_HEIGHT; y++)
        for (int x = 0; x < BOARD_WIDTH; x++) {
            switch (gameState.board[y][x]) {
                case CAGE: drawRectangle3D((Rectangle3D) { { { x, y, 0 } }, { {x + 1, y + 1, 0} } }, BLUE); break;
            }
        }
    for (int y = BOARD_HEIGHT - 1; y > 0; y--) {
        for (int x = 0; x < BOARD_WIDTH / 2; x++)
            drawGameObject3D(x, y);
        for (int x = BOARD_WIDTH - 1; x > BOARD_WIDTH / 2; x--)
            drawGameObject3D(x, y);
    }
}

void displayWelcome(void) {
    clear();
    drawString(60, 25, "Welcome!", WHITE);
    refresh();
}



static inline Depth getDepth(Vec3 v) {
    return world_to_camera(v).z * (1 << (8 * sizeof(Depth)));
}


bool pushAnimation3DUpdate(void) {

    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();


    if (pushAnimationData.action == STOP)
        return true;

    /* The 3D case is complicated so we just simply update the whole screen */
    /* But we have to pay attension to the rendering order */
    /* The order is from the farthest to the nearest */


    /* update zbuffer when necessary */

    static int t = 0;
    const PushAnimationData *data = &pushAnimationData;

    float x[5], y[5];
    x[0] = data->j;
    y[0] = data->i;


    switch (data->action) {
        case UP:
            x[1] = x[0]; y[1] = y[0] - 1;
            x[2] = x[0]; y[2] = y[1] - 1;
            x[3] = x[0]; y[3] = y[0] - t / 8.0;
            x[4] = x[0]; y[4] = y[1] - t / 8.0;
            break;
        case DOWN:
            x[1] = x[0]; y[1] = y[0] + 1;
            x[2] = x[0]; y[2] = y[1] + 1;
            x[3] = x[0]; y[3] = y[0] + t / 8.0;
            x[4] = x[0]; y[4] = y[1] + t / 8.0;
            break;
        case LEFT:
            x[1] = x[0] - 1; y[1] = y[0];
            x[2] = x[1] - 1; y[2] = y[0];
            x[3] = x[0] - t / 8.0; y[3] = y[0];
            x[4] = x[1] - t / 8.0; y[4] = y[0];
            break;
        case RIGHT:
            x[1] = x[0] + 1; y[1] = y[0];
            x[2] = x[1] + 1; y[2] = y[0];
            x[3] = x[0] + t / 8.0; y[3] = y[0];
            x[4] = x[1] + t / 8.0; y[4] = y[0];
            break;
        case STOP: /* this should not happen */ return true;
    }

    /* clear only the two blocks that are moving */
    switch (data->imageID[3]) {
        case IMG_CST:
            drawCube((Cube) { { { x[3], y[3], 0 } }, { { x[3] + 1, y[3] + 1, 1 } } }, BLACK);
            break;
        default:
            /* This should not happen */
            drawString2(0, 60, "ERROR1", RED);
            break;
    }

    switch (data->imageID[4]) {
        case IMG_GK:
            drawCube((Cube) { { { x[4], y[4], 0 } }, { { x[4] + 1, y[4] + 1, 1 } } }, BLACK);
            break;
        case IMG_BLANK:
            break;
        default:
            /* This should not happen */
            drawString2(0, 60, "ERROR2", RED);
            break;
    }


    t++;


    switch (data->action) {
        case UP:
            x[1] = x[0]; y[1] = y[0] - 1;
            x[2] = x[0]; y[2] = y[1] - 1;
            x[3] = x[0]; y[3] = y[0] - t / 8.0;
            x[4] = x[0]; y[4] = y[1] - t / 8.0;
            break;
        case DOWN:
            x[1] = x[0]; y[1] = y[0] + 1;
            x[2] = x[0]; y[2] = y[1] + 1;
            x[3] = x[0]; y[3] = y[0] + t / 8.0;
            x[4] = x[0]; y[4] = y[1] + t / 8.0;
            break;
        case LEFT:
            x[1] = x[0] - 1; y[1] = y[0];
            x[2] = x[1] - 1; y[2] = y[0];
            x[3] = x[0] - t / 8.0; y[3] = y[0];
            x[4] = x[1] - t / 8.0; y[4] = y[0];
            break;
        case RIGHT:
            x[1] = x[0] + 1; y[1] = y[0];
            x[2] = x[1] + 1; y[2] = y[0];
            x[3] = x[0] + t / 8.0; y[3] = y[0];
            x[4] = x[1] + t / 8.0; y[4] = y[0];
            break;
        case STOP: /* this should not happen */ return true;
    }

    /* update only the depth of the two blocks that are moving */
    // zbuffer[(int)y[0] * BOARD_WIDTH + (int)x[0]] = getDepth((Vec3) { { x[1] + 0.5, y[1] + 0.5, 0.5 } });
    // zbuffer[(int)y[1] * BOARD_WIDTH + (int)x[1]] = getDepth((Vec3) { { x[1] + 0.5, y[1] + 0.5, 0.5 } });
    // zbuffer[(int)y[2] * BOARD_WIDTH + (int)x[2]] = getDepth((Vec3) { { x[2] + 0.5, y[2] + 0.5, 0.5 } });



    /* sort the zorder list based on depth */
    // TODO simplyfly 
    /* sort */
    for (int i = 0; i < NUM_BLOCKS; i++) {
        for (int j = i + 1; j < NUM_BLOCKS; j++) {
            if (zbuffer[zorder[i]] < zbuffer[zorder[j]]) {
                swap(zorder[i], zorder[j]);
            }
        }
    }

    /* draw the blocks in the order of upper level to lower level */
    for (int i = 0; i < NUM_BLOCKS; i++) {
        int id = zorder[i];
        int xx = id % BOARD_WIDTH;
        int yy = id / BOARD_WIDTH;

        if (id == y[1] * BOARD_WIDTH + x[1]) {
            switch (data->imageID[3]) {
                case IMG_CST:
                    drawCube((Cube) { { { x[3], y[3], 0 } }, { { x[3] + 1, y[3] + 1, 1 } } }, RED);
                    break;
                default:
                    /* This should not happen */
                    drawString2(0, 60, "ERROR3", RED);
                    break;
            }
        }
        else if (id == y[2] * BOARD_WIDTH + x[2]) {
            switch (data->imageID[4]) {
                case IMG_GK:
                    drawCube((Cube) { { { x[4], y[4], 0 } }, { { x[4] + 1, y[4] + 1, 1 } } }, YELLOW);
                    break;
                case IMG_BLANK:
                    break;
                default:
                    /* This should not happen */
                    drawString2(0, 60, "ERROR4", RED);
                    break;
            }
        }
        else {
            switch (gameState.board[yy][xx]) {
                case GK: drawCube((Cube) { { { xx, yy, 0 } }, { {xx + 1, yy + 1, 1} } }, YELLOW); break;
                case CST: /* this should not happen */ 
                    drawString2(0, 60, "ERROR5", RED);
                break;
                case CAGE: drawRectangle3D((Rectangle3D) { { { xx, yy, 0 } }, { {xx + 1, yy + 1, 0} } }, BLUE); break;
                case GK_IN_CAGE: drawCube((Cube) { { { xx, yy, 0 } }, { {xx + 1, yy + 1, 1} } }, CYAN); break;
                case CST_ON_CAGE: drawCube((Cube) { { { xx, yy, 0 } }, { {xx + 1, yy + 1, 1} } }, MAGENTA); break;
                case TREE: drawCube((Cube) { { { xx, yy, 0 } }, { {xx + 1, yy + 1, 1} } }, GREEN); break;
                case BLANK: break;
            }
        }
    }


    /* finally, check if the animation is completed */
    if (t == 8) {
        t = 0;
        return true;
    }
    return false;


}


bool pushAnimationUpdate(void) {

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
    int order[5] = { 0, 1, 2, 3, 4 };
    /* priority : CST > GK > CAGE > BLANK */
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (data->imageID[order[i]] < data->imageID[order[j]]) {
                swap(order[i], order[j]);
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        fillArea(x[i], y[i], x[i] + BLOCK_WIDTH, y[i] + BLOCK_HEIGHT, BLACK);
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
    if (++t == 8) {
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





#define DELAY 1000
bool startModeFadeInUpdate() {
    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 y;
    y.r = 0b11111 * (n) / (float)N;
    y.g = 0b111111 * (n) / (float)N;
    y.b = 0;

    drawStringCenter(20, "WELCOME,", y.c);
    drawStringCenter(40, "BRO", y.c);

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY


#define DELAY 1000
bool startModeFadeOutUpdate(void) {
    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 y;
    y.r = 0b11111 * (N - n) / (float)N;
    y.g = 0b111111 * (N - n) / (float)N;
    y.b = 0;
    drawStringCenter(20, "WELCOME,", y.c);
    drawStringCenter(40, "BRO", y.c);

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY


#define DELAY 1000
bool levelSelectModeFadeInUpdate(uint8_t level) {


    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 r, y;
    r.r = 0b11111 * (n) / (float)N;
    r.g = 0;
    r.b = 0;

    y.r = 0b11111 * (n) / (float)N;
    y.g = 0b111111 * (n) / (float)N;
    y.b = 0;

    drawStringCenter(10, "Easy", level == 0 ? r.c : y.c);
    drawStringCenter(30, "Medium", level == 1 ? r.c : y.c);
    drawStringCenter(50, "Hard", level == 2 ? r.c : y.c);

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY


#define DELAY 1000
bool levelSelectModeFadeOutUpdate(uint8_t level) {

    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 r, y;
    r.r = 0b11111 * (N - n) / (float)N;
    r.g = 0;
    r.b = 0;

    y.r = 0b11111 * (N - n) / (float)N;
    y.g = 0b111111 * (N - n) / (float)N;
    y.b = 0;

    drawStringCenter(10, "Easy", level == 0 ? r.c : y.c);
    drawStringCenter(30, "Medium", level == 1 ? r.c : y.c);
    drawStringCenter(50, "Hard", level == 2 ? r.c : y.c);

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY


#define DELAY 1000
bool boxesSelectModeFadeInUpdate(uint8_t num) {

    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 r, y;
    r.r = 0b11111 * (n) / (float)N;
    r.g = 0;
    r.b = 0;

    y.r = 0b11111 * (n) / (float)N;
    y.g = 0b111111 * (n) / (float)N;
    y.b = 0;

    drawStringCenter(10, "1 Boxes", num == 0 ? r.c : y.c);
    drawStringCenter(30, "2 Boxes", num == 1 ? r.c : y.c);
    drawStringCenter(50, "3 Boxes", num == 2 ? r.c : y.c);


    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY


#define DELAY 1000
bool boxesSelectModeFadeOutUpdate(uint8_t num) {

    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 r, y;
    r.r = 0b11111 * (N - n) / (float)N;
    r.g = 0;
    r.b = 0;

    y.r = 0b11111 * (N - n) / (float)N;
    y.g = 0b111111 * (N - n) / (float)N;
    y.b = 0;

    drawStringCenter(10, "1 Boxes", num == 0 ? r.c : y.c);
    drawStringCenter(30, "2 Boxes", num == 1 ? r.c : y.c);
    drawStringCenter(50, "3 Boxes", num == 2 ? r.c : y.c);

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY


#define CASE(NAME) \
    case NAME: \
    for (int ii = 0; ii < BLOCK_HEIGHT; ii++) {  \
        for (int jj = 0; jj < BLOCK_WIDTH; jj++) { \
            int index = (i * BLOCK_HEIGHT + ii) * LCD_W + (j * BLOCK_WIDTH + jj); \
            RGB565 rgb; \
            rgb.c = blockImage[IMG_##NAME][ii * BLOCK_WIDTH + jj]; \
            rgb.r *= (n) / (float)N; \
            rgb.g *= (n) / (float)N; \
            rgb.b *= (n) / (float)N; \
            framebuffer[index] = rgb.c; \
        } \
    } \
    break;
#define DELAY 200
bool gameModeFadeInUpdate(void) {

    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

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

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY
#undef CASE


#define DELAY 200
bool gameMode3DFadeInUpdate(void) {

    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 y, r, b, c, m, g;
    y.r = 0b11111 * (n) / (float)N;
    y.g = 0b111111 * (n) / (float)N;
    y.b = 0;

    r.r = 0b11111 * (n) / (float)N;
    r.g = 0;
    r.b = 0;

    b.r = 0;
    b.g = 0;
    b.b = 0b11111 * (n) / (float)N;

    c.r = 0;
    c.g = 0b111111 * (n) / (float)N;
    c.b = 0b11111 * (n) / (float)N;

    m.r = 0b11111 * (n) / (float)N;
    m.g = 0;
    m.b = 0b11111 * (n) / (float)N;

    g.r = 0;
    g.g = 0b111111 * (n) / (float)N;
    g.b = 0;


    for (int j = 0; j < BOARD_HEIGHT; j++)
        for (int i = 0; i < BOARD_WIDTH; i++) {
            switch (gameState.board[j][i]) {
                case GK: drawCube((Cube) { { { i, j, 0 } }, { { i + 1, j + 1, 1 } } }, y.c); break;
                case CST: drawCube((Cube) { { { i, j, 0 } }, { { i + 1, j + 1, 1 } } }, r.c); break;
                case CAGE: drawRectangle3D((Rectangle3D) { { { i, j, 0 } }, { { i + 1, j + 1, 0 } } }, b.c); break;
                case GK_IN_CAGE: drawCube((Cube) { { { i, j, 0 } }, { { i + 1, j + 1, 1 } } }, c.c); break;
                case CST_ON_CAGE: drawCube((Cube) { { { i, j, 0 } }, { { i + 1, j + 1, 1 } } }, m.c); break;
                case TREE: drawCube((Cube) { { { i, j, 0 } }, { {i + 1, j + 1, 1} } }, g.c); break;
                case BLANK: break;
            }
        }

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;

}
#undef DELAY


#define DELAY 250
bool gameModeFadeOutUpdate(void) {

    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    for (int i = 0; i < LCD_H; i++)
        for (int j = 0; j < LCD_W; j++) {
            int index = i * LCD_W + j;
            RGB565 rgb;
            rgb.c = framebuffer[index];
            rgb.r *= (N - n) / (float)N;
            rgb.g *= (N - n) / (float)N;
            rgb.b *= (N - n) / (float)N;
            framebuffer[index] = rgb.c;
        }

    RGB565 w;
    w.r = 0b11111 * (N - n) / (float)N;
    w.g = 0b111111 * (N - n) / (float)N;
    w.b = 0b11111 * (N - n) / (float)N;

    char str[21];
    sprintf(str, "%20d", gameState.step);
    drawString(0, 10, str, w.c);

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY


#define DELAY 1000
bool gameWonModeFadeInUpdate(void) {
    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 y;
    y.r = 0b11111 * (n) / (float)N;
    y.g = 0b111111 * (n) / (float)N;
    y.b = 0;

    drawString(LCD_W - 3 * 8, 30, "You", y.c);
    drawString(LCD_W - 3 * 8, 50, "Win", y.c);

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY

#define DELAY 1000
bool gameWonModeFadeOutUpdate(void) {
    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 y;
    y.r = 0b11111 * (N - n) / (float)N;
    y.g = 0b111111 * (N - n) / (float)N;
    y.b = 0;

    drawString(LCD_W - 3 * 8, 30, "You", y.c);
    drawString(LCD_W - 3 * 8, 50, "Win", y.c);

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY


#define DELAY 1000
bool highScoreModeFadeInUpdate(uint8_t level, uint8_t boxes, uint8_t bestSteps[3][3]) {

    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 w, r, y;
    w.r = 0b11111 * (n) / (float)N;
    w.g = 0b111111 * (n) / (float)N;
    w.b = 0b11111 * (n) / (float)N;
    r.r = 0b11111 * (n) / (float)N;
    r.g = 0;
    r.b = 0;
    y.r = 0b11111 * (n) / (float)N;
    y.g = 0b111111 * (n) / (float)N;
    y.b = 0;


    char str[21];
    sprintf(str, "Level %d, %d Boxes", level + 1, boxes + 1);
    drawStringCenter(10, str, w.c);
    if (bestSteps[level][boxes] > gameState.step) {
        drawStringCenter(30, "NEW RECORD!", r.c);
        drawIntCenter(50, gameState.step, y.c);
    }
    else {
        sprintf(str, "RECORD STEPS: %d", bestSteps[level][boxes]);
        drawStringCenter(30, str, w.c);
        sprintf(str, "YOUR STEPS: %d", gameState.step);
        drawStringCenter(50, str, w.c);
    }

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;

}
#undef DELAY


bool highScoreModeUpdate(uint8_t level, uint8_t boxes, uint8_t bestSteps[3][3]) {

    char str[21];
    sprintf(str, "Level %d, %d Boxes", level + 1, boxes + 1);
    drawStringCenter(10, str, WHITE);
    if (bestSteps[level][boxes] > gameState.step) {
        drawStringCenter(30, "NEW RECORD!", RED);
        drawIntCenter(50, gameState.step, YELLOW);
    }
    else {
        sprintf(str, "RECORD STEPS: %d", bestSteps[level][boxes]);
        drawStringCenter(30, str, WHITE);
        sprintf(str, "YOUR STEPS: %d", gameState.step);
        drawStringCenter(50, str, WHITE);
    }
}


#define DELAY 1000
bool highScoreModeFadeOutUpdate(uint8_t level, uint8_t boxes, uint8_t bestSteps[3][3]) {

    static int n = 0;
    static uint64_t last_update_time;
    if (get_timer_value() - last_update_time < 27000 * PERIOD)
        return false;
    last_update_time = get_timer_value();

    RGB565 w, r, y;
    w.r = 0b11111 * (N - n) / (float)N;
    w.g = 0b111111 * (N - n) / (float)N;
    w.b = 0b11111 * (N - n) / (float)N;
    r.r = 0b11111 * (N - n) / (float)N;
    r.g = 0;
    r.b = 0;
    y.r = 0b11111 * (N - n) / (float)N;
    y.g = 0b111111 * (N - n) / (float)N;
    y.b = 0;


    char str[21];
    sprintf(str, "Level %d, %d Boxes", level + 1, boxes + 1);
    drawStringCenter(10, str, w.c);
    if (bestSteps[level][boxes] > gameState.step) {
        drawStringCenter(30, "NEW RECORD!", r.c);
        drawIntCenter(50, gameState.step, y.c);
    }
    else {
        sprintf(str, "RECORD STEPS: %d", bestSteps[level][boxes]);
        drawStringCenter(30, str, w.c);
        sprintf(str, "YOUR STEPS: %d", gameState.step);
        drawStringCenter(50, str, w.c);
    }

    if (++n == N) {
        n = 0;
        return true;
    }
    return false;
}
#undef DELAY