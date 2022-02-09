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
```

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
![Case_60_120_1000_10](https://user-images.githubusercontent.com/32535717/153019611-869fb3fb-0bd0-49c4-a60e-0092054cd4a7.png)

---

Cases:

## Changing `resolution`:
`/spiral 60 120 10 10`
![Screenshot from 2022-02-09 23-16-49](https://user-images.githubusercontent.com/32535717/153260332-6e585db6-0c0b-495b-875b-3744f0ba5d3c.png)

`/spiral 60 120 5 10`
![Screenshot from 2022-02-09 23-17-30](https://user-images.githubusercontent.com/32535717/153260392-e76e4e2c-0365-462a-99cf-44293721221c.png)

---

## Changing `number_of_spirals`:

`./spiral 60 120 100 0`
![Screenshot from 2022-02-09 23-18-02](https://user-images.githubusercontent.com/32535717/153260512-db6c0cad-8ed8-4a36-af65-77244acbe7ac.png)

`./spiral 60 120 100 1`
![Screenshot from 2022-02-09 23-18-12](https://user-images.githubusercontent.com/32535717/153260651-d1d6feaf-a8a5-4ace-842d-a27547bcb8af.png)

`./spiral 60 120 100 2`
![Screenshot from 2022-02-09 23-18-26](https://user-images.githubusercontent.com/32535717/153260659-17c9d6ec-2d6e-4032-9328-248090ab4ab1.png)

`./spiral 60 120 100 3`
![Screenshot from 2022-02-09 23-18-36](https://user-images.githubusercontent.com/32535717/153260854-3aad50d2-4232-4319-a9a0-d65d3b1ec52e.png)

`./spiral 60 120 100 10`
![Screenshot from 2022-02-09 23-18-47](https://user-images.githubusercontent.com/32535717/153260710-83df654d-1f6c-433b-ae67-2cb025711155.png)

`./spiral 60 120 100 100`
![Screenshot from 2022-02-09 23-18-56](https://user-images.githubusercontent.com/32535717/153260741-cbbe0558-8dcb-4652-ad80-cc556b74be3e.png)

---

## Changing `major_radius`:
` ./spiral 60 60 100 10`
![Screenshot from 2022-02-09 23-19-12](https://user-images.githubusercontent.com/32535717/153261061-cfc2ef53-41fd-4887-bf65-05c0140d3daa.png)

` ./spiral 60 30 100 10`
![Screenshot from 2022-02-09 23-19-25](https://user-images.githubusercontent.com/32535717/153261163-37e0b372-08ff-4178-b176-9e303be02a50.png)

` ./spiral 60 0 100 10`
![Screenshot from 2022-02-09 23-19-38](https://user-images.githubusercontent.com/32535717/153261181-d507ee7f-c4e6-4834-be86-ab3bb50ee2dc.png)
---

## Changing `minor_radius`:
`./spiral 0 0 100 10`
![Screenshot from 2022-02-09 23-19-50](https://user-images.githubusercontent.com/32535717/153261340-a5b62930-52d6-42ca-8010-9b0e69b076b6.png)

---

Using negative for any parameter throws error (std::error)
