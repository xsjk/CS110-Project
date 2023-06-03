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

    GuiMode next_mode;

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

            case StartModeFadeIn:

                lcd_fb_enable();
                update_stars();
                if (startModeFadeInUpdate())
                    mode = StartMode;
                break;


            case StartMode:

                lcd_fb_enable();
                update_stars();
                drawStringCenter(20, "WELCOME,", YELLOW);
                drawStringCenter(40, "BRO", YELLOW);

                chaseAnimation();

                if (getButton(BUTTON_1)) {
                    mode = StartModeFadeOut;
                    next_mode = LevelSelectModeFadeIn;
                }
                break;

            case StartModeFadeOut:

                lcd_fb_enable();
                update_stars();
                if (startModeFadeOutUpdate()) {
                    mode = next_mode;
                }
                break;

            case LevelSelectModeFadeIn:

                lcd_fb_enable();
                update_stars();
                if (levelSelectModeFadeInUpdate(selectedLevel))
                    mode = LevelSelectMode;
                
                if (getButton(JOY_RIGHT))
                    selectedLevel = (selectedLevel + 2) % 3;
                else if (getButton(JOY_LEFT))
                    selectedLevel = (selectedLevel + 1) % 3;
                else if (getButton(BUTTON_1)) {
                    mode = LevelSelectModeFadeOut;
                    next_mode = BoxesSelectModeFadeIn;
                }
                else if (getButton(BOOT_0)) {
                    mode = StartMode;
                    next_mode = StartModeFadeIn;
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
                    mode = LevelSelectModeFadeOut;
                    next_mode = BoxesSelectModeFadeIn;
                }
                else if (getButton(BOOT_0)) {
                    mode = LevelSelectModeFadeOut;
                    next_mode = StartModeFadeIn;
                }

                break;

            case LevelSelectModeFadeOut:

                lcd_fb_enable();
                update_stars();
                if (levelSelectModeFadeOutUpdate(selectedLevel)) {
                    mode = next_mode;
                }
                break;

            case BoxesSelectModeFadeIn:

                lcd_fb_enable();
                update_stars();
                if (boxesSelectModeFadeInUpdate(selectedBoxes))
                    mode = BoxesSelectMode;
                
                if (getButton(JOY_RIGHT))
                    selectedBoxes = (selectedBoxes + 2) % 3;
                else if (getButton(JOY_LEFT))
                    selectedBoxes = (selectedBoxes + 1) % 3;
                else if (getButton(BUTTON_1)) {
                    mode = BoxesSelectModeFadeOut;
                    next_mode = GameModeStart;
                }
                else if (getButton(BOOT_0)) {
                    mode = BoxesSelectModeFadeOut;
                    next_mode = LevelSelectModeFadeIn;
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
                    mode = BoxesSelectModeFadeOut;
                    next_mode = GameModeStart;
                }
                else if (getButton(BOOT_0)) {
                    mode = BoxesSelectModeFadeOut;
                    next_mode = LevelSelectModeFadeIn;
                    clear();
                }
                break;

            case BoxesSelectModeFadeOut:

                lcd_fb_enable();
                update_stars();
                if (boxesSelectModeFadeOutUpdate(selectedBoxes)) {
                    mode = next_mode;
                }
                break;


            case GameModeStart:

                gameInitialize(selectedLevel + 1, selectedBoxes + 1);
                init_buffer();
                mode = GameModeFadeIn;
                break;

            case GameModeFadeIn:

                lcd_fb_enable();
                update_stars();
                if (gameModeFadeInUpdate()) {
                    lcd_fb_disable();
                    mode = GameMode;
                }
                break;

            case GameMode:

                clear();
                drawBoard();
                
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
                    mode = GameModeFadeOut;
                    next_mode = BoxesSelectModeFadeIn;
                    break;
                }
                else if (getButton(BUTTON_1)) {
                    mode = GameModeFadeOut;
                    next_mode = GameMode3DFadeIn;
                    break;
                }


                displaySteps(gameState.step);

                refresh();

                break;

            case GameModeFadeOut:

                lcd_fb_enable();

                if (gameModeFadeOutUpdate()) {
                    mode = next_mode;
                }
                break;  

            case PushAnimation:

                if (pushAnimationUpdate()) {
                    if (isWin) {
                        mode = GameWonModeFadeIn;
                    }
                    else {
                        mode = GameMode;
                    }
                }
                refresh();
                break;

            case PushAnimation3D: 
                 
                if (pushAnimation3DUpdate()) {
                    if (isWin) {
                        mode = GameWonModeFadeIn;
                    }
                    else {
                        mode = GameMode3D;
                    }
                }
                refresh();
                break;

            case GameMode3DFadeIn:

                lcd_fb_enable();
                if (gameMode3DFadeInUpdate()) {
                    mode = GameMode3D;
                }
                break;

            case GameMode3D:

                lcd_fb_enable();

                drawBoard3D();
                
                if (getButton(JOY_LEFT)) {
                    mode = PushAnimation3D;
                    isWin = gameMoveCST(RIGHT);
                }
                else if (getButton(JOY_DOWN)) {
                    mode = PushAnimation3D;
                    isWin = gameMoveCST(UP);
                }
                else if (getButton(JOY_RIGHT)) {
                    mode = PushAnimation3D;
                    isWin = gameMoveCST(LEFT);
                }
                else if (getButton(JOY_CTR)) {
                    mode = PushAnimation3D;
                    isWin = gameMoveCST(DOWN);
                }
                else if (getButton(BOOT_0)) {
                    mode = GameMode3DFadeOut;
                    next_mode = BoxesSelectModeFadeIn;
                    break;
                }
                else if (getButton(BUTTON_1)) {
                    mode = GameMode3DFadeOut;
                    next_mode = GameModeFadeIn;
                    break;
                }

                displaySteps(gameState.step);
                break;

            case GameMode3DFadeOut:
                
                lcd_fb_enable();

                if (gameMode3DFadeOutUpdate()) {
                    mode = next_mode;
                }



                break;

            
            case GameWonModeFadeIn:
                
                lcd_fb_enable();

                if (gameWonModeFadeInUpdate()) {
                    mode = GameWonModeFadeOut;
                }
                if (getButton(BUTTON_1)) {
                    mode = GameModeFadeOut;
                    next_mode = HighScoreModeFadeIn;
                }
                if (getButton(BOOT_0)) {
                    mode = GameModeFadeOut;
                    next_mode = BoxesSelectModeFadeIn;
                }
                break;

            case GameWonModeFadeOut:
            
                lcd_fb_enable();

                if (gameWonModeFadeOutUpdate()) {
                    mode = GameWonModeFadeIn;
                }
                if (getButton(BUTTON_1)) {
                    mode = GameModeFadeOut;
                    next_mode = HighScoreModeFadeIn;
                }
                if (getButton(BOOT_0)) {
                    mode = GameModeFadeOut;
                    next_mode = BoxesSelectModeFadeIn;
                }

                break;  

            case HighScoreModeFadeIn:
                
                lcd_fb_enable();
                update_stars();
                if (highScoreModeFadeInUpdate(selectedLevel, selectedBoxes, bestSteps)) {
                    mode = HighScoreMode;
                }
                break;

            case HighScoreMode:

                lcd_fb_enable();
                update_stars();
                highScoreModeUpdate(selectedLevel, selectedBoxes, bestSteps);
                
                if (getButton(BUTTON_1)) {
                    // put best steps update here so that the new record can be always displayed
                    mode = HighScoreModeFadeOut;
                    next_mode = LevelSelectModeFadeIn;
                    
                }
                break;

            case HighScoreModeFadeOut:
                
                lcd_fb_enable();
                update_stars();
                if (highScoreModeFadeOutUpdate(selectedLevel, selectedBoxes, bestSteps)) {
                    bestSteps[selectedLevel][selectedBoxes] = gameState.step;
                    // reset seleceted level and boxes
                    selectedLevel = 0;
                    selectedBoxes = 0;
                    mode = next_mode;
                }
                break;  
        }
    }
}