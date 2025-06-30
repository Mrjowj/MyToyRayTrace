#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <unordered_map>
#include <omp.h> // OpenMP parallel rendering

// Third-party library 
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "include/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include "include/json.hpp"
using json = nlohmann::json;


#include "vec3.h"
#include "material.h"
#include "sphere.h"
#include "render.h"
#include "background.h"
#include "camera.h"

using namespace std;

int depthMax;

// argc = 2, argv[1] = depthMax
int main(int argc, char* argv[]) {
    depthMax = 4; 
    if (argc >= 2) {
        try {
            depthMax = stoi(argv[1]); 
            if (depthMax < 0 || depthMax > 100 ) {
                cerr << "Invalid depth. Must be >= 0.\n";
                return 1;
            }
        } catch (...) {
            cerr << "Usage: " << argv[0] << " <max_recursion_depth>\n";
            return 1;
        }
    }
    unordered_map<string, Material> material_map = {
        {"ivory",       ivory},
        {"glass",       glass},
        {"mirror",      mirror},
        {"red_rubber",  red_rubber},
        {"gold",        gold},
        {"emerald",     emerald},
        {"steel",       steel},
        {"ice",         ice}
    };

    // === Load configuration from JSON ===
    json config;
    ifstream in("scene.json");
    in >> config;

    int width  = config["width"];
    int height = config["height"];
    float fov  = config["fov"];

    vec3 camera_pos = {0, 0, 0};
    vec3 look_at = {0, 0, -1};
    if (config.contains("camera")) {
        auto cam = config["camera"];
        camera_pos = vec3{cam["position"][0], cam["position"][1], cam["position"][2]};
        look_at    = vec3{cam["look_at"][0],   cam["look_at"][1],   cam["look_at"][2]};
    }
    Camera cam(camera_pos, look_at);

    Background bg;
    bg.color = vec3{0.2f, 0.7f, 0.8f}; // color when failed to load any background
    if (config.contains("background")) {
        auto b = config["background"];
        if (b["type"] == "image" && b.contains("path")) {
            string path = b["path"];
            bg.image_data = stbi_load(path.c_str(), &bg.width, &bg.height, &bg.channels, 0);
            if (!bg.image_data) {
                cerr << "Failed to load envmap, fallback to color.\n";
            }
        }
        if (b.contains("default")) {
            auto d = b["default"];
            bg.color = vec3{d[0], d[1], d[2]};
        }
    }
    
    vector<vec3> framebuffer(width * height);

    vector<vec3> lights;
    for (auto& l : config["lights"]) {
        lights.push_back(vec3{l[0], l[1], l[2]});
    }

    vector<Sphere> spheres;
    for (auto& s : config["spheres"]) {
        vec3 center = {s["center"][0], s["center"][1], s["center"][2]};
        float radius = s["radius"];
        std::string mname = s["material"];

        Material m = material_map.count(mname) ? material_map[mname] : mirror;
        spheres.emplace_back(center, radius, m);
    }

/*------------------------ main(parallelized) -------------------------*/
    auto start_time = chrono::high_resolution_clock::now(); // Start timing
#pragma omp parallel for
    for (int pix = 0; pix < width * height; ++pix) {
        // 1dim 
        int i = pix % width;
        int j = pix / width;

        float dir_x =  (i + 0.5f) - width / 2.f;
        float dir_y = -(j + 0.5f) + height / 2.f;  // Flip vertically, careful
        float dir_z = height / (2.f * tan(fov / 2.f));

        //cam.pos2curpixel
        vec3 dir = (cam.forward * dir_z + cam.right * dir_x + cam.up * dir_y).normalized();

        // Cast a ray from cam in direction 'dir' and compute its resulting color.
        framebuffer[pix] = cast_ray(cam.position, dir, cam, spheres, lights, bg, 0);
    }

    auto end_time = chrono::high_resolution_clock::now(); // End timing
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Render time: " << duration << " ms" << endl;


/*------------------------------- save -------------------------------*/
    filesystem::create_directories("out");

    // Save framebuffer to .ppm file
    ofstream ofs("out/out.ppm", ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (const vec3& color : framebuffer) {
        float max_c = max(1.f, max(color[0], max(color[1], color[2])));
        for (int i = 0; i < 3; ++i) {
            ofs << (char)(255 * color[i] / max_c);
        }
    }
    ofs.close();

    // Save framebuffer to .png using stb_image_write
    vector<unsigned char> img_data(width * height * 3);
    for (int i = 0; i < width * height; ++i) {
        float max_c = max(1.f, max(framebuffer[i][0], max(framebuffer[i][1], framebuffer[i][2])));
        img_data[i * 3 + 0] = static_cast<unsigned char>(255 * framebuffer[i][0] / max_c);
        img_data[i * 3 + 1] = static_cast<unsigned char>(255 * framebuffer[i][1] / max_c);
        img_data[i * 3 + 2] = static_cast<unsigned char>(255 * framebuffer[i][2] / max_c);
    }
    stbi_write_png("out/out.png", width, height, 3, img_data.data(), width * 3);

    return 0;
}