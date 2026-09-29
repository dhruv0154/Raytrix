#include "math/color.h"

#include <iostream>

int main() {
    int imageWidth = 256;
    int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto r = double(i) / (imageWidth - 1);
            auto g = double(j) / (imageHeight - 1);
            auto b = 0.0f;

            color pixelColor = color(r, g, b);
            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}