#pragma once

#include <stdint.h>
#include <stdbool.h>

#define LCD_W 160
#define LCD_H 80
#define LCD_SIZE (LCD_W * LCD_H)

extern uint16_t framebuffer[LCD_SIZE];


//Brush color
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE           	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430
#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458
#define LIGHTGREEN     	 0X841F
#define LGRAY 			 0XC618
#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12



/**
 * @brief Draws a block of a given ID at a given position.
 * @param i The row of the block.
 * @param j The column of the block.
 * @param imageID The ID of preloaded image.
 */
void drawBlock(int i, int j, int imageID);

/**
 * @brief Displays the framebuffer on the LCD.
 */
void refresh(void);

/**
 * @brief Clears the framebuffer.
 */
void clear(void);

/**
 * @brief Display steps on the top right corner of the screen.
 * @param steps The steps to be displayed.
 */
void displaySteps(int score);

/**
 * @brief Display level on the top right corner of the screen.
 * @param level The level to be displayed.
 */
void displayLevel(int level);


/**************************************************************/


/**
 * @brief Draw a point on the screen.
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @param color The color of the point.
 */
void drawPoint(uint8_t x, uint8_t y, uint16_t color);


/**
 * @brief Fill color in the specified area.
 * @param xsta The x coordinate of the starting point.
 * @param ysta The y coordinate of the starting point.
 * @param xend The x coordinate of the ending point.
 * @param yend The y coordinate of the ending point.
 * @param color The color to be filled.
*/
void fillArea(uint8_t xsta, uint8_t ysta, uint8_t xend, uint8_t yend, uint16_t color);


/**
 * @brief Fill the screen with certain color
 * @param color The color to fill
*/
void fillAll(uint16_t color);


/**
 * @brief Draw a line
 * @param x1 The x coordinate of the starting point
 * @param y1 The y coordinate of the starting point
 * @param x2 The x coordinate of the ending point
 * @param y1 The y coordinate of the ending point
 * @param color The color of the line.
*/
void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);


/**
 * @brief Draw a rectangle
 * @param x1 The x coordinate of the starting point
 * @param y1 The y coordinate of the starting point
 * @param x2 The x coordinate of the ending point
 * @param y1 The y coordinate of the ending point
 * @param color The color of the rectangle.
*/
void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);


/**
 * @brief Draw a circle
 * @param x0 The x coordinate of the center
 * @param y0 The y coordinate of the center
 * @param r The radius of the circle
 * @param color The color of the circle
*/
void drawCircle(uint8_t x0, uint8_t y0, uint8_t r, uint16_t color);


/**
 * @brief Display characters
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param c The character to display
 * @param color The color of the character
*/
void drawChar(uint8_t x, uint8_t y, char c, uint16_t color);


/**
 * @brief Display string
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param p The pointer of the string to be displayed
 * @param color The color of the text
*/
void drawString(uint8_t x, uint8_t y, const char *p, uint16_t color);


/**
 * @brief Display string in center (vertically)
 * @param y The y coordinate of the starting point
 * @param p The pointer of the string to be displayed
 * @param color The color of the text
*/
void drawStringCenter(uint8_t y, const char *p, uint16_t color);


/**
 * @brief Display integer
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param num The integer to be displayed
 * @param color The color of the text
*/
void drawInt(uint8_t x, uint8_t y, int num, uint16_t color);


/**
 * @brief Display integer in center (vertically)
 * @param y The y coordinate of the starting point
 * @param num The integer to be displayed
 * @param color The color of the text
*/
void drawIntCenter(uint8_t y, int num, uint16_t color);


/**
 * @brief Display float
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param num The float to be displayed
 * @param color The color of the text
*/
void drawFloat(uint8_t x, uint8_t y, float num, uint16_t color);

