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
    uint8_t selectedLevel = 0;
    while (1) {
        switch (guiMode) {
            case StartMode:
                clear();
                drawString(30, 30, "START MODE", WHITE);
                if (getButton(BUTTON_1))
                    guiMode = MenuMode;
                break;
            case MenuMode:
                clear();
                if (getButton(JOY_RIGHT)) {
                    selectedLevel = (selectedLevel + 2) % 3;
                }
                else if (getButton(JOY_LEFT))
                    selectedLevel = (selectedLevel + 1) % 3;
                else if (getButton(BUTTON_1)) {
                    gameInitialize(selectedLevel + 1);
                    drawBoard();
                    guiMode = GameMode;
                    selectedLevel = 0;
                }
                switch (selectedLevel) {
                    case 0:
                        drawString(60, 10, "Easy", RED);
                        drawString(50, 30, "Medium", YELLOW);
                        drawString(60, 50, "Hard", YELLOW);
                        break;
                    case 1:
                        drawString(60, 10, "Easy", YELLOW);
                        drawString(50, 30, "Medium", RED);
                        drawString(60, 50, "Hard", YELLOW);
                        break;
                    case 2:
                        drawString(60, 10, "Easy", YELLOW);
                        drawString(50, 30, "Medium", YELLOW);
                        drawString(60, 50, "Hard", RED);
                        break;
                }
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