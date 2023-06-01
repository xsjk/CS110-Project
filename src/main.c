#include "lcd/lcd.h"
#include <string.h>
#include "utils.h"
#include "mylcd.h"
#include "color.h"
#include "assets.h"
#include "display.h"

void Inp_init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOC);

    gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6);
    gpio_init(GPIOC, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
}

void IO_init(void)
{
    Inp_init(); // inport init
    Lcd_Init(); // LCD init
}

int main(void)
{
    IO_init();         // init OLED
    // lcd_init();        // init LCD
    // YOUR CODE HERE
    for( int i = 0; i < NUM_COLS; i++ )
    {
        drawBlock(2, i, TREE);
        drawBlock(4, i, TREE);
        drawBlock(6, i, TREE);
    }
    drawBlock(3, 1, CST);
    drawBlock(3, 2, GK);
    drawBlock(3, 3, CAGE);
    drawBlock(5, 2, CST);
    drawBlock(5, 3, GK_IN_CAGE);
    LCD_ShowPicture(0,0,160-1,80-1);
    // lcd_write_u16(0, 0, 160, 80, framebuffer);


    while (1)
    {
        // LCD_ShowLogo();
        // LCD_Clear(BLACK);
        // LCD_ShowString(60,25,"TEST",WHITE);
        // if (Get_Button(JOY_LEFT))
        // {
        //     LCD_ShowString(5,25,"L", BLUE);
        //     //continue;
        // }
        // if (Get_Button(JOY_DOWN))
        // {
        //     LCD_ShowString(25,45,"D", BLUE);
        // }
        // LCD_ShowString(5,5,"U:INOP",RED);
        // if (Get_Button(JOY_RIGHT))
        // {
        //     LCD_ShowString(45,25,"R", BLUE);
        // }
        // if (Get_Button(JOY_CTR))
        // {
        //     LCD_ShowString(25,25,"C", BLUE);
        // }
        // if (Get_Button(BUTTON_1))
        // {
        //     LCD_ShowString(60,5,"SW1", BLUE);
        // }
        // LCD_ShowString(60,45,"SW2:INOP",RED);
    }
}
