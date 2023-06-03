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
 * @brief draw the 3D board to the framebuffer
*/
void drawBoard3D(void);

/**
 * @brief display welcome screen
*/
void displayWelcome(void);


/**
 * @brief update the animation of moving for one timestep
 * @return true if the animation is finished
 */
bool pushAnimationUpdate(void);

/**
 * @brief update the 3D animation of moving for one timestep
 * @return true if the animation is finished
 */
bool pushAnimation3DUpdate(void);


/**
 * @brief the struct to hold data for push animation redering
 * @note upper level: img3 -> img4
 *       lower level: img0 -> img1 -> img2 
 *       block id:   (i, j)
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


/**
 * @brief update the fade in animation of Start mode
 * @return true if the animation if finished
*/
bool startModeFadeInUpdate(void);


/**
 * @brief update the fade out animation of Start mode
 * @return true if the animation if finished
 */
bool startModeFadeOutUpdate(void);

/**
 * @brief update the fade in animation of LevelSelect mode
 * @param level the level to be highlighted
 * @return true if the animation if finished
*/
bool levelSelectModeFadeInUpdate(uint8_t level);

/**
 * @brief update the fade out animation of LevelSelect mode
 * @param level the level to be highlighted
 * @return true if the animation if finished
*/
bool levelSelectModeFadeOutUpdate(uint8_t level);

/**
 * @brief update the fade in animation of BoxesSelect mode
 * @param num the number of the box to be highlighted
 * @return true if the animation if finished
*/
bool boxesSelectModeFadeInUpdate(uint8_t num);

/**
 * @brief update the fade out animation of BoxesSelect mode
 * @param num the number of the box to be highlighted
 * @return true if the animation if finished
*/
bool boxesSelectModeFadeOutUpdate(uint8_t num);


/**
 * @brief update the fade in animation of Game mode
 * @return true if the animation if finished
*/
bool gameModeFadeInUpdate(void);

/**
 * @brief update the fade in animation of Game mode
 * @return true if the animation if finished
*/
bool gameMode3DFadeInUpdate(void);

/**
 * @brief update the fade out animation of Game mode
 * @return true if the animation if finished
*/
bool gameModeFadeOutUpdate(void);

/**
 * @brief update the fade in animation of GameWon Mode
 * @return true if the animation if finished
*/
bool gameWonModeFadeInUpdate(void);

/**
 * @brief update the fade out animation of GameWon Mode
 * @return true if the animation if finished
*/
bool gameWonModeFadeOutUpdate(void);

/**
 * @brief update the fade in animation of HighScore mode
 * @return true if the animation if finished
*/
bool highScoreModeFadeInUpdate(uint8_t level, uint8_t boxes, uint8_t bestSteps[3][3]);


/**
 * @brief update the fade in animation of HighScore mode
 * @return true if the animation if finished
*/
bool highScoreModeUpdate(uint8_t level, uint8_t boxes, uint8_t bestSteps[3][3]);

/**
 * @brief update the fade out animation of HighScore mode
 * @return true if the animation if finished
*/
bool highScoreModeFadeOutUpdate(uint8_t level, uint8_t boxes, uint8_t bestSteps[3][3]);