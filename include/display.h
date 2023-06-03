#pragma once

#include <stdbool.h>
#include "color.h"

#define LCD_W 160
#define LCD_H 80
#define LCD_SIZE (LCD_W * LCD_H)

#define BLOCK_WIDTH 8
#define BLOCK_HEIGHT 8
#define BLOCK_SIZE (BLOCK_WIDTH*BLOCK_HEIGHT)

#define NUM_ROWS (LCD_H/BLOCK_HEIGHT)
#define NUM_COLS (LCD_W/BLOCK_WIDTH)
#define NUM_BLOCKS (NUM_ROWS*NUM_COLS)

extern Color framebuffer[LCD_SIZE];
typedef uint8_t Depth;

// Since the RAM is not enough, we use a smaller zbuffer that only stores the depth of each block.
// extern Depth zbuffer[LCD_SIZE];
extern Depth zbuffer[NUM_BLOCKS];
extern uint8_t zorder[NUM_BLOCKS];

#define DEPTH_MAX ((Depth)(-1))

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
 * @brief Draw a image of the specified size at the specified position.
 * @param x The x coordinate of the starting point.
 * @param y The y coordinate of the starting point.
 * @param w The width of the image.
 * @param h The height of the image.
 * @param img The pointer to the image.
*/
void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const Color *img);

/**
 * @brief Draw a image with mask
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param img 
 * @param mask each bit represent whether this pixel is not transparent
 * @note the mask int uint64_t and only support 64bit img for the time being
 */
void drawImageMask(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const Color *img, uint64_t mask);


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


/**************************************************************/


/**
 * @brief Draw a point on the screen.
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @param color The color of the point.
 */
void drawPoint(uint8_t x, uint8_t y, Color color);


/**
 * @brief Fill color in the specified area.
 * @param xsta The x coordinate of the starting point.
 * @param ysta The y coordinate of the starting point.
 * @param xend The x coordinate of the ending point.
 * @param yend The y coordinate of the ending point.
 * @param color The color to be filled.
*/
void fillArea(uint8_t xsta, uint8_t ysta, uint8_t xend, uint8_t yend, Color color);


/**
 * @brief Fill the screen with certain color
 * @param color The color to fill
*/
void fillAll(Color color);


/**
 * @brief Draw a line
 * @param x1 The x coordinate of the starting point
 * @param y1 The y coordinate of the starting point
 * @param x2 The x coordinate of the ending point
 * @param y1 The y coordinate of the ending point
 * @param color The color of the line.
*/
void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color);


/**
 * @brief Draw a rectangle
 * @param x1 The x coordinate of the starting point
 * @param y1 The y coordinate of the starting point
 * @param x2 The x coordinate of the ending point
 * @param y1 The y coordinate of the ending point
 * @param color The color of the rectangle.
*/
void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color);

/**
 * @brief Fill a triangle
 * @param x1 The x coordinate of the first point
 * @param y1 The y coordinate of the first point
 * @param x2 The x coordinate of the second point
 * @param y2 The y coordinate of the second point
 * @param x3 The x coordinate of the third point
 * @param y3 The y coordinate of the third point
*/
void fillTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3);


/**
 * @brief Draw a circle
 * @param x0 The x coordinate of the center
 * @param y0 The y coordinate of the center
 * @param r The radius of the circle
 * @param color The color of the circle
*/
void drawCircle(uint8_t x0, uint8_t y0, uint8_t r, Color color);


/**
 * @brief Display characters with transparancy
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param c The character to display
 * @param color The color of the character
*/
void drawChar(uint8_t x, uint8_t y, char c, Color color);


/**
 * @brief Display characters without transparancy
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param c The character to display
 * @param color The color of the character
*/
void drawChar2(uint8_t x, uint8_t y, char c, Color color);


/**
 * @brief Display string with transparancy
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param p The pointer of the string to be displayed
 * @param color The color of the text
*/
void drawString(uint8_t x, uint8_t y, const char *p, Color color);


/**
 * @brief Display string without transparancy
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param p The pointer of the string to be displayed
 * @param color The color of the text
*/
void drawString2(uint8_t x, uint8_t y, const char *p, Color color);


/**
 * @brief Display string in center (vertically)
 * @param y The y coordinate of the starting point
 * @param p The pointer of the string to be displayed
 * @param color The color of the text
*/
void drawStringCenter(uint8_t y, const char *p, uint16_t color);


/**
 * @brief Display integer with transparancy
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param num The integer to be displayed
 * @param color The color of the text
*/
void drawInt(uint8_t x, uint8_t y, int num, Color color);

/**
 * @brief Display integer without transparancy
 * @param x The x coordinate of the starting point
 * @param y The y coordinate of the starting point
 * @param num The integer to be displayed
 * @param color The color of the text
*/
void drawInt2(uint8_t x, uint8_t y, int num, Color color);

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
void drawFloat(uint8_t x, uint8_t y, float num, Color color);



void init_buffer(void);
