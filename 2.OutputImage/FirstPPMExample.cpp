// build this program:
// g++ FirstPPMExample.cpp -o ppmImage

// then run: 
// ./ppmImage > image.ppm

#include <iostream>

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
            // auto r = 0;
            // auto g = 0;
            // auto b = double(i+2*j) / (imageWidth-1 + imageHeight-1);

            auto r = double(i) / (imageWidth-1);
            auto g = double(j) / (imageHeight-1);
            auto b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}