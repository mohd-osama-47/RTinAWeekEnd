// Goal is to calculate surface normals for shading
// Normals are vectors perpendicular to the surface at intersection point

// for a spehere:
// an outward normal vector is in the direction of the hit point MINUS the center:
// norm = P - C

#include "../3Vec3Class/vec3.h"
#include "../3Vec3Class/color.h"
#include "../4Rays/ray.h"
#include "sphere.h"

#include <iostream>

double hit_sphereOLD(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - (radius * radius);
    auto discriminant = b*b - (4*a*c);
    
    // return (discriminant >= 0);
    // instead, compute normal:
    if (discriminant < 0) {
        return -1.0;    // complex root
    }
    else {
        return (-b - sqrt(discriminant)) / (2.0*a); // get the smaller root (- not + in the quad formula)
    }
}

// optimized and cleaned up hit_sphere
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - (a*c);
    
    if (discriminant < 0) {
        return -1.0;    // complex root
    }
    else {
        return (-half_b - sqrt(discriminant)) / a; // get the smaller root (- not + in the quad formula)
    }
}

color ray_color(const ray& r) {
    // instead of just drawing a sphere, visualize surface normals:
    double t = hit_sphere(point3(0,0,-1), 0.25, r);
    if ( t > 0.0 ) {
        // get surface normal relative to sphere centered at (0,0,-1)
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0); // shift range from [-1,1] to [0,1]
    // based on the y-coordinate, return a new color
    return (1 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    // return (1 - a) * color(1.0, 1.0, 1.0) + a * color(0.8, 0, 0);
}


int main () {
    //! IMAGE INFO
    auto aspect_ratio = 16.0/9.0;
    int image_width = 500;

    //get the image height, ensuring its atleast 1
    int image_height = static_cast<int> (image_width / aspect_ratio);

    image_height = (image_height < 1)? 1 : image_height;


    //! CAMERA DETAILS
    auto focal_length = 1.0;
    auto viewport_height = 2.0; // choose an arbitrary viewport height of 2.0

    // the actual ratio between image_width and image_height can vary,
    // for view port calculate the actual thing
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    // origin at (0,0,0), y is up, x is right, -z towards viewing direction
    point3 camera_center(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u(viewport_width, 0, 0);
    vec3 viewport_v(0, -viewport_height, 0); // - since the direction is flipped!

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // to aid in traversing the viewport:
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // get the location of the upper left pixel:
    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    
    //! RENDER
    // generate the image:
    std::cout<<"P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j{0}; j < image_height; j++) {
        std::clog << "\rLines Remaining: " << image_height - j << ' ' << std::flush;
        for (int i{0}; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

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
