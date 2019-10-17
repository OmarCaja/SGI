#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#define PI 3.1415
#define Z_COORDINATE 0.0

void printTriangle(double initialAngle)
{
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0, 0.0, 0.3);
    double phaseAngle = 2 * PI / 3.0;
    for (int i = 0; i < 4; i++)
    {
        glVertex3f(cos(initialAngle + i * phaseAngle), sin(initialAngle + i * phaseAngle), Z_COORDINATE);
        glVertex3f(0.7 * cos(initialAngle + i * phaseAngle), 0.7 * sin(initialAngle + i * phaseAngle), Z_COORDINATE);
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    printTriangle(PI / 6.0);
    printTriangle(PI / 2.0);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SGI P2");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}