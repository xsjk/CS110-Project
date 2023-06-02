#include "display.h"
#include "assets.h"
#include "font.h"
#include <stdio.h>
#include "lcd.h"
#include "string.h"

uint16_t framebuffer[LCD_SIZE];

void drawBlock(int i, int j, int imageID) {
    for (int ii = 0; ii < IMAGE_HEIGHT; ii++) {
        for (int jj = 0; jj < IMAGE_WIDTH; jj++) {
            framebuffer[(i * IMAGE_HEIGHT + ii) * LCD_W + (j * IMAGE_WIDTH + jj)] = images[imageID][ii * IMAGE_WIDTH + jj];
        }
    }
}

void refresh(void) {
    lcd_write_u16(0, 0, 160, 80, (void *)framebuffer);
}

void clear(void) {
    // for (int y = 0; y < LCD_H; y++)
    //     for (int x = 0; x < LCD_W; x++)
    //         // drawPoint(x, y, RED);
    //         framebuffer[y * LCD_W + x] = RED;
    // for (int i = 0; i < sizeof(framebuffer)/sizeof(*framebuffer); i++)
    //     framebuffer[i] = RED;

    memset(framebuffer, 0, sizeof(framebuffer));
}

void displayScore(int score) {
    char str[21];
    sprintf(str, "%20d", score);
    drawString(0, 0, str, WHITE);
}

void diplsayLevel(int level) {
    char str[15];
    sprintf(str, "Level: %d", level);
    drawString(0, 10, str, WHITE);
}

/**************************************************************/

void drawPoint(uint8_t x, uint8_t y, uint16_t color) {
    framebuffer[y * LCD_W + x] = color;
}


void fillArea(uint8_t xsta, uint8_t ysta, uint8_t xend, uint8_t yend, uint16_t color) {
    for (uint8_t y = ysta; y < yend; y++)
        for (uint8_t x = xsta; x < xend; x++)
            drawPoint(x, y, RED);
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


void drawChar(uint8_t x, uint8_t y, char c, uint16_t color) {
    int num = c - ' ';
    for (int pos = 0; pos < 16; pos++) {
        uint8_t temp = asc2_1608[num][pos];
        for (int t = 0; t < 8; t++) {
            if (temp & 1)
                drawPoint(x + pos / 2, y - t + 8 * (1 + pos % 2), color);
            temp >>= 1;
        }
    }
}



void drawString(uint8_t x, uint8_t y, const char *p, uint16_t color) {
    while (*p != '\0') {
        if (x > LCD_W - 8) { x = 0;y += 16; }
        if (y > LCD_H - 16) { y = x = 0; fillAll(RED); }
        drawChar(x, y, *p, color);
        x += 8;
        p++;
    }
}



void drawStringCenter(uint8_t y, const char *p, uint16_t color) {
    char str[21];
    sprintf(str, "%*s%s", (20 - strlen(p)) / 2, "", p);
    drawString(0, y, str, color);
}



void drawInt(uint8_t x, uint8_t y, int num, uint16_t color) {
    char str[10];
    sprintf(str, "%d", num);
    drawString(x, y, str, color);
}


void drawIntCenter(uint8_t y, int num, uint16_t color) {
    char str[10];
    sprintf(str, "%d", num);
    drawStringCenter(y, str, color);
}


void drawFloat(uint8_t x, uint8_t y, float num, uint16_t color) {
    char str[10];
    sprintf(str, "%f", num);
    drawString(x, y, str, color);
}