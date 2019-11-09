#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#define PI 3.1415
#define Z_COORDINATE 0.0
#define RADIO_INT 1.0
#define RADIO_EXT 0.7

static GLuint triangle;
static GLuint start;

void drawTriangle()
{
    glBegin(GL_TRIANGLE_STRIP);

    double initialAngle = PI / 6.0;
    double phaseAngle = 2 * PI / 3.0;
    for (int i = 0; i < 4; i++)
    {
        glVertex3f(RADIO_INT * cos(initialAngle + i * phaseAngle), RADIO_INT * sin(initialAngle + i * phaseAngle), Z_COORDINATE);
        glVertex3f(RADIO_EXT * cos(initialAngle + i * phaseAngle), RADIO_EXT * sin(initialAngle + i * phaseAngle), Z_COORDINATE);
    }

    glEnd();
}

void drawStart()
{
    glPushMatrix();
    glCallList(triangle);

    glRotatef(180, 0, 0, 1);
    glCallList(triangle);
    glPopMatrix();
}

void drawSixStarts()
{

    for (int i = 0; i < 360/60; i++)
    {
        glPushMatrix();
        glColor3f(0, 0.1 * i, 0.1 * i);
        glRotatef(30 * i, 0, 1, 0);
        glCallList(start);
        glPopMatrix();
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    triangle = glGenLists(1);
    glNewList(triangle, GL_COMPILE);
    drawTriangle();
    glEndList();

    start = glGenLists(2);
    glNewList(start, GL_COMPILE);
    drawStart();
    glEndList();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);

    glColor3f(0.3, 0, 0);
    glutWireSphere(1.0, 20, 20);

    drawSixStarts();

    glFlush();
}

void reshape(GLint w, GLint h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float razon = (float)w / h;
    gluPerspective(45, razon, 0.1, 100);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SGI P4");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
