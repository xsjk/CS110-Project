#include "utils.h"
#include "gd32vf103_libopt.h"

#define DELAY 2000
uint64_t lastPressed[5] = {0, 0, 0, 0, 0};

/* -----------------------------
 Description: Return 1 if button number ch is pressed
                          Return 0 otherwise
----------------------------- */
int getButtonRaw(int ch) {
 /* hack for new board*/
  if (ch != GPIO_PIN_13)
    return (int)(gpio_input_bit_get(GPIOA, ch));
  else
    return (int)(gpio_input_bit_get(GPIOC, ch));
}

// getButtonRaw with debouncing
int Get_Button(int ch) {
  uint64_t time = get_timer_value() / 4000;
  if (getButtonRaw(ch)) {
    if (ch == JOY_LEFT && time - lastPressed[0] > DELAY) {
        return lastPressed[0] = time, 1;
    }
    else if (ch == JOY_RIGHT && time - lastPressed[1] > DELAY) {
        return lastPressed[1] = time, 1;
    }
    else if (ch == JOY_DOWN && time - lastPressed[2] > DELAY) {
        return lastPressed[2] = time, 1;
    }
    else if (ch == JOY_CTR && time - lastPressed[3] > DELAY) {
        return lastPressed[3] = time, 1;
    }
    else if (ch == BUTTON_1 && time - lastPressed[4] > DELAY) {
        return lastPressed[4] = time, 1;
    }
  }
  return 0;
}

/* -----------------------------
 Description: Return 1 if button BOOT0 ch is pressed
                          Return 0 otherwise
----------------------------- */
int Get_BOOT0(void) { return (int)(gpio_input_bit_get(GPIOA, GPIO_PIN_8)); }
