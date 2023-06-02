#pragma once

#include <stdint.h>

#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))
#define swap(a,b) do { a+=b; b=a-b; a-=b; } while(0)

uint32_t jenkins_mix_3(uint32_t a, uint32_t b, uint32_t c);

uint32_t jenkins_mix_2(uint32_t a, uint32_t b);

uint32_t jenkins_mix(uint32_t a);

// Random number generator based on Jenkins hash.

static uint32_t g_rnd_state;
uint32_t rnd_u32(void);

typedef struct {
    int16_t x, y, z, p;
} Star;

enum { NUM_STARS = 400 };
Star g_stars[NUM_STARS];

void update_star(Star* v, int delta);