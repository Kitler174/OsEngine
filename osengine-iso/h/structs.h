#pragma once
#include <vector>
#include <cstdint>

struct Image {
    int width;
    int height;
    std::vector<uint32_t> pixels;
};
