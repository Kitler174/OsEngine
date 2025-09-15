#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include "../h/structs.h"
using namespace std;

Image load_image_bin(const char* bin_path) {
    Image img;
    ifstream in(bin_path, std::ios::binary);

    // szerokość i wysokość
    in.read(reinterpret_cast<char*>(&img.width), sizeof(int));
    in.read(reinterpret_cast<char*>(&img.height), sizeof(int));

    // wczytujemy surowe RGBA
    vector<unsigned char> raw(img.width * img.height * 4);
    in.read(reinterpret_cast<char*>(raw.data()), raw.size());

    // konwersja RGBA → uint32_t (ARGB8888)
    img.pixels.resize(img.width * img.height);
    for (int i = 0; i < img.width * img.height; i++) {
        uint8_t r = raw[i * 4 + 0];
        uint8_t g = raw[i * 4 + 1];
        uint8_t b = raw[i * 4 + 2];
        uint8_t a = raw[i * 4 + 3];

        img.pixels[i] = (a << 24) | (r << 16) | (g << 8) | (b);
    }

    return img;
}