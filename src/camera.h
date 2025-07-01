#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include <cmath>
#include <cstdlib>

using namespace std;

inline float randf() {
    return rand() / (RAND_MAX + 1.0f);
}

struct Camera {
    vec3 position;
    vec3 right, up, forward;
    float fov = 1.0f;
    float aperture = 0.0f;    // 光圈半径 / Aperture radius
    float focus_dist = 1.0f;  // 焦点距离 / Focus distance

    Camera(const vec3& pos = {0, 0, 0}, const vec3& look_at = {0, 0, -1},
           float fov_ = 1.0f, 
           float aperture_ = 0.0f, float focus_ = 1.0f) 
        : position(pos), fov(fov_), aperture(aperture_), focus_dist(focus_) {        
        this->forward  = (look_at - pos).normalized();
        this->right    = cross(forward, vec3{0, 1, 0}).normalized();
        this->up       = cross(right, forward).normalized();
    }

    //cam.pos2curpixel
    vec3 get_ray_dir(int pix, int width, int height) const {
        int i = pix % width;
        int j = pix / width;
        float dir_x =  (i + 0.5f) - width / 2.f;
        float dir_y = -(j + 0.5f) + height / 2.f;
        float dir_z = height / (2.f * tan(fov / 2.f));
        return (forward * dir_z + right * dir_x + up * dir_y).normalized();
    }

    // This seems better
    // 标准透视锥体,但我还不懂,所以不用
    // vec3 get_ray_dir(float u, float v, float aspect_ratio) const {
    //     float x = (2.0f * u - 1.0f) * aspect_ratio * tan(fov / 2.0f);
    //     float y = (1.0f - 2.0f * v) * tan(fov / 2.0f);
    //     vec3 dir = (forward + x * right + y * up).normalized();
    //     return dir;
    // }

    // 带景深的光线生成函数：光圈扰动发射点，指向焦平面
    // DOF-enabled ray: jitter origin inside aperture, aim at focus plane
    void get_ray_with_dof(int pix, int width, int height, vec3& ray_orig, vec3& ray_dir) const {
        vec3 base_dir = get_ray_dir(pix, width, height);

        // 光圈随机偏移（在 XY 平面内）
        float r1 = randf(), r2 = randf();
        float theta = 2.0f * M_PI * r1;
        float radius = aperture * sqrt(r2);
        float dx = radius * cos(theta);
        float dy = radius * sin(theta);
        vec3 offset = right * dx + up * dy;

        vec3 focus_point = position + base_dir * focus_dist;
        ray_orig = position + offset;
        ray_dir = (focus_point - ray_orig).normalized();
    }
};

#endif
