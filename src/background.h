#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "vec3.h"
#include <string>
using namespace std;

struct Background {
    vec3 color; // fallback color
    unsigned char* image_data = nullptr;
    int width = 0, height = 0, channels = 0;

    vec3 sample(const vec3& dir) const {
    if (!image_data) return color;

    // 使用世界方向 dir 直接计算球面坐标
    vec3 d = dir.normalized();

    // φ: azimuth angle (longitude), measured around Y axis, in range [-π, π]
    // 方位角，表示在水平面上绕 Y 轴旋转的角度
    float phi   = atan2(-d.z, d.x);    // be careful with '-d.z'

    // θ: polar angle (colatitude), angle from Y axis (up), in range [0, π]
    // 极角，表示与 Y 轴夹角
    float theta = acos(clamp(d.y, -1.f, 1.f));

    // 转换为 [0,1] 的 UV 坐标
    float u = (phi + M_PI) / (2 * M_PI);
    u = u + 0.25f;                        // + 0.25f to move to the center
    if (u >= 1.0f) u -= 1.0f;
    if (u < 0.0f)  u += 1.0f;

    float v = theta / M_PI;

    // UV coordinates to pixel coordinates (x, y)
    int x = min(int(u * width), width - 1);
    int y = min(int(v * height), height - 1);
    int idx = (y * width + x) * 3;

    return vec3{
        image_data[idx]     / 255.f,
        image_data[idx + 1] / 255.f,
        image_data[idx + 2] / 255.f
    };
}


    /*If you dont want rotate background with camPos, use this*/
    // // 返回背景颜色（根据ray方向计算贴图坐标）
    // // Return background color based on ray direction (sample from environment map)
    // vec3 sample(const vec3& dir, const vec3& right, const vec3& up, const vec3& forward) const {
    //     if (!image_data) return color;

    //     // Transform world-space direction into camera-local space
    //     // 将世界方向 dir 投影到相机局部空间
    //     vec3 d_cam = vec3{
    //         dir * right,
    //         dir * up,
    //         dir * forward
    //     }.normalized();

    //     float phi = atan2(-d_cam.z, d_cam.x); // careful the '-'

    //     float theta = acos(d_cam.y);

    //     // UV coordinates
    //     float u = (phi + M_PI) / (2 * M_PI);
    //     float v = theta / M_PI;

    //     int x = min(int(u * width), width - 1);
    //     int y = min(int(v * height), height - 1);
    //     int idx = (y * width + x) * 3;

    //     return vec3{
    //         image_data[idx]     / 255.f,
    //         image_data[idx + 1] / 255.f,
    //         image_data[idx + 2] / 255.f
    //     };
    // }
};

#endif
