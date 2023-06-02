#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "game.h"

/**
 * @brief draw the board to the framebuffer
*/
void drawBoard(void);


/**
 * @brief display welcome screen
*/
void displayWelcome(void);


/**
 * @brief update the animation of moving for one timestep
 * @return true if the animation is finished
 */
bool moveUpdate(void);

/*
  upper level: img3 -> img4
  lower level: img0 -> img1 -> img2 
  block id:   (i, j)
*/
typedef struct {
    Action action;
    uint8_t i, j; /* the position of the image0 */
    int8_t imageID[5];
} PushAnimationData;

extern PushAnimationData pushAnimationData;


/**
 * @brief register a push animation
 * @param Action the action of the block to be moved
 */
void registerPushAnimation(Action action);

