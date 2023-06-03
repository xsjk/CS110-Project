#pragma once

#include <stdint.h>
#include <display.h>
#include "game.h"
#include "color.h"


#define BLOCK_TYPES 6
#define BLOCK_MASK_TYPE 2

#define IMG_CST 0
#define IMG_CAGE 1
#define IMG_GK 2
#define IMG_GK_IN_CAGE 3
#define IMG_CST_ON_CAGE 4
#define IMG_TREE 5
#define IMG_BLANK 6

extern const Color blockImage[BLOCK_TYPES][BLOCK_SIZE];
extern const uint64_t blockImageMask[BLOCK_MASK_TYPE];

extern const GameState gameLevel1_1, gameLevel1_2, gameLevel1_3,
                       gameLevel2_1, gameLevel2_2, gameLevel2_3,
                       gameLevel3_1, gameLevel3_2, gameLevel3_3;
                       