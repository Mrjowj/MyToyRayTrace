//This is the start of this project
//Dont forget operator function must enclose with { }

#ifndef VEC3_H
#define VEC3_H

#include <cmath>

// 3D Vector Struct
struct vec3 {
    float x = 0, y = 0, z = 0;

    //Access by index(dont forget the &)
    float& operator[](int i) {
        return i == 0 ? x : (i == 1 ? y : z);
    }

    const float& operator[](int i) const {
        return i == 0 ? x : (i == 1 ? y : z);
    }

    // add
    vec3 operator+(const vec3& v) const {
        return { x + v.x, y + v.y, z + v.z };
    }

    // sub
    vec3 operator-(const vec3& v) const {
        return { x - v.x, y - v.y, z - v.z };
    }

    // mul
    vec3 operator*(float v) const {
        return { x * v, y * v, z * v };
    }

    // Dot
    float operator*(const vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    vec3 operator-() const {
        return { -x, -y, -z };
    }

    // norm
    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalized len
    vec3 normalized() const {
        return (*this) * (1.f / norm());
    }
};

// Cross product
inline vec3 cross(const vec3& a, const vec3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

#endif 
