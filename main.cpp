#include <iostream>
#include <fstream>
#include <filesystem>
#include "lodepng.h"

namespace fs = std::filesystem;

void showHelp();

unsigned int decodeOneStep(const char *filename, std::vector<unsigned char> &image);

int main(int argc, const char *argv[]) {

    if (argc != 3) {
        showHelp();
        return 1;
    }

    std::vector<unsigned char> image;
    unsigned width, height;


    unsigned error = lodepng::decode(image, width, height, argv[1]);

    if (error) {
        std::cerr << "Decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        return 2;
    }

    std::ofstream output(argv[2]);

    if (!output) {
        std::cerr << "Problem writing \"" << argv[2] << "\" file" << std::endl;
        return 3;
    }

    auto name = fs::path(argv[2]).stem().string();

    output << ".text\n"
              ".global " << name << "\n" <<
           "\n" <<
           name << ":\n";

    output << "    .xword " << width << " \t// width\n";
    output << "    .xword " << height << " \t// height\n";


    for (int i = 0; i < image.size(); i += 4) {
        output << "    .byte 0x" << std::hex << std::setw(2) << std::setfill('0') << (int) image[i + 2] << "\t// B\n";
        output << "    .byte 0x" << std::hex << std::setw(2) << std::setfill('0') << (int) image[i + 1] << "\t// G\n";
        output << "    .byte 0x" << std::hex << std::setw(2) << std::setfill('0') << int( image[i]) << "\t// R\n";
        output << "    .byte 0x" << std::hex << std::setw(2) << std::setfill('0') << (int) image[i + 3] << "\t// A\n";
    }


    return 0;
}

void showHelp() {
    std::cout << "png2asm in_file.png  out_file.asm \n"
                 "\n"
                 "Both parameters are requiered.\n";
}
