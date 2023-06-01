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