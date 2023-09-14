#ifndef RAY_H
#define RAY_H

#include "../3Vec3Class/vec3.h"

// @brief the basic ray class to build the ray tracer with!
class ray {
    public:
        // Constructors:
        ray() {}

        // represent a ray as P(t) = A + t*b
        // A = origin, b is ray direction, t is a real number that moves P in space
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        // getter functions
        point3 origin() const {return orig;}
        vec3 direction() const {return dir;}

        // calculate ray based on paramater t:
        point3 at(double t) const {
            return orig + t*dir;
            // r.origin() + t*r.direction()
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif