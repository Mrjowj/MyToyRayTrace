# Study Note
## Foreword
| Axis     | Direction (English) | Notes              |
|----------|---------------------|--------------------|
| X        | Right (+)           | Horizontal axis    |
| Y        | Up (+)              | Vertical axis      |
| Z        | Into screen (-)     | Depth (camera view)|
<figure>
  <img src="docs/screen.png" alt="Axis" width="400">
  <figcaption><b>Figure:</b> Axis</figcaption>
</figure>

- using `vector<vec3> framebuffer(width * height)`to store pixios
- For ray algorithm and corresponding material parameters
  -> [watch here](docs/algorithm&material.pdf)
## sphere.c

- framebuffer is a 1dim array of Vec3f values, give us (r,g,b) values for each pixel. 

- How to know a intersect between ray and sphere?
  -> [watch here](http://www.lighthouse3d.com/tutorials/maths/ray-sphere-intersection/)

<figure>
  <img src="docs/r.png" alt="ray_sphere_intersect() in sphere.h" width="400">
  <figcaption><b>Figure:</b> ray_sphere_intersect() in <code>sphere.h</code></figcaption>
</figure>

---
## render.c
- How to Calculate reflection vector?
  -> [watch here](https://zhuanlan.zhihu.com/p/555451478)
- Calculate refraction vector using Snell's law?
  -> [watch here](https://byjus.com/physics/law-refraction-snells-law/)

---



*Maintained by: Mrjowj*