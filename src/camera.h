#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

struct Camera {
    vec3 position;
    vec3 forward;
    vec3 right;
    vec3 up;

    // 显式构造函数：给定 position 和 look_at 向量
    Camera(const vec3& pos, const vec3& look_at) {
        position = pos;
        forward = (look_at - pos).normalized();
        right   = cross(forward, vec3{0, 1, 0}).normalized();
        up      = cross(right, forward).normalized();
    }
};

#endif // CAMERA_H
