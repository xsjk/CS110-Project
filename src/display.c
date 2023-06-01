#include "display.h"
#include "assets.h"
#include "font.h"
#include <stdio.h>
#include "mylcd.h"

volatile uint16_t framebuffer[LCD_SIZE];

void drawBlock(int i, int j, int imageID) {
    for (int ii = 0; ii < IMAGE_HEIGHT; ii++) {
        for (int jj = 0; jj < IMAGE_WIDTH; jj++) {
            framebuffer[(i * IMAGE_HEIGHT + ii) * LCD_W + (j * IMAGE_WIDTH + jj)] = images[imageID][ii * IMAGE_WIDTH + jj];
        }
    }
}

void refresh(void) {
    lcd_write_u16(0, 0, 160, 80, (void*)framebuffer);
}

void clear(void) {
    fillAll(0);
}

/**************************************************************/

void drawPoint(uint8_t x, uint8_t y, uint16_t color) {
    framebuffer[y * LCD_W + x] = color;
}


void fillArea(uint8_t xsta, uint8_t ysta, uint8_t xend, uint8_t yend, uint16_t color) {
    for (int x = xsta; x < xend; x++)
        for (int y = ysta; y < yend; y++)
            drawPoint(x, y, color);
}

void fillAll(uint16_t color) {
    fillArea(0, 0, LCD_W, LCD_H, color);
}

void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color) {
    int xerr = 0, yerr = 0, distance;
    int incx, incy, uRow, uCol;
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0) incx = 1;
    else if (delta_x == 0) incx = 0;
    else { incx = -1; delta_x = -delta_x; }
    if (delta_y > 0) incy = 1;
    else if (delta_y == 0) incy = 0;
    else { incy = -1; delta_y = -delta_x; }
    if (delta_x > delta_y) distance = delta_x;
    else distance = delta_y;
    for (int t = 0; t < distance + 1; t++) {
        drawPoint(uRow, uCol, color);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}


void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color) {
    drawLine(x1, y1, x2, y1, color);
    drawLine(x1, y1, x1, y2, color);
    drawLine(x1, y2, x2, y2, color);
    drawLine(x2, y1, x2, y2, color);
}



void drawCircle(uint8_t x0, uint8_t y0, uint8_t r, uint16_t color) {
    int a = 0, b = r;
    while (a <= b) {
        drawPoint(x0 - b, y0 - a, color);             //3           
        drawPoint(x0 + b, y0 - a, color);             //0           
        drawPoint(x0 - a, y0 + b, color);             //1                
        drawPoint(x0 - a, y0 - b, color);             //2             
        drawPoint(x0 + b, y0 + a, color);             //4               
        drawPoint(x0 + a, y0 - b, color);             //5
        drawPoint(x0 + a, y0 + b, color);             //6 
        drawPoint(x0 - b, y0 + a, color);             //7
        a++;
        if ((a * a + b * b) > (r * r))
            b--;
    }
}


void showChar(uint8_t x, uint8_t y, char c, uint8_t mode, uint16_t color) {
    uint8_t temp;
    uint8_t pos;
    uint8_t x0 = x;
    if (x > LCD_W - 16 || y > LCD_H - 16)return;	    //Settings window		   
    c = c - ' ';//Get offset value
    if (!mode) {
        //Non-overlapping
        for (pos = 0;pos < 16;pos++) {
            temp = asc2_1608[c][pos];		 //Call 1608 font
            for (int t = 0;t < 8;t++) {
                if (temp & 0x01)
                    drawPoint(x + t, y + pos, color);//Draw a dot  
                else
                    drawPoint(x + t, y + pos, 0);
                temp >>= 1;
                x++;
            }
            x = x0;
            y++;
        }
    }
    else {
        //overlapping mode
        for (pos = 0;pos < 16;pos++) {
            temp = asc2_1608[c][pos];		 //Call 1608 font
            for (int t = 0;t < 8;t++) {
                if (temp & 0x01) drawPoint(x + t, y + pos, color);//Draw a dot   
                temp >>= 1;
            }
        }
    }
}



void showString(uint8_t x, uint8_t y, const char *p, uint16_t color) {
    while (*p != '\0') {
        if (x > LCD_W - 16) { x = 0;y += 16; }
        if (y > LCD_H - 16) { y = x = 0; fillAll(RED); }
        showChar(x, y, *p, 0, color);
        x += 8;
        p++;
    }
}


void showInt(uint8_t x, uint8_t y, int num, uint16_t color) {
    char str[10];
    sprintf(str, "%d", num);
    showString(x, y, str, color);
}


void showFloat(uint8_t x, uint8_t y, float num, uint16_t color) {
    char str[10];
    sprintf(str, "%f", num);
    showString(x, y, str, color);
}