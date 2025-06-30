// This file is the core of the project
// Description: Core rendering logic of the raytracer.
//              Includes ray tracing, reflection, refraction, and shading.
#ifndef RENDER_H
#define RENDER_H

#include "vec3.h"
#include "sphere.h"
#include "background.h"
#include "camera.h"
#include <cmath>
#include <tuple>
#include <vector>
using namespace std;
extern int depthMax; 

// Calculate reflection vector (Specular Reflection)
inline vec3 reflect(const vec3& I, const vec3& N) {
    return I - N * 2.f * (I * N);
}

// Snellの法則に基づく屈折ベクトルを計算する関数
// Calculate the refraction vector based on Snell's Law
//
// Parameters:
// - I: 入射方向ベクトル（単位ベクトル）
//      Incident direction vector
// - N: 表面の法線ベクトル（単位ベクトル）
//      Unit normal vector at the surface
// - eta_t: 出射媒質の屈折率（例：ガラスなら 1.5）
//          Refractive index of the transmission medium
// - eta_i: 入射媒質の屈折率（省略時は空気 = 1.0）
//          Refractive index of the incident medium
//
// 全反射の場合は無効なベクトル（{1, 0, 0}）を返す。
// Returns invalid vector ({1, 0, 0}) if total internal reflection occurs.
inline vec3 refract(const vec3& I, const vec3& N, float eta_t, float eta_i = 1.f) {
    float cosi = -max(-1.f, min(1.f, I * N));  // Cosine of incidence angle
    if (cosi < 0) return refract(I, -N, eta_i, eta_t); 

    float eta = eta_i / eta_t;                // 屈折率の比 / Ratio of refractive indices
    float k = 1 - eta * eta * (1 - cosi * cosi);  // 全反射の判定 / Discriminant for total internal reflection

    // k < 0 ⇒ 全反射/ Total internal reflection
    return k < 0 ? vec3{1, 0, 0} : I * eta + N * (eta * cosi - sqrt(k)); 
}

// Test if a ray intersects with any object in the scene
// 返回：是否命中、交点位置、法向量、材质
inline tuple<bool, vec3, vec3, Material> scene_intersect(
    const vec3& orig, const vec3& dir,
    const vector<Sphere>& spheres
) {
    vec3 pt, N;
    Material material;
    float nearest_dist = 1e10;

    // board floor 
    if (abs(dir.y) > 0.001f) {
        float d = -(orig.y + 4) / dir.y;
        vec3 p = orig + dir * d;
        if (d > 0.001f && d < nearest_dist && abs(p.x) < 10 && p.z < -10 && p.z > -30) {
            nearest_dist = d;
            pt = p;
            N = {0, 1, 0};
            bool checker = (int(0.5f * pt.x + 1000) + int(0.5f * pt.z)) % 2;
            material.diffuse_color = checker ? vec3{0.3, 0.3, 0.3} : vec3{0.3, 0.2, 0.1};
        }
    }

    // spheres
    for (const Sphere& s : spheres) {
        auto [hit, dist] = ray_sphere_intersect(orig, dir, s);
        if (hit && dist < nearest_dist) {
            nearest_dist = dist;
            pt = orig + dir * dist;
            N = (pt - s.center).normalized();
            material = s.material;
        }
    }

    return {nearest_dist < 1000, pt, N, material};
}

/*----------------- Recursive ray tracing -----------------*/ 
// Cast a ray from 'orig' in direction 'dir' and compute its resulting color.
inline vec3 cast_ray(
    const vec3& orig, const vec3& dir,
    const Camera& cam, 
    const vector<Sphere>& spheres,
    const vector<vec3>& lights,
    const Background& background,
    int depth = 0
) {
    if (depth > depthMax) return background.color;

    auto [hit, point, N, material] = scene_intersect(orig, dir, spheres);
    if (!hit) return background.sample(dir, cam.right, cam.up, cam.forward);

    // Compute and normalize reflection and refraction directions
    vec3 reflect_dir = reflect(dir, N).normalized();
    vec3 refract_dir = refract(dir, N, material.refractive_index).normalized();

    // ! important ! : Recursively trace reflected and refracted rays to get their resulting color.
    // 再帰的に追跡
    vec3 reflect_color = cast_ray(point, reflect_dir, cam, spheres, lights, background, depth + 1);
    vec3 refract_color = cast_ray(point, refract_dir, cam, spheres, lights, background, depth + 1);


    // Initialize diffuse and specular light intensity. Loop over each point light.
    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (const vec3& light : lights) {
        //若中途遇到遮挡物（即在阴影中），则跳过该光源的贡献
        vec3 light_dir = (light - point).normalized();
        auto [shadow_hit, shadow_pt, trashnrm, trashmat] = scene_intersect(point, light_dir, spheres);
        if (shadow_hit && (shadow_pt - point).norm() < (light - point).norm()) continue;
        
        // 漫反射 = 入射光与法向夹角的余弦值，取非负。
        diffuse_light_intensity += max(0.f, light_dir * N);

        // 高光 = 视线方向与光的反射方向的夹角余弦的 material.specular_exponent 次幂。
        specular_light_intensity += pow(max(0.f, -reflect(-light_dir, N) * dir), material.specular_exponent);
    }

    // 日：最終の色は、拡散反射・鏡面反射・反射・屈折の合成。albedo[] により各成分を重みづけ。
    // En: Final color is weighted sum of diffuse, specular, reflection, and refraction via albedo[].

    // diffuse
    return material.diffuse_color * diffuse_light_intensity * material.albedo[0]

    // specular
         + vec3{1.0f, 1.0f, 1.0f} * specular_light_intensity * material.albedo[1]

    // 再帰で得られた色
    // Reflection component — color seen from recursively tracing the reflected ray
         + reflect_color * material.albedo[2]

    // Refraction component — recursively computed color for rays passing through transparent materials
         + refract_color * material.albedo[3];
}

#endif
