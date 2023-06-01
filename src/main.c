#include <string.h>
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

    gameInitialize(1);
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
    showString(60,25,"TEST",WHITE);
    refresh();

    while (1)
    {
        showString(60,25,"TEST",WHITE);
        if (Get_Button(JOY_LEFT))
        {
            showString(25,25,"L", BLUE);
            //continue;
        }
        if (Get_Button(JOY_DOWN))
        {
            showString(25,25,"D", BLUE);
        }
        showString(5,5,"U:INOP",RED);
        if (Get_Button(JOY_RIGHT))
        {
            showString(25,25,"R", BLUE);
        }
        if (Get_Button(JOY_CTR))
        {
            showString(25,25,"C", BLUE);
        }
        if (Get_Button(BUTTON_1))
        {
            showString(25,25,"SW1", BLUE);
        }
        if (Get_Button(BOOT_0))
        {
            showString(25,25,"B", BLUE);
        }
        refresh();
    }
}
