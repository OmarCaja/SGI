#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#define PI 3.1415
#define Z_COORDINATE 0.0
#define RADIO_INT 1.0
#define RADIO_EXT 0.7

static GLuint triangle;

void drawTriangle()
{
    double initialAngle = PI / 6.0;
    double phaseAngle = 2 * PI / 3.0;
    for (int i = 0; i < 4; i++)
    {
        glVertex3f(RADIO_INT * cos(initialAngle + i * phaseAngle), RADIO_INT * sin(initialAngle + i * phaseAngle), Z_COORDINATE);
        glVertex3f(RADIO_EXT * cos(initialAngle + i * phaseAngle), RADIO_EXT * sin(initialAngle + i * phaseAngle), Z_COORDINATE);
    }
}

void init()
{
    triangle = glGenLists(1);

    glNewList(triangle, GL_COMPILE);

    glBegin(GL_TRIANGLE_STRIP);
    drawTriangle();
    glEnd();

    glEndList();
}

void drawStart()
{
    glColor3f(0.0, 0.0, 0.3);
    glCallList(triangle);

    glRotatef(180, 0, 0, 1);
    glCallList(triangle);
    glPushMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawStart();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SGI P2");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
