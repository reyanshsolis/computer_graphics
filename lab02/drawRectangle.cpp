// A simple introductory program; its main window contains a static picture
// of a triangle, whose three vertices are red, green and blue.  The program
// illustrates viewing with default viewing parameters only.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define windowWidth 500
#define windowHeight 300

#define widht 20
#define height 10

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex3f(-widht, -height, 0);
    // glColor3f(1, 1, 0);
    glVertex3f(widht, -height, 0);
    // glColor3f(1, 1, 0);
    glVertex3f(widht, height, 0);
    // glColor3f(1, 1, 0);
    glVertex3f(-widht, height, 0);
    glEnd();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("A Simple Rectange");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    init();
    glutMainLoop();
}
