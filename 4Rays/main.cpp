#include <iostream>

#include "../3Vec3Class/color.h"
#include "../3Vec3Class/vec3.h"
#include "ray.h"

// returns the color for a given scene ray
color ray_color(const ray& r) {
    // generate a linear interpolation from white to blue:
    // blendedValue = (1−a) ⋅ startValue[white] + a⋅endValue[blue]
    // a from 0 to 1

    // getting the unit vector generates a horizontal AND vertical
    // gradient! if r is not normalized you will only get a vertical gradient
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0); // shift range from [-1,1] to [0,1]
    // based on the y-coordinate, return a new color
    // return (1 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    return (1 - a) * color(1.0, 1.0, 1.0) + a * color(0, 0, 0);
}

int main () {
    // IMAGE INFO
    // generate a fixed aspect ration and width,
    // calculate height based on that
    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;

    //get the image height, ensuring its atleast 1
    int image_height = static_cast<int> (image_width / aspect_ratio);

    image_height = (image_height < 1)? 1 : image_height;


    // CAMERA DETAILS
    auto focal_length = 1.0;
    // set up a virtual viewport, which is a virtual rectangle in a 3D world
    // containing the grid of image pixel locations 
    
    // The distance between two adjacent pixels is called 
    // the pixel spacing, and square pixels is the standard. 
    auto viewport_height = 2.0; // choose an arbitrary viewport height of 2.0

    // the actual ratio between image_width and image_height can vary,
    // for view port calculate the actual thing
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    // now, generate the camera center.
    // camera (eye point): 3D point in space, origin of all scene rays

    // The vector from the camera center to the viewport center will be 
    // **orthogonal** to the viewport

    // initially set the distance between the viewport and the camera center
    //  point to be one unit. This distance is often referred to as the **focal length**.

    // origin at (0,0,0), y is up, x is right, -z towards viewing direction
    point3 camera_center(0, 0, 0);
    // or, alternatively:
    // auto camera_center = point3(0, 0, 0);

    // image goes from top to bottom, left to right, y is opposite of camera!
    // will generate two vectors, left to right (Vu), right to left (Vv)
    // and inset traversal by half pixel-to-pixel distance

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u(viewport_width, 0, 0);
    vec3 viewport_v(0, -viewport_height, 0); // - since the direction is flipped!

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // to aid in traversing the viewport:
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // get the location of the upper left pixel:
    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // since the first pixel is offset by half delta_u and delta_v:
    point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // generate the image:
    std::cout<<"P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j{0}; j < image_height; j++) {
        std::clog << "\rLines Remaining: " << image_height - j << ' ' << std::flush;
        for (int i{0}; i < image_width; i++) {
            // go left to right, top to bottom
            // i is horizontal, j is vertical
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            // std::clog << ray_direction << std::endl;

            // generate a ray from camera center to the current pixel
            ray r(camera_center, ray_direction);

            // get color to represent ray from camera to pixel
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone!                 \n";
    return 0;
}
