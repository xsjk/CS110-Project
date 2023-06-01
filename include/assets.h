#pragma once


#include <stdint.h>
#include <lcd/lcd.h>

#define IMAGE_WIDTH 8
#define IMAGE_HEIGHT 8
#define IMAGE_SIZE (IMAGE_WIDTH*IMAGE_HEIGHT)

#define NUM_ROWS (LCD_H/IMAGE_HEIGHT)
#define NUM_COLS (LCD_W/IMAGE_WIDTH)

#define IMAGE_COUNT 6

#define CST 0
#define GK 1
#define CAGE 2
#define GK_IN_CAGE 3
#define WALL 4
#define TREE 5
extern const uint16_t images[IMAGE_COUNT][IMAGE_SIZE];