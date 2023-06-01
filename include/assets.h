#pragma once


#include <stdint.h>
#include <lcd/lcd.h>

#define IMAGE_WIDTH 8
#define IMAGE_HEIGHT 8
#define IMAGE_SIZE (IMAGE_WIDTH*IMAGE_HEIGHT)

#define NUM_ROWS (LCD_H/IMAGE_HEIGHT)
#define NUM_COLS (LCD_W/IMAGE_WIDTH)

#define IMAGE_COUNT 5

#define IMG_CST 0
#define IMG_GK 1
#define IMG_CAGE 2
#define IMG_GK_IN_CAGE 3
#define IMG_TREE 4
extern const uint16_t images[IMAGE_COUNT][IMAGE_SIZE];