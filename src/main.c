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

int main(void)
{
    lcd_init();        // init LCD
    button_init();

    gameInitialize(3);
    // for( int i = 0; i < NUM_COLS; i++ )
    // {
    //     drawBlock(2, i, IMG_TREE);
    //     drawBlock(4, i, IMG_TREE);
    //     drawBlock(6, i, IMG_TREE);
    // }
    // drawBlock(3, 1, IMG_CST);
    // drawBlock(3, 2, IMG_GK);
    // drawBlock(3, 3, IMG_CAGE);
    // drawBlock(5, 2, IMG_CST);
    // drawBlock(5, 3, IMG_GK_IN_CAGE);
    // fillArea(80, 40, 160, 80, GREEN);
    // refresh();



    // drawBoard();
    // drawString(60,25,"TEST",WHITE);
    refresh();

    while (1)
    {
        if (getButton(JOY_LEFT))
        {
            if (gameMoveCST(RIGHT)) {
                drawBoard();
                drawString(25,25,"WIN", BLUE);
                refresh();
                break;
            }
        }
        if (getButton(JOY_DOWN))
        {
            if (gameMoveCST(UP)) {
                drawBoard();
                drawString(25,25,"WIN", BLUE);
                refresh();
                break;
            }
        }
        if (getButton(JOY_RIGHT))
        {
            if (gameMoveCST(LEFT)) {
                drawBoard();
                drawString(25,25,"WIN", BLUE);
                refresh();
                break;
            }
        }
        if (getButton(JOY_CTR))
        {
            if (gameMoveCST(DOWN)) {
                drawBoard();
                drawString(25,25,"WIN", BLUE);
                refresh();
                break;
            }
        }
        // if (getButton(BUTTON_1))
        // {
        //     drawString(25,25,"SW1", BLUE);
        // }
        // if (getButton(BOOT_0))
        // {
        //     drawString(25,25,"B", BLUE);
        // }
        drawBoard();
        char step[10];
        sprintf(step, "%d", gameState.step);
        showString(LCD_W-24,0,step,WHITE);
        refresh();
        

    }
}
