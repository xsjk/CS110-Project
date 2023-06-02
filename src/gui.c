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

void guiUpdate(void) {
    while (1) {
        switch (guiMode) {
            case StartMode:
                clear();
                drawString(30, 30, "START MODE", WHITE);
                refresh();
                if (getButton(BUTTON_1))
                    guiMode = MenuMode;
                break;
            case MenuMode:
                clear();
                drawString(30, 30, "MENU MODE", WHITE);
                refresh();
                if (getButton(BUTTON_1)) {
                    gameInitialize(1);
                    drawBoard();
                    refresh();
                    guiMode = GameMode;
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
                refresh();
                break;
            // case PushingMode:
            //     break;
            case GameWonMode:
                clear();
                drawString(30, 20, "WON MODE", GREEN);
                refresh();
                if (getButton(BUTTON_1))
                    guiMode = HighScoreMode;
                break;
            case HighScoreMode:
                clear();
                drawString(30, 40, "HIGHSCORE MODE", WHITE);
                refresh();
                if (getButton(BUTTON_1))
                    guiMode = StartMode;
                break;
        }
    }
}