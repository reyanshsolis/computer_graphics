## Creating Spiral-Like Shape Along The Circumference of a Circle using Bresenham’s Line Drawing Algorithm
====

Computer Graphics, Spring’22 : Assignment 1
Rishabh Singh : 17QE30004
---

Mathematical Formulation:

- Parameteric Equation of a Circle:
- Angle increment is `2 * PI / resolution` as for ex. with a resolution of 10
  this will give us a set of 10 points.

```bash
    circle_points = []
    for angle in 0 to 2 * PI with increment of 2 * PI / resolution:
        x = radius * sin(angle) + center_x
        y = radius * cos(angle) + center_y
        circle_points.append([x, y])
```

- Now to roll this circle along x axis to make a spiral along x-axis:
- We make constant incremental change along the x-axis.

```bash
    spiral_points = []
    dx = 0.5  (incremental change along x-axis)
    for angle in 0 to number_of_circles * 2 * PI with increment of 2 * PI / resolution:
        center_x = center_x + dx
        x = radius * sin(angle) + center_x
        y = radius * cos(angle) + center_y

        spiral_points.append([x, y])
```

- Now to let's roll this axis itself:
- In previous case the center of circle was running along x-axis (dx = 0.5, dy = 0).
- In order to make the center of cicles run along a circumference of a circle, we can 
  make (dx = major_radius * sin(major_angle) + major_cx
  and  (dy = major_radius * cos(major_angle) + major_cy).
  [We will be refering to the larger imaginary circle as major circle, and the circle
   creating the spiral like shape as the minor circle].
- The range of angle goes from 0 to number_of_circles * 2 * PI with increment.
- number_of_circles is 1 + number_of_spirals. i.e. number_of_spirals = 0, gives us
  a circle.
- The major angle goes from 0 to 2 * PI while the minor angles goes from 
  0 to number_of_circles * 2 * PI. Therefore the increment for the major angle is 
  minor_angle_increment / num_circles

```bash
    spiral_points = []
    minor_angle_increment = 2.0 * PI / resolution
    major_angle_increment = minor_angle_increment / number_of_circles
    for minor_angle in 0 to number_of_circles * 2 * PI with increment of minor_angle_increment
        and major_angle in 0 to 2 * PI with increment of major_angle_increment:
        
        // Center offset along x axis.
        cx = major_radius * sin(major_angle) + major_cx;
        // Center offset along y axis.
        cy = major_radius * cos(major_angle) + major_cy;

        spiral_points.append([radius * sin(minor_angle) + cx, radius * cos(minor_angle) + cy])
```

Parameters:

minor_radius // Radius of smaller minor circles used to create spiral loops.
major_radius // Radius of imaginary circle.
resolution // Resolution in each spiral loop. 
number_of_spirals // Number of spirals.

Usage:
```bash
# Compilation:
g++ spiral.cpp -lglut -lGL -lGLEW -lGLU -o spiral

# Usage:
```
 Usage: 
 ./spiral [minor_radius] [major_radius] [resolution] [number_of_spirals]

            minor_radius: Radius of smaller minor circles used to create spiral loops.
            major_radius: Radius of imaginary circle.
            resolution: Resolution in each spiral loop.
            number_of_spirals: Number of spirals.
```

Example:
```bash
  ./spiral 60 120 1000 10
```
---
