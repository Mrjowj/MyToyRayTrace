# MyRaytracer Project

This project is inspired by ssloy's [TinyRaytracer Wiki](https://github.com/ssloy/tinyraytracer/wiki), which I studied in depth and restructured into a cleaner, more modularized version as part of my learning journey.

## Project Preview
<figure>
  <img src="assets/sample_1.png" alt="sample" width="1920">
  <figcaption><b>Figure:</b> sample(forward)</figcaption>
  <br>
  <br>
  <img src="assets/sample_2.png" alt="sample" width="1920">
  <figcaption><b>Figure:</b> sample(behand)</figcaption>
  <br>
  <br>
  <img src="assets/sample_3.png" alt="sample" width="1920">
  <figcaption><b>Figure:</b> add depth of field</figcaption>
</figure>

Try higher resolution plssss, its beautiful!

## Requirements

- C++17-compliant compiler (e.g. `g++`, `clang++`)
- OpenMP support (`-fopenmp`)`
- No external dependencies — all required headers (`stb_image_write.h`, `json.hpp`) are included in this repo.`

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
{
  "width": 3840,
  "height": 2880,
  "camera": {"..."},
  "background": {"..."},
  "lights": ["..."],
  "spheres": ["..."]
}
```
- You can define custom resolution, spheres, lights, resolution, etc. via a `scene.json`file.
- The default camera parameters facing forward are as follows:
```json
"camera": {
    "position": [0, 0, 0],
    "look_at": [0, 0, -1],
    "aperture": 0, //0 means no depth of field effect
    "focus_dist": 25.0,
}
```
### The rendered images will be saved in the `out` folder located at the project root directory.

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
