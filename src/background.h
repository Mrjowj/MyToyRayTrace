#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "vec3.h"
#include <string>

struct Background {
    vec3 color; // fallback color
    unsigned char* image_data = nullptr;
    int width = 0, height = 0, channels = 0;

    // 返回背景颜色（根据ray方向计算贴图坐标）
    vec3 sample(const vec3& dir) const {
        if (!image_data) return color;

        vec3 d = dir.normalized();
        float phi = atan2(d.z, d.x);
        float theta = acos(d.y);
        float u = (phi + M_PI) / (2 * M_PI);
        float v = theta / M_PI;

        int x = std::min(int(u * width), width - 1);
        int y = std::min(int(v * height), height - 1);
        int idx = (y * width + x) * 3;

        return vec3{
            image_data[idx]     / 255.f,
            image_data[idx + 1] / 255.f,
            image_data[idx + 2] / 255.f
        };
    }
};

#endif
