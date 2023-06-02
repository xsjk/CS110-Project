#include <string.h>
#include <stdio.h>
#include "button.h"
#include "lcd.h"
#include "color.h"
#include "assets.h"
#include "display.h"
#include "game_display.h"
#include "font.h"
#include "gd32vf103_gpio.h"
#include "gui.h"

GuiMode guiMode = StartMode;

void guiMainLoop(void) {
    uint8_t selectedLevel = 0, selectedBoxes = 0;
    // initially all best steps are very large
    uint8_t bestSteps[3][3] = {
         {-1, -1, -1} ,
         {-1, -1, -1} ,
         {-1, -1, -1}
    };
    while (1) {
        switch (guiMode) {
            case StartMode:
                clear();
                drawString(30, 30, "START MODE", WHITE);
                if (getButton(BUTTON_1))
                    guiMode = LevelSelectMode;
                break;
            case LevelSelectMode:
                clear();
                if (getButton(JOY_RIGHT))
                    selectedLevel = (selectedLevel + 2) % 3;
                else if (getButton(JOY_LEFT))
                    selectedLevel = (selectedLevel + 1) % 3;
                else if (getButton(BUTTON_1)) {
                    guiMode = BoxesSelectMode;
                }
                drawStringCenter(10, "Easy", selectedLevel == 0 ? RED : YELLOW);
                drawStringCenter(30, "Medium", selectedLevel == 1 ? RED : YELLOW);
                drawStringCenter(50, "Hard", selectedLevel == 2 ? RED : YELLOW);
                break;
            case BoxesSelectMode:
                clear();
                if (getButton(JOY_RIGHT))
                    selectedBoxes = (selectedBoxes + 2) % 3;
                else if (getButton(JOY_LEFT))
                    selectedBoxes = (selectedBoxes + 1) % 3;
                else if (getButton(BUTTON_1)) {
                    gameInitialize(selectedLevel + 1, selectedBoxes + 1);
                    drawBoard();
                    guiMode = GameMode;
                }
                drawStringCenter(10, "1 Boxes", selectedBoxes == 0 ? RED : YELLOW);
                drawStringCenter(30, "2 Boxes", selectedBoxes == 1 ? RED : YELLOW);
                drawStringCenter(50, "3 Boxes", selectedBoxes == 2 ? RED : YELLOW);
                break;
            case GameMode:
                if (getButton(JOY_LEFT)) {
                    if (gameMoveCST(RIGHT))
                        guiMode = GameWonMode;
                }
                else if (getButton(JOY_DOWN)) {
                    if (gameMoveCST(UP))
                        guiMode = GameWonMode;
                }
                else if (getButton(JOY_RIGHT)) {
                    if (gameMoveCST(LEFT))
                        guiMode = GameWonMode;
                }
                if (getButton(JOY_CTR)) {
                    if (gameMoveCST(DOWN))
                        guiMode = GameWonMode;
                }
                drawBoard();
                displaySteps(gameState.step);
                break;
            // case PushingMode:
            //     break;
            case GameWonMode:
                drawString(LCD_W - 3 * 8, 30, "You", YELLOW);
                drawString(LCD_W - 3 * 8, 50, "Win", YELLOW);
                if (getButton(BUTTON_1))
                    guiMode = HighScoreMode;
                break;
            case HighScoreMode:
                clear();
                char str[20];
                sprintf(str, "Level %d, %d Boxes", selectedLevel + 1, selectedBoxes + 1);
                drawStringCenter(10, str, WHITE);
                if (bestSteps[selectedLevel][selectedBoxes] > gameState.step) {
                    drawStringCenter(30, "NEW RECORD!", RED);
                    drawIntCenter(50, gameState.step, YELLOW);
                }
                else {
                    sprintf(str, "RECORD STEPS: %d", bestSteps[selectedLevel][selectedBoxes]);
                    drawStringCenter(30, str, WHITE);
                    sprintf(str, "YOUR STEPS: %d", gameState.step);
                    drawStringCenter(50, str, WHITE);
                }
                if (getButton(BUTTON_1)) {
                    // put best steps update here so that the new record can be always displayed
                    bestSteps[selectedLevel][selectedBoxes] = gameState.step;
                    guiMode = StartMode;
                    // reset seleceted level and boxes
                    selectedLevel = 0;
                    selectedBoxes = 0;
                }
                break;
        }
        refresh();
    }
}