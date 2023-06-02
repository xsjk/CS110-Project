#include "button.h"
#include "lcd.h"
#include "gui.h"

int main(void) {
    lcd_init();        // init LCD
    button_init();

    guiUpdate();
    return 0;
}