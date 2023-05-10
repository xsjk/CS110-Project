#ifndef __UTILS_H
#define __UTILS_H

#define JOY_LEFT GPIO_PIN_0
#define JOY_DOWN GPIO_PIN_1
#define JOY_RIGHT GPIO_PIN_2
#define JOY_UP GPIO_PIN_5
#define JOY_CTR GPIO_PIN_4

#define BUTTON_1 GPIO_PIN_6
#define BUTTON_2 GPIO_PIN_7

int Get_Button(int ch);
int Get_BOOT0(void);

#endif