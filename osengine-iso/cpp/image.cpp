#include <cstdint>
#include <cstring> 
#include "../h/structs.h"
#include <cstddef>
#include <cstdlib>  

// ##################################################################
//  Load image from memory buffer
// ##################################################################
Image load_image_from_memory(const uint8_t *data, size_t size)
{
    Image img;
    img.width = 0;
    img.height = 0;
    img.pixels = nullptr;

    if (size < 8)
        return img;

    int width = 0, height = 0;
    std::memcpy(&width, data, 4);  
    std::memcpy(&height, data + 4, 4);  

    size_t expected_size = 8 + width * height * 4;
    if (size < expected_size)
        return img;

    img.width = width;
    img.height = height;

    img.pixels = (uint32_t *)malloc(width * height * sizeof(uint32_t));
    if (!img.pixels) {
        img.width = 0;
        img.height = 0;
        return img;
    }

    for (size_t i = 0; i < width * height; ++i) {
        uint32_t pixel = 0;
        std::memcpy(&pixel, data + 8 + i * 4, 4);
        img.pixels[i] = pixel;
    }

    return img;
}
