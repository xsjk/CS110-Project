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
#include "3D/object.h"
#include "starfield.h"
#include "systick.h"

GuiMode mode = StartMode;




void mainloop(void) {

    uint8_t selectedLevel = 0, selectedBoxes = 0;
    // initially all best steps are very large
    uint8_t bestSteps[3][3] = {
         {-1, -1, -1} ,
         {-1, -1, -1} ,
         {-1, -1, -1}
    };

    bool isWin = false;

    lcd_fb_setaddr(framebuffer);

    // Initial stars.
    for (int i=0; i < NUM_STARS; i++)
    {
        g_stars[i].x = rnd_u32();
        g_stars[i].y = rnd_u32();
        g_stars[i].z = rnd_u32();
        g_stars[i].p = -1;
    }

    while (1) {


        // Enable continuous framebuffer update.

        switch (mode) {
            case StartMode:

                lcd_fb_enable();
                update_stars();
                drawStringCenter(20, "WELCOME,", YELLOW);
                drawStringCenter(40, "BRO", YELLOW);

                if (getButton(BUTTON_1)) {
                    mode = LevelSelectMode;
                    clear();
                }
                break;

            case LevelSelectMode:

                lcd_fb_enable();
                update_stars();
                drawStringCenter(10, "Easy", selectedLevel == 0 ? RED : YELLOW);
                drawStringCenter(30, "Medium", selectedLevel == 1 ? RED : YELLOW);
                drawStringCenter(50, "Hard", selectedLevel == 2 ? RED : YELLOW);

                if (getButton(JOY_RIGHT))
                    selectedLevel = (selectedLevel + 2) % 3;
                else if (getButton(JOY_LEFT))
                    selectedLevel = (selectedLevel + 1) % 3;
                else if (getButton(BUTTON_1)) {
                    mode = BoxesSelectMode;
                    clear();
                }
                else if (getButton(BOOT_0)) {
                    mode = StartMode;
                    clear();
                }

                break;

            case BoxesSelectMode:

                lcd_fb_enable();
                update_stars();
                drawStringCenter(10, "1 Boxes", selectedBoxes == 0 ? RED : YELLOW);
                drawStringCenter(30, "2 Boxes", selectedBoxes == 1 ? RED : YELLOW);
                drawStringCenter(50, "3 Boxes", selectedBoxes == 2 ? RED : YELLOW);

                if (getButton(JOY_RIGHT))
                    selectedBoxes = (selectedBoxes + 2) % 3;
                else if (getButton(JOY_LEFT))
                    selectedBoxes = (selectedBoxes + 1) % 3;
                else if (getButton(BUTTON_1)) {
                    mode = GameStartMode;
                }
                else if (getButton(BOOT_0)) {
                    mode = LevelSelectMode;
                    clear();
                }
                break;

            case GameStartMode:

                gameInitialize(selectedLevel + 1, selectedBoxes + 1);
                lcd_fb_disable();
                mode = GameMode;
                break;

            case GameMode:

                clear();
                drawBoard();
                displaySteps(gameState.step);
                refresh();
                

                if (getButton(JOY_LEFT)) {
                    mode = PushAnimation;
                    isWin = gameMoveCST(RIGHT);
                }
                else if (getButton(JOY_DOWN)) {
                    mode = PushAnimation;
                    isWin = gameMoveCST(UP);
                }
                else if (getButton(JOY_RIGHT)) {
                    mode = PushAnimation;
                    isWin = gameMoveCST(LEFT);
                }
                else if (getButton(JOY_CTR)) {
                    mode = PushAnimation;
                    isWin = gameMoveCST(DOWN);
                }
                else if (getButton(BOOT_0)) {
                    mode = BoxesSelectMode;
                    clear();
                    break;
                }
            

                break;

            case PushAnimation:

                if (moveUpdate()) 
                    /* the animation is done */
                    mode = isWin ? GameWonMode : GameMode;
                
                refresh();
                break;

            case GameWonMode:

                drawString(LCD_W - 3 * 8, 30, "You", YELLOW);
                drawString(LCD_W - 3 * 8, 50, "Win", YELLOW);

                if (getButton(BUTTON_1)) {
                    mode = HighScoreMode;
                    clear();
                }
                if (getButton(BOOT_0))
                    mode = GameStartMode;

                break;

            case HighScoreMode:

                lcd_fb_enable();
                update_stars();
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
                    mode = StartMode;
                    // reset seleceted level and boxes
                    selectedLevel = 0;
                    selectedBoxes = 0;
                    clear();
                }
                break;
        }
    }
}