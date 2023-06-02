#pragma once

#include <stdint.h>

typedef union {
    struct {
        int b: 5;
        int g: 6;
        int r: 5;
    };
    uint16_t c;
} RGB565;


typedef union {
    struct {
        int b: 3;
        int g: 3;
        int r: 2;
    };
    uint8_t c;
} RGB332;


typedef uint16_t Color;