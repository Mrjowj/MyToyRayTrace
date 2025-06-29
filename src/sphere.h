// Sphere structure
#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "material.h"
#include <tuple>

// We only need a center point and Radius to discribe a sphere.
struct Sphere {
    vec3 center;
    float radius;
    Material material;

    Sphere(const vec3& c, float r, const Material& m)
    : center(c), radius(r), material(m) {}
};

// Check if a ray intersects with a sphere
// para：o(orig) = ray origin point(cam pos)
//       dir     = ray direction（normalized）
//       s       =  target sphere
// Return value: tuple<intersection found, hit distance>
inline std::tuple<bool, float> ray_sphere_intersect(const vec3& orig, const vec3& dir, const Sphere& s) {
    vec3 o2s = s.center - orig;           // cam -> sphere center
    float tca = o2s * dir;                // t (closest approach), Projected length on the ray
    float d2 = o2s * o2s - tca * tca;     // 最近点到球心的距离平方 / Closest distance squared
    float r2 = s.radius * s.radius;       // Squaring is much faster than computing sqrt


    if (d2 > r2) return {false, 0};       // No intersection

    //if intersect, than check the position 
    float thc = std::sqrt(r2 - d2);       // 半弦长,从射线最近点到球体表面交点之间的距离 / Half chord 
    float t0 = tca - thc;
    float t1 = tca + thc;

    // 返回最近的正交点 / Return the nearest valid intersection
    if (t0 > 0.001f) return {true, t0};
    if (t1 > 0.001f) return {true, t1};
    return {false, 0};
}

#endif 
