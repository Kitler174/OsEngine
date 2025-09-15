#include "../../h/framebuffer.h"
#include "../h/image.h"


//##################################################################
// Loading image from linker and drawing it example:
//##################################################################
// extern uint8_t _binary_im1_bin_start[];
// extern uint8_t _binary_im1_bin_end[];
// uint8_t* img_start = _binary_im1_bin_start;
// size_t img_size = _binary_im1_bin_end - _binary_im1_bin_start;
// Image img = load_image_from_memory(img_start, img_size);
// draw_image(framebuffer, fb_width, fb_height, x, y, img);
//##################################################################
