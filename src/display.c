#include "display.h"
#include "assets.h"
#include "lcd/lcd.h"

void drawBlock(int i, int j, int imageID) {
    for (int ii = 0; ii < IMAGE_HEIGHT; ii++) {
        for (int jj = 0; jj < IMAGE_WIDTH; jj++) {
            framebuffer[(i*IMAGE_HEIGHT + ii)*LCD_W + (j*IMAGE_WIDTH + jj)] = images[imageID][ii*IMAGE_WIDTH + jj];
        }
    }
}