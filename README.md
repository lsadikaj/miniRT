# miniRT

This project has been created as part of the 42 curriculum by lsadikaj, jiparcero.

## Description

miniRT is a simple ray tracer written in C, built from scratch as part of the 42 curriculum. It generates computer-generated images of a scene, as seen from a specific camera angle and position, made up of basic geometric primitives (planes, spheres, and cylinders) each with their own color, lighting, and shadowing.

The renderer reads a scene description from a custom `.rt` file, casts a ray through every pixel of the output window, computes the closest intersection with the objects in the scene, and shades the resulting point using ambient and diffuse lighting, with hard shadows cast by any object standing between a surface point and the light source.

Display is handled through the MiniLibX graphics library.

## Instructions

### Requirements

- Linux or macOS
- MiniLibX (system version or bundled sources)
- X11 development libraries (Linux)
- `cc` compiler with `-Wall -Wextra -Werror`
- `make`

### Compilation

```
make
```

### Execution

```
./miniRT scenes/scene_name.rt
```

The program takes a single argument: a scene description file with the `.rt` extension.

### Controls

| Action | Effect |
|---|---|
| `ESC` | Closes the window and exits cleanly |
| Red cross (window frame) | Closes the window and exits cleanly |

## Scene file format (.rt)

Each element is identified by a one or two character identifier at the start of the line, followed by its parameters in a fixed order. Elements can appear in any order in the file, and elements identified by a capital letter (`A`, `C`, `L`) can only be declared once.

| Identifier | Element | Parameters |
|---|---|---|
| `A` | Ambient lighting | ratio [0.0,1.0], color (R,G,B) |
| `C` | Camera | position (x,y,z), orientation vector, FOV [0,180] |
| `L` | Light | position (x,y,z), brightness ratio [0.0,1.0], color (R,G,B) |
| `sp` | Sphere | center (x,y,z), diameter, color (R,G,B) |
| `pl` | Plane | point (x,y,z), normal vector, color (R,G,B) |
| `cy` | Cylinder | center (x,y,z), axis vector, diameter, height, color (R,G,B) |

Example scene:

```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255

pl 0,0,0 0,1.0,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

Any malformed scene file causes the program to exit cleanly, printing `Error` followed by an explicit message describing the issue.

## Supported features

- Plane, sphere, and cylinder primitives, with correct handling of all intersections (including the inside of objects)
- Resizable object properties: sphere diameter, cylinder width and height
- Translation and rotation transformations on objects, lights, and cameras (spheres and lights excluded, per subject constraints)
- Ambient and diffuse lighting
- Hard shadows
- Fluid window management (minimization, focus switching, etc.)
- Strict scene file parsing with explicit error handling


## Resources

- Scratchapixel — Introduction to Ray Tracing
- MiniLibX documentation (42 sources)
- `man 3 math` — math library reference
- 42's miniRT subject (v9.0)

## AI usage

Claude (Anthropic) was used throughout this project for the following purposes:

- **Concept explanation**: understanding vector math (dot product, cross product, normalization), the derivation of ray-sphere, ray-plane, and ray-cylinder intersection formulas, and the Phong-style ambient/diffuse lighting model
- **Architecture design**: structuring the scene parser, the object/ray/hit data types, and the render loop around MiniLibX
- **Debugging**: tracking down a cylinder intersection bug caused by a missing vector normalization and a coordinate system mix-up in a cross product
- **Code review**: catching edge cases in scene file parsing and memory management

All code was written and understood by the team members. AI was used as a learning and debugging assistant, not as a code generator.