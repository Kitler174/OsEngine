#include <cstdint>
#include "../h/8x8.h"
#include "../h/structs.h"
// ##################################################################
//  Draw single character using 8x8 font at (x, y) position on framebuffer
// ##################################################################
void draw_char8x8(uint32_t *fb, int fb_width, int fb_height, int x, int y, uint8_t c, uint32_t color)
{
    if ((unsigned char)c > 127)
        return;
    for (int row = 0; row < 8; ++row)
    {
        unsigned char bits = font8x8_basic[(uint8_t)c][row];
        for (int col = 0; col < 8; ++col)
        {
            if (bits & (1 << col))
            {
                int px = x + col;
                int py = y + row;
                if (px >= 0 && px < fb_width && py >= 0 && py < fb_height)
                {
                    fb[py * fb_width + px] = color;
                }
            }
        }
    }
}

// ##################################################################
//  Draw string using 8x8 font at (x, y) position on framebuffer
// ##################################################################
void draw_string8x8(uint32_t *fb, int fb_width, int fb_height, int x, int y, const char *str, uint32_t color)
{
    int cx = x;
    while (*str)
    {
        draw_char8x8(fb, fb_width, fb_height, cx, y, *str, color);
        cx += 8;
        ++str;
    }
}

// ##################################################################
//  Draw image (ARGB8888) at (x, y) position on framebuffer
// ##################################################################
void draw_image(uint32_t *fb, int fb_width, int fb_height, int x, int y, const Image &img)
{
    for (int row = 0; row < img.height; ++row)
    {
        for (int col = 0; col < img.width; ++col)
        {
            int px = x + col;
            int py = y + row;

            if (px < 0 || py < 0 || px >= fb_width || py >= fb_height)
            {
                continue;
            }

            uint32_t color = img.pixels[row * img.width + col];
            fb[py * fb_width + px] = color;
        }
    }
}
