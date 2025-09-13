#pragma once
#include <stdint.h>
struct Image;
Image load_image_bin(const char* bin_path, int x, int y, uint32_t *fb);