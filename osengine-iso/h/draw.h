// font8x8_basic jest zdefiniowane tylko raz w 8x8.cpp lub framebuffer.cpp!
#include <stdint.h>
#include "structs.h"

extern uint8_t font8x8_basic[128][8];

void draw_char8x8(uint32_t *fb, int fb_width, int fb_height, int x, int y, uint8_t c, uint32_t color);

void draw_string8x8(uint32_t *fb, int fb_width, int fb_height, int x, int y, const char *str, uint32_t color);

void draw_image(uint32_t *fb, int fb_width, int fb_height, int x, int y, const Image &img);
