#include "display.h"
#include "assets.h"
#include "font.h"
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "string.h"
#include "defines.h"
#include "3D/camera.h"

Color framebuffer[LCD_SIZE];
Depth zbuffer[NUM_BLOCKS];
uint8_t zorder[NUM_BLOCKS];

void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const Color* img) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            drawPoint(x + j, y + i, img[i * w + j]);
    }
}

void drawImageMask(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const Color *img, uint64_t mask) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            if ((mask >> (i * w + j)) & 1)
                drawPoint(x + j, y + i, img[i * w + j]);
    }
}

void drawBlock(int i, int j, int imageID) {
    drawImage(j * BLOCK_WIDTH, i * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, blockImage[imageID]);
}

void refresh(void) {
    lcd_write_u16(0, 0, 160, 80-1, (void *)framebuffer);
}

void clear(void) {
    memset(framebuffer, 0, sizeof(framebuffer));
}

void displaySteps(int steps) {
    static int last_steps;
    if (steps == last_steps)
        return;
    char str[21];
    sprintf(str, "%20d", last_steps);
    drawString(0, 10, str, BLACK);
    sprintf(str, "%20d", steps);
    drawString(0, 10, str, WHITE);
    last_steps = steps;
}

void diplsayLevel(int level) {
    char str[15];
    sprintf(str, "Level: %d", level);
    drawString(0, 10, str, WHITE);
}

/**************************************************************/

void drawPoint(uint8_t x, uint8_t y, Color color) {
    framebuffer[y * LCD_W + x] = color;
}


void fillArea(uint8_t xsta, uint8_t ysta, uint8_t xend, uint8_t yend, Color color) {
    for (uint8_t y = ysta; y < yend; y++)
        for (uint8_t x = xsta; x < xend; x++)
            drawPoint(x, y, color);
}

void fillAll(Color color) {
    fillArea(0, 0, LCD_W, LCD_H, color);
}

void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        drawPoint(x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}



void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color) {
    drawLine(x1, y1, x2, y1, color);
    drawLine(x1, y1, x1, y2, color);
    drawLine(x1, y2, x2, y2, color);
    drawLine(x2, y1, x2, y2, color);
}


void fillTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3) {
    uint8_t min_x = min(min(x1, x2), x3);
    // TODO: 

}


void drawCircle(uint8_t x0, uint8_t y0, uint8_t r, Color color) {
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


void drawChar(uint8_t x, uint8_t y, char c, Color color) {
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


void drawChar2(uint8_t x, uint8_t y, char c, Color color) {
    int num = c - ' ';
    for (int pos = 0; pos < 16; pos++) {
        uint8_t temp = asc2_1608[num][pos];
        for (int t = 0; t < 8; t++) {
            drawPoint(x + pos / 2, y - t + 8 * (1 + pos % 2), (temp & 1) ? color : 0);
            temp >>= 1;
        }
    }
}


void drawString(uint8_t x, uint8_t y, const char *p, Color color) {
    while (*p != '\0') {
        if (x > LCD_W - 8) { x = 0;y += 16; }
        if (y > LCD_H - 16) { y = x = 0; fillAll(RED); }
        drawChar(x, y, *p, color);
        x += 8;
        p++;
    }
}


void drawString2(uint8_t x, uint8_t y, const char *p, Color color) {
    while (*p != '\0') {
        if (x > LCD_W - 8) { x = 0;y += 16; }
        if (y > LCD_H - 16) { y = x = 0; fillAll(RED); }
        drawChar2(x, y, *p, color);
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

void drawInt2(uint8_t x, uint8_t y, int num, uint16_t color) {
    char str[10];
    sprintf(str, "%d", num);
    drawString2(x, y, str, color);
}


void drawIntCenter(uint8_t y, int num, uint16_t color) {
    char str[10];
    sprintf(str, "%d", num);
    drawStringCenter(y, str, color);
}


void drawFloat(uint8_t x, uint8_t y, float num, uint16_t color) {
    char str[20];
    // TODO fix
}


void init_buffer() {
    /* init zorder */
    for (int i = 0; i < NUM_BLOCKS; i++) {
        zorder[i] = i;
    }
    /* init zbuffer */
    for (int i = 0 ; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            Vec3 v = {{i + 0.5, j + 0.5, 0.5}};
            zbuffer[i * NUM_COLS + j] = world_to_camera(v).z * (1 << (8 * sizeof(Depth)));
        }
    }
    /* sort */
    for ( int i = 0; i < NUM_BLOCKS; i++)
        for (int j = i + 1; j < NUM_BLOCKS; j++)
            if (zorder[i] < zorder[j])
                swap(zorder[i], zorder[j]);
}