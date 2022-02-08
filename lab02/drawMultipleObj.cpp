#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define windowWidth 1000
#define windowHeight 1000

#define widht 20
#define height 10

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(5);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight, 0.0, 1.0);
}

void drawLine(float start_x, float start_y, float end_x, float end_y)
{
    glBegin(GL_LINES);
    glColor3f(1, 1, 0);
    glVertex2f(start_x, start_y);
    glVertex2f(end_x, end_y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawLine(20, 20, 400, 20);
    drawLine(20, 20, 20, 400);

    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    // glPointSize(50);
    glVertex3f(100.0f, 50.0f, 0.0f);
    glVertex3f(100.0f, 150.0f, 0.0f);
    glVertex3f(200.0f, 200.0f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex3f(200, 100, 0);
    glVertex3f(300, 100, 0);
    glVertex3f(250, 200, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(250, 250, 0);
    glVertex3f(350, 250, 0);
    glVertex3f(350, 350, 0);
    glVertex3f(250, 350, 0);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("A Simple Rectange");

    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);

    init();
    glutMainLoop();
}
