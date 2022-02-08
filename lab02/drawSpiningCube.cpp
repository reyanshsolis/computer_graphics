#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define windowWidth 1000
#define windowHeight 1000

static GLfloat spin_x = 0.0;
static GLfloat spin_y = 0.0;
static GLfloat spin_z = 0.0;
static int factor_x = 0.0;
static int factor_y = 1.0;
static int factor_z = 0.0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(5);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight, 0.0, 1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glRotatef(spin_x, 0.0, 0.0, 1.0);
    glRotatef(spin_y, 0.0, 1.0, 0.0);
    glRotatef(spin_z, 1.0, 0.0, 0.0);

    // glRotatef(spin, 1.0, 1.0, 1.0);

    glColor3f(1.0, 0.0, 1.0);
    glutSolidCube(10.0);
    glPopMatrix();
    glutSwapBuffers();
}

void spinDisplay(void)
{
    spin_x = spin_x + factor_x >= 360 ? spin_x + factor_x - 360.0 : spin_x + factor_x;
    spin_y = spin_y + factor_y >= 360 ? spin_y + factor_y - 360.0 : spin_y + factor_y;
    spin_z = spin_z + factor_z >= 360 ? spin_z + factor_z - 360.0 : spin_z + factor_z;
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
        break;
    case GLUT_MIDDLE_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Spining Cube");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    init();
    glutMainLoop();
}
