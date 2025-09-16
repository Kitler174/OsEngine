#include "../../h/image.h"
extern unsigned char _binary_im1_bin_start[];
extern unsigned char _binary_im1_bin_end[];
    struct Ragnar {
    int health = 100;
    int speed = 20;
    int x = 20;
    int y = 20;
    Image Image = load_image_from_memory(_binary_im1_bin_start, _binary_im1_bin_end - _binary_im1_bin_start);
};
extern unsigned char _binary_im2_bin_start[];
extern unsigned char _binary_im2_bin_end[];
    struct Ragnar2 {
    int health = 100;
    int speed = 20;
    int x = 20;
    int y = 20;
    Image Image = load_image_from_memory(_binary_im2_bin_start, _binary_im2_bin_end - _binary_im2_bin_start);
};
