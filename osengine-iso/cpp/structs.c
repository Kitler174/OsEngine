#include <vector>

struct Image {
    int width;
    int height;
    vector<uint32_t> pixels; // każdy piksel to 0xAARRGGBB
};