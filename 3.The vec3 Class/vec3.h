#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>


class vec3 {
    public:
        double e[3];

        //constructor
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

        // retrieval functions
        // const ensures compiler will raise an error if any data is manipulated
        // inside those functions:
        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        // define operator functions:
        
        // - operator
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        
        // [] operator
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }
        
        // += operator
        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }
        
        // *= operator
        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        // /= operator
        vec3& operator/=(double t) {
            // make use of the *= defined before:
            return *this *= 1 / t;
        }

        // retrieve vector length of vec3 object
        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }
};

// generate a point3 version of vec3 to represent points in space:
using point3 = vec3;

// utility functions for vectors:

// print to std out
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// vector addition
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// vector subtraction
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// vector multiplication
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// vector & scalar multiplication
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
// in case the user flips the order, just reuse what was written before as an overload:
inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

// vector & scalar division
inline vec3 operator/(vec3& u, double t) {
    return (1/t) * u;
}

// vector dot product
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// vector cross product
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// unit vector
inline vec3 unit_vector(vec3& u) {
    return u / u.length();
}

#endif