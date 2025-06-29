#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

// Material definition, pls read the doc to understand
struct Material {
    float refractive_index = 1.0f;     // 折射率 / Refractive index
    float albedo[4] = {1, 0, 0, 0};    // 反射属性数组：漫反射、镜面、反射、折射 / Albedo components: diffuse, specular, reflection, refraction
    vec3 diffuse_color = {0, 0, 0};    // 漫反射颜色 / Base diffuse color
    float specular_exponent = 0.0f;    // 镜面高光指数 / Specular exponent
};

// Common predefined materials
constexpr Material ivory = {
    1.0f,
    {0.9f, 0.5f, 0.1f, 0.0f},
    {0.4f, 0.4f, 0.3f},
    50.0f
};

constexpr Material glass = {
    1.5f,
    {0.0f, 0.9f, 0.1f, 0.8f},
    {0.6f, 0.7f, 0.8f},
    125.0f
};

constexpr Material red_rubber = {
    1.0f,
    {1.4f, 0.3f, 0.0f, 0.0f},
    {0.3f, 0.1f, 0.1f},
    10.0f
};

constexpr Material mirror = {
    1.0f,
    {0.0f, 16.0f, 0.8f, 0.0f},
    {1.0f, 1.0f, 1.0f},
    1425.0f
};

constexpr Material gold = {
    1.0f,
    {0.5f, 0.8f, 0.3f, 0.0f},
    {1.0f, 0.843f, 0.0f},
    300.0f
};

constexpr Material emerald = {
    1.3f,
    {0.1f, 0.3f, 0.0f, 0.6f},
    {0.314f, 0.784f, 0.471f},
    75.0f
};

constexpr Material steel = {
    1.0f,
    {0.2f, 1.0f, 0.5f, 0.0f},
    {0.6f, 0.6f, 0.7f},
    800.0f
};

constexpr Material ice = {
    1.31f,
    {0.1f, 0.3f, 0.1f, 0.9f},
    {0.9f, 0.95f, 1.0f},
    250.0f
};

#endif // MATERIAL_H
