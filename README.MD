# MyRaytracer Project

This project is inspired by ssloy's [TinyRaytracer Wiki](https://github.com/ssloy/tinyraytracer/wiki), which I studied in depth and restructured into a cleaner, more modularized version as part of my learning journey.

## Requirements

- C++17-compliant compiler (e.g. `g++`, `clang++`)
- OpenMP support (`-fopenmp`)
- No external dependencies — all required headers (`stb_image_write.h`, `json.hpp`) are included in this repo.

## How to Build (Linux / Windows)
```bash
g++ -std=c++17 -fopenmp -O2 -o myraytracer src/main.cpp
```

## How to Use
### Specify Maximum Recursion Depth
```bash
./myraytracer <depth>
```
### Use a JSON Scene Configuration File
```json
  "width": 1960,
  "height": 1440,
  "fov": 2,
  "background": [0.2, 0.7, 0.8],
  "lights": [
  ...
```
- You can define custom spheres, lights, resolution, etc. via a `scene.json`file.

# Project Goals

- **Refresh my C++ skills**: I haven't used C++ for over a year, so this project serves as a hands-on way to recover my coding proficiency.
  
- **Inprove my English Skill**: All code/Study Note will be commented in English to improve technical writing skills and prepare for future global collaboration.(Due to my current English level, some complex concepts may include brief Chinese notes(Or Japanese) for self-reference.)

- **UnderStand simpleRayTrace**: 
This project aims to help me deeply understand the core principles behind ray tracing, including ray-sphere intersection, shading models, reflection/refraction, and recursive rendering techniques. Through direct implementation, I hope to bridge the gap between theoretical knowledge and practical application.

---
## Docs
- Watch my docs 
  -> [here](Note.md)

*Maintained by: Mrjowj*
