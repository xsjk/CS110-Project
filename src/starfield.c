#include "starfield.h"
#include "display.h"

uint32_t jenkins_mix_3(uint32_t a, uint32_t b, uint32_t c)
{
    a -= c; a ^= rot(c, 4); c += b;
    b -= a; b ^= rot(a, 6); a += c;
    c -= b; c ^= rot(b, 8); b += a;
    a -= c; a ^= rot(c,16); c += b;
    b -= a; b ^= rot(a,19); a += c;
    c -= b; c ^= rot(b, 4); b += a;
    return c;
}

uint32_t jenkins_mix_2(uint32_t a, uint32_t b)
{
    return jenkins_mix_3(a, b, 0xdeadbeef);
}

uint32_t jenkins_mix(uint32_t a)
{
    return jenkins_mix_3(a, 0x72837482, 0xdeadbeef);
}

// Random number generator based on Jenkins hash.

static uint32_t g_rnd_state = 0;
uint32_t rnd_u32(void)
{
    return jenkins_mix(g_rnd_state++);
}


Star g_stars[NUM_STARS];

// ------------------------------------------------------------------------

void update_star(Star* v, int delta)
{
    v->z -= delta;
    if (v->z <= 0 || v->p < 0)
    {
        v->x = rnd_u32();
        v->y = rnd_u32();
        v->z = 0x7fff;
    }

    int x = ((int)(v->x) << 16) / v->z;
    int y = ((int)(v->y) << 16) / v->z;

    x >>= 10;
    y >>= 10;

    x += LCD_W >> 1;
    y += LCD_H >> 1;
    if (x < 0 || x >= LCD_W || y < 0 || y >= LCD_H)
        v->p = -1;
    else
        v->p = x + LCD_W * y;
}

// ------------------------------------------------------------------------
