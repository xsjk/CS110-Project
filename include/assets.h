#pragma once

#include <stdint.h>
#include <display.h>
#include "game.h"
#include "color.h"

#define BLOCK_WIDTH 8
#define BLOCK_HEIGHT 8
#define BLOCK_SIZE (BLOCK_WIDTH*BLOCK_HEIGHT)

#define NUM_ROWS (LCD_H/BLOCK_HEIGHT)
#define NUM_COLS (LCD_W/BLOCK_WIDTH)

#define BLOCK_TYPES 6

#define IMG_CST 0
#define IMG_GK 1
#define IMG_CAGE 2
#define IMG_GK_IN_CAGE 3
#define IMG_CST_ON_CAGE 4
#define IMG_TREE 5

extern const Color blockImage[BLOCK_TYPES][BLOCK_SIZE];

extern const GameState gameLevel1_1, gameLevel1_2, gameLevel1_3,
                       gameLevel2_1, gameLevel2_2, gameLevel2_3,
                       gameLevel3_1, gameLevel3_2, gameLevel3_3;