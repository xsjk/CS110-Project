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
                    // reset these two before entering GameMode so next time we select level and boxes, they are 0 by default
                    selectedLevel = 0;
                    selectedBoxes = 0;
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
                displayScore(gameState.step); // TODO: actually not score but step
                break;
            // case PushingMode:
            //     break;
            case GameWonMode:
                drawString(30, 30, "WON MODE", GREEN);
                if (getButton(BUTTON_1))
                    guiMode = HighScoreMode;
                break;
            case HighScoreMode:
                clear();
                drawString(30, 30, "HIGHSCORE MODE", WHITE);
                if (getButton(BUTTON_1))
                    guiMode = StartMode;
                break;
        }
        refresh();
    }
}