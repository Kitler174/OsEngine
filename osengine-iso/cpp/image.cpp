#include <cstdint>
#include "../h/structs.h"
#include <cstddef>

// ##################################################################
//  Load image from memory buffer (simple custom format)
// ##################################################################
Image load_image_from_memory(const uint8_t *data, size_t size)
{
    Image img;

    if (size < sizeof(int) * 2)
    { // Minimal size width + height
        img.width = 0;
        img.height = 0;
        img.pixels = nullptr;
        return img;
    }

    // Loading width and height (first 8 bytes)
    img.width = *(const int *)data;
    img.height = *(const int *)(data + 4);

    size_t expected_size = 8 + img.width * img.height * 4;
    if (size < expected_size)
    { // Not enough data
        img.width = 0;
        img.height = 0;
        img.pixels = nullptr;
        return img;
    }

    // Pointing to pixel data (ARGB8888)
    img.pixels = (uint32_t *)(data + 8);

    return img;
}
