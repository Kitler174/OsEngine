#include <iostream>
#include <fstream>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace fs = std::filesystem;

// Funkcja do konwersji PNG -> BIN
void convertImages(const std::string& input_folder, const std::string& output_folder) {
    fs::create_directories(output_folder);

    for (const auto& entry : fs::directory_iterator(input_folder)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
            std::string input_path = entry.path().string();
            std::string filename = entry.path().stem().string();
            std::string output_path = output_folder + "/" + filename + ".bin";

            int width, height, channels;
            unsigned char* img = stbi_load(input_path.c_str(), &width, &height, &channels, 4);
            if (!img) {
                std::cerr << "Failed to load image: " << input_path << std::endl;
                continue;
            }

            std::ofstream out(output_path, std::ios::binary);
            if (!out.is_open()) {
                std::cerr << "Cannot open output file: " << output_path << std::endl;
                stbi_image_free(img);
                continue;
            }

            // Zapisujemy szerokość i wysokość na początku pliku
            out.write(reinterpret_cast<char*>(&width), sizeof(int));
            out.write(reinterpret_cast<char*>(&height), sizeof(int));

            // Zapisujemy dane pikseli
            out.write(reinterpret_cast<char*>(img), width * height * 4);
            out.close();
            stbi_image_free(img);

            std::cout << "Converted image: " << input_path << " -> " << output_path << std::endl;
        }
    }
}

// Funkcja do konwersji MP3 -> BIN
void convertMusic(const std::string& input_folder, const std::string& output_folder) {
    fs::create_directories(output_folder);

    for (const auto& entry : fs::directory_iterator(input_folder)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            std::string input_path = entry.path().string();
            std::string filename = entry.path().stem().string();
            std::string output_path = output_folder + "/" + filename + ".bin";

            std::ifstream in(input_path, std::ios::binary);
            if (!in.is_open()) {
                std::cerr << "Cannot open input file: " << input_path << std::endl;
                continue;
            }

            std::ofstream out(output_path, std::ios::binary);
            if (!out.is_open()) {
                std::cerr << "Cannot open output file: " << output_path << std::endl;
                continue;
            }

            out << in.rdbuf(); // kopiowanie bajt po bajcie
            in.close();
            out.close();

            std::cout << "Converted music: " << input_path << " -> " << output_path << std::endl;
        }
    }
}

int main() {
    std::string images_input = "a_main_images";
    std::string images_output = "osengine-iso/data/images";

    std::string music_input = "a_main_music";
    std::string music_output = "osengine-iso/data/music";

    std::cout << "Converting images..." << std::endl;
    convertImages(images_input, images_output);

    std::cout << "Converting music..." << std::endl;
    convertMusic(music_input, music_output);

    std::cout << "All files converted!" << std::endl;
    return 0;
}
