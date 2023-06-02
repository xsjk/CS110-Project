#include "starfield.h"
#include "display.h"

uint32_t jenkins_mix_3(uint32_t a, uint32_t b, uint32_t c) {
    a -= c; a ^= rot(c, 4); c += b;
    b -= a; b ^= rot(a, 6); a += c;
    c -= b; c ^= rot(b, 8); b += a;
    a -= c; a ^= rot(c, 16); c += b;
    b -= a; b ^= rot(a, 19); a += c;
    c -= b; c ^= rot(b, 4); b += a;
    return c;
}

uint32_t jenkins_mix_2(uint32_t a, uint32_t b) {
    return jenkins_mix_3(a, b, 0xdeadbeef);
}

uint32_t jenkins_mix(uint32_t a) {
    return jenkins_mix_3(a, 0x72837482, 0xdeadbeef);
}

// Random number generator based on Jenkins hash.

uint32_t g_rnd_state = 0;
uint32_t rnd_u32(void) {
    return jenkins_mix(g_rnd_state++);
}


Star g_stars[NUM_STARS];

// ------------------------------------------------------------------------

void update_star(Star *v, int delta) {
    v->z -= delta;
    if (v->z <= 0 || v->p < 0) {
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


static uint16_t bgcolxy(int x, int y) {
    x -= LCD_W >> 1;
    y -= LCD_H >> 1;
    y <<= 1;
    int r = x*x + y*y;
    return r >> 11;
}

static uint16_t bgcol(int p)
{
    int y = p / LCD_W;
    int x = p - y * LCD_W;
    return bgcolxy(x, y);
}


void update_stars(void) {

    for (int i = 0; i < NUM_STARS; i++) {
        Star *s = &g_stars[i];
        if (s->p >= 0) {
            uint16_t color = bgcol(s->p);
            int x = s->p % LCD_W;
            int y = s->p / LCD_W;
            drawPoint(x, y, color);
            // drawPoint(x + 1, y, color);
            // drawPoint(x, y+1, color);
            // drawPoint(x+1, y+1, color);
        }
        update_star(s, 10);
        if (s->p >= 0) {
            int g = (0x7fff - s->z) >> 9;
            if (g > 31) g = 31;
            int r = g >> 1;

            // framebuffer[s->p] += (r << 11) | (g << 5) | r;
            int x = s->p % LCD_W;
            int y = s->p / LCD_W;
            uint16_t color = (r << 11) | (g << 5) | r;
            drawPoint(x, y, color);
            // drawPoint(x + 1, y, color);
            // drawPoint(x, y+1, color);
            // drawPoint(x+1, y+1, color);

        }
    }
}