#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <regex>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace fs = std::filesystem;

// ============================
//  PNG -> BIN -> osengine-iso/data/images
// ============================
void convertImages(const std::string &input_folder, const std::string &output_folder)
{
    fs::create_directories(output_folder);

    for (const auto &entry : fs::directory_iterator(input_folder))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".png")
        {
            std::string input_path = entry.path().string();
            std::string filename = entry.path().stem().string();
            std::string output_path = output_folder + "/" + filename + ".bin";

            int width, height, channels;
            unsigned char *img = stbi_load(input_path.c_str(), &width, &height, &channels, 4);
            if (!img)
            {
                std::cerr << "Failed to load image: " << input_path << std::endl;
                continue;
            }

            std::ofstream out(output_path, std::ios::binary);
            if (!out.is_open())
            {
                std::cerr << "Cannot open output file: " << output_path << std::endl;
                stbi_image_free(img);
                continue;
            }

            out.write(reinterpret_cast<char *>(&width), sizeof(int));
            out.write(reinterpret_cast<char *>(&height), sizeof(int));
            out.write(reinterpret_cast<char *>(img), width * height * 4);
            out.close();
            stbi_image_free(img);

            std::cout << "Converted image: " << input_path << " -> " << output_path << std::endl;
        }
    }
}

// ============================
//  MP3 -> BIN -> osengine-iso/data/music
// ============================
void convertMusic(const std::string &input_folder, const std::string &output_folder)
{
    fs::create_directories(output_folder);

    for (const auto &entry : fs::directory_iterator(input_folder))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3")
        {
            std::string input_path = entry.path().string();
            std::string filename = entry.path().stem().string();
            std::string output_path = output_folder + "/" + filename + ".bin";

            std::ifstream in(input_path, std::ios::binary);
            if (!in.is_open())
            {
                std::cerr << "Cannot open input file: " << input_path << std::endl;
                continue;
            }

            std::ofstream out(output_path, std::ios::binary);
            if (!out.is_open())
            {
                std::cerr << "Cannot open output file: " << output_path << std::endl;
                continue;
            }

            out << in.rdbuf();
            in.close();
            out.close();

            std::cout << "Converted music: " << input_path << " -> " << output_path << std::endl;
        }
    }
}

// ============================
//  OSE -> CPP -> osengine-iso/data/ose
// ============================
void convertOSE()
{
    std::string path = "loops";

    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".ose")
        {
            std::ifstream in(entry.path());
            if (!in.is_open())
            {
                std::cerr << "Cant open file: " << entry.path() << std::endl;
                continue;
            }

            std::string outPath = "osengine-iso/data/ose/" + entry.path().stem().string() + ".cpp";
            std::ofstream out(outPath);
            if (!out.is_open())
            {
                std::cerr << "Cant save file: " << outPath << std::endl;
                continue;
            }

            std::string line;
            while (std::getline(in, line))
            {
                std::smatch m;

                // ============================
                // #imp -> #include
                // ============================
                std::regex reImp(R"(^#imp\s+(\w+);$)");
                if (std::regex_match(line, m, reImp))
                {
                    out << "#include \"../../h/" << m[1].str() << ".h\"\n";
                    continue;
                }

                // ============================
                // $characters / $enemies / other_structures
                // ============================
                std::regex reStruct(R"(^\$(\w+)(\|(\w+))?\s+(\w+)\.struct\s+as\s+(\w+);$)");
                if (std::regex_match(line, m, reStruct))
                {
                    std::string folder = m[1].str(); // np. characters
                    std::string subfolder = m[3].matched ? m[3].str() : "";
                    std::string structName = m[4].str();

                    std::string path = "../data/struct/" + folder;
                    if (!subfolder.empty())
                        path += "/" + subfolder;
                    path += "/" + structName + ".h";

                    out << "#include \"" << path << "\"\n";
                    continue;
                }
                out << line << "\n";
            }

            in.close();
            out.close();
            std::cout << "Converted " << entry.path() << " -> " << outPath << std::endl;
        }
    }
}
// ============================
// STRUCT -> h - > osengine-iso/data/struct
// ============================
void ConvertSTRUCT()
{
    std::string path = ".";

    for (auto it = fs::recursive_directory_iterator(path,
                                                    fs::directory_options::skip_permission_denied);
         it != fs::recursive_directory_iterator(); ++it)
    {
        if (it->is_directory())
        {
            std::string name = it->path().filename().string();
            if (!name.empty() && name[0] == '.')
            {
                it.disable_recursion_pending();
                continue;
            }
            if (name.rfind("osengine-iso", 0) == 0)
            {
                it.disable_recursion_pending();
                continue;
            }
            for (const auto &entry : fs::directory_iterator(it->path()))
                if (entry.is_regular_file() && entry.path().extension() == ".struct")
                {
                    std::string s = entry.path().string();
                    std::string suffix = ".struct";
                    if (s.size() >= suffix.size() &&
                        s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0)
                    {
                        s.erase(s.size() - suffix.size());
                    }

                    std::ifstream in(entry.path());
                    if (!in.is_open())
                    {
                        std::cerr << "Cant open file: " << s << std::endl;
                        continue;
                    }

                    std::string outPath = "osengine-iso/data/struct/" + s.erase(0, 2) + ".h";
                    std::cout << "Converted struct: " << entry.path().string().erase(0, 2) << " -> " << outPath << std::endl;
                }
        }
    }
}

// ============================
// MAIN
// ============================
int main()
{
    std::string images_input = "a_main_images";
    std::string images_output = "osengine-iso/data/images";

    std::string music_input = "a_main_music";
    std::string music_output = "osengine-iso/data/music";

    std::cout << "Converting images..." << std::endl;
    convertImages(images_input, images_output);
    std::cout << "################################" << std::endl
              << std::endl;
    std::cout << "Converting music..." << std::endl;
    convertMusic(music_input, music_output);
    std::cout << "################################" << std::endl
              << std::endl;
    std::cout << "Converting ose..." << std::endl;
    convertOSE();
    std::cout << "################################" << std::endl
              << std::endl;
    std::cout << "Converting struct..." << std::endl;
    ConvertSTRUCT();
    std::cout << "################################" << std::endl
              << std::endl;
    std::cout << "All files converted!" << std::endl;
    return 0;
}
