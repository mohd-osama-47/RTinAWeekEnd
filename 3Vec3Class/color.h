#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, color& pixel_color) {
    // print out each channel's color:
    // use getter functions for better data safety:
    out << static_cast<int>(255.999 * pixel_color.x()) <<  ' '
        << static_cast<int>(255.999 * pixel_color.y()) <<  ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif