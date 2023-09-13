// build this program:
// g++ main.cpp -o ppmImage

// then run: 
// ./ppmImage > image.ppm

// this uses the new header files for more efficient calculations:
#include <iostream>
#include "color.h"
#include "vec3.h"

int main() {
    // Generate a PPM image:
    int imageWidth{256};
    int imageHeight{256};

    // Render the image
    // P3 in PPM format means use ASCII format, 255 means max for a channel
    std::cout<<"P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i{0}; i < imageHeight; i++) {
        // write to log, since we are saving to a file using std out
        // flush so that its a single line being updated, wont overrun the terminal with new lines
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
        for (int j{0}; j < imageWidth; j++) {
            // OLD METHOD:
            // auto r = double(i) / (imageWidth-1);
            // auto g = double(j) / (imageHeight-1);
            // auto b = 0;

            // int ir = static_cast<int>(255.999 * r);
            // int ig = static_cast<int>(255.999 * g);
            // int ib = static_cast<int>(255.999 * b);

            // NEW METHOD WITH HEADER FILES:
            auto pixel_color = color(double(i) / (imageWidth-1), double(j) / (imageHeight-1), 128);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}