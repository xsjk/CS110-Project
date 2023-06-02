#include "button.h"
#include "gd32vf103_libopt.h"

#define DELAY 2000
uint64_t lastPressed[] = {0, 0, 0, 0, 0, 0};

/* -----------------------------
 Description: Return 1 if button number ch is pressed
                          Return 0 otherwise
----------------------------- */
static inline int getButtonRaw(int ch) {
  return (gpio_input_bit_get(ch != GPIO_PIN_13 ? GPIOA : GPIOC, ch));
}

// getButtonRaw with debouncing
int getButton(int ch) {
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
    else if (ch == BOOT_0 && time - lastPressed[5] > DELAY) {
        return lastPressed[5] = time, 1;
    }
  }
  return 0;
}

void button_init(void) {
  rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOC);
  gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6);
  gpio_init(GPIOC, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
}