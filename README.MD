# MyRaytracer Project

This project is based on the [TinyRaytracer Wiki by ssloy](https://github.com/ssloy/tinyraytracer/wiki), which I’m using as a learning reference.

## Requirements

- C++17-compliant compiler (e.g. `g++`, `clang++`)
- OpenMP support (`-fopenmp`)
- No external dependencies — all required headers (`stb_image_write.h`, `json.hpp`) are included in this repo.

## How to Build (Linux / Windows)
```bash
g++ -std=c++17 -fopenmp -O2 -o raytracer src/main.cpp
```

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
