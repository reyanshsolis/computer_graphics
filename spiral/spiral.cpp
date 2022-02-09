// 17QE30004 Rishabh Singh
// Computer Graphics Assignment 1

#include <iostream>
#include <vector>

// For sin and cos functions and M_PI value.
#include <cmath>
// For throwing errors.
#include <stdexcept>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Window Width.
#define windowWidth 1600
// Window Height.
#define windowHeight 900
// Point Size.
#define pointSize 3

// Container for storing 2D Points of type integer.
struct Point2i {
    Point2i(int x = 0, int y = 0) : x_(x), y_(y) {}
    // Casts double to int.
    Point2i(double x = 0.0f, double y = 0.0f)
        : x_(static_cast<int>(x)), y_(static_cast<int>(y)) {}
    int x_;
    int y_;
};

// OpenGL is a C API, and knows nothing about this pointers. Therefore global
// container or static functions must be used.

// Container for Circular Spiral parameters.
struct CircularSpiralParam {
    CircularSpiralParam(double minor_radius = 60,
                        double major_radius = 120,
                        size_t resolution = 100,
                        size_t number_of_spirals = 10)
        : minor_radius_(minor_radius),
          major_radius_(major_radius),
          resolution_(resolution),
          number_of_spirals_(number_of_spirals) {
        // Verify parameters:
        if (minor_radius < 0 || major_radius < 0) {
            throw std::invalid_argument(
                    "Received negative value. All arguments must be positive");
        }
    }

    void operator()(double minor_radius,
                    double major_radius,
                    size_t resolution,
                    size_t number_of_spirals) {
        minor_radius_ = minor_radius;
        major_radius_ = major_radius;
        resolution_ = resolution;
        number_of_spirals_ = number_of_spirals;
    }

    double minor_radius_;
    double major_radius_;
    size_t resolution_;
    size_t number_of_spirals_;
} circular_spiral_param;

// Draw one pixel.
void DrawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Draw line using Bresenham’s line drawing algorithm.
void DrawLine(int x1, int x2, int y1, int y2) {
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    incx = 1;
    if (x2 < x1) incx = -1;
    incy = 1;
    if (y2 < y1) incy = -1;
    x = x1;
    y = y1;
    if (dx > dy) {
        DrawPixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += inc1;
            } else
                e += inc2;
            x += incx;
            DrawPixel(x, y);
        }
    } else {
        DrawPixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            } else
                e += inc2;
            y += incy;
            DrawPixel(x, y);
        }
    }
}

/// \brief Returns list of 2D interget points on the circumference of the
/// circular spiral.
std::vector<Point2i> GetPointsOnCircularSpiral(CircularSpiralParam& param) {
    // Taking center of the major circle in the center of the screen.
    const int major_cx = windowWidth / 2;
    const int major_cy = windowHeight / 2;

    // Number of spirals is one less than the number of circles. Therefore,
    // for `0` spirals, we get a complete circle.
    const double num_circles = param.number_of_spirals_ + 1;

    // The minor angle loop runs from 0 to `(number of circles) x 2 PI`.
    // M_PI : Value of PI defined in std (math.h) [3.14159265358979323846]
    const double minor_angle_range = num_circles * 2.0f * M_PI;
    const double minor_angle_increment =
            2.0f * M_PI / static_cast<double>(param.resolution_);
    const double major_angle_increment = minor_angle_increment / num_circles;

    // Stores points for the spiral geometry.
    std::vector<Point2i> points;
    points.reserve(param.resolution_ * num_circles + 1);

    for (double minor_angle = 0.0f, major_angle = 0.0f;
         minor_angle <= minor_angle_range; minor_angle += minor_angle_increment,
                major_angle += major_angle_increment) {
        // Center offset along x axis.
        const double cx =
                param.major_radius_ * std::sin(major_angle) + major_cx;
        // Center offset along y axis.
        const double cy =
                param.major_radius_ * std::cos(major_angle) + major_cy;

        points.emplace_back(param.minor_radius_ * std::sin(minor_angle) + cx,
                            param.minor_radius_ * std::cos(minor_angle) + cy);
    }

    return points;
}

// OpenGL Init function.
void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Set background color.
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glPointSize(pointSize);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight, 0.0, 1.0);
}

// Display Function.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Get list of points on the geometry.
    std::vector<Point2i> points =
            GetPointsOnCircularSpiral(circular_spiral_param);
    const size_t num_points = points.size();

    // Draw line segments between the obtained points.
    for (size_t i = 1; i < num_points; ++i) {
        DrawLine(points[i - 1].x_, points[i].x_, points[i - 1].y_,
                 points[i].y_);
    }
    // Completed the loop by drawing the line segment between first and the
    // last point.
    DrawLine(points[0].x_, points[num_points - 1].x_, points[0].y_,
             points[num_points - 1].y_);

    glFlush();
}

/// \brief Prints usage information.
void PrintHelp() {
    // clang-format off
    std::cout << "\n Usage: "
              << "\n ./spiral [minor_radius] [major_radius] [resolution] [number_of_spirals]"
              << "\n"
              << "\n            minor_radius: Radius of smaller minor circles used to create spiral loops."
              << "\n            major_radius: Radius of imaginary circle."
              << "\n            resolution: Resolution in each spiral loop."
              << "\n            number_of_spirals: Number of spirals."
              << std::endl;
    // clang-format on
}

/// \brief Validated user inputs, and sets the parameter for circular spiral.
/// Expects 4 arguments for minor_radius [double], major_radius [double],
/// resolution [size_t], number_of_spirals [size_t]. All of these arguments must
/// be positive.
void SetParametersFromArgs(int argc, char** argv) {
    double minor_radius =
            atof(argv[1]) < 0 ? throw std::invalid_argument(
                                        "Invalid argument for minor_radius. "
                                        "All argument must be positive.")
                              : static_cast<double>(atof(argv[1]));
    double major_radius =
            atof(argv[2]) < 0 ? throw std::invalid_argument(
                                        "Invalid argument for major_radius. "
                                        "All argument must be positive.")
                              : static_cast<double>(atof(argv[2]));
    size_t resolution = atoi(argv[3]) < 0
                                ? throw std::invalid_argument(
                                          "Invalid argument for resolution. "
                                          "All argument must "
                                          "be positive.")
                                : static_cast<size_t>(atoi(argv[3]));
    size_t number_of_spirals =
            atoi(argv[4]) < 0
                    ? throw std::invalid_argument(
                              "Invalid argument for number_of_spirals. All "
                              "argument must be positive.")
                    : static_cast<size_t>(atoi(argv[4]));

    circular_spiral_param(minor_radius, major_radius, resolution,
                          number_of_spirals);
}

int main(int argc, char** argv) {
    if (argc < 5) {
        PrintHelp();
        return 0;
    }
    SetParametersFromArgs(argc, argv);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circular Spiral Loop using Bresenham's Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
