#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#define PI 3.1415
#define Z_COORDINATE 0.0
#define RADIO_INT 1.0
#define RADIO_EXT 0.7

static GLuint triangle;
static GLuint start;
static GLuint twoStarts;

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
    glColor3f(0.0, 0.0, 0.3);
    glCallList(triangle);

    glRotatef(180, 0, 0, 1);
    glCallList(triangle);
    glPopMatrix();
}

void drawTwoStarts()
{
    glPushMatrix();
    glRotatef(-15, 0, 0, 1);
    glCallList(start);
    glPushMatrix();
    glScalef(0.4, 0.4, Z_COORDINATE);
    glRotatef(30, 0, 0, 1);
    glCallList(start);
    glPopMatrix();
    glPopMatrix();
}

void init()
{
    triangle = glGenLists(1);
    glNewList(triangle, GL_COMPILE);
    drawTriangle();
    glEndList();

    start = glGenLists(2);
    glNewList(start, GL_COMPILE);
    drawStart();
    glEndList();

    twoStarts = glGenLists(3);
    glNewList(twoStarts, GL_COMPILE);
    drawTwoStarts();
    glEndList();
}

void drawStarts()
{
    glPushMatrix();
    glScalef(0.5, 0.5, Z_COORDINATE);

    glPushMatrix();
    glTranslatef(1.0, 1.0, Z_COORDINATE);
    glCallList(twoStarts);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0, -1.0, Z_COORDINATE);
    glRotatef(30, 0, 0, 1);
    glCallList(twoStarts);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0, 1.0, Z_COORDINATE);
    glRotatef(30, 0, 0, 1);
    glCallList(twoStarts);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0, -1.0, Z_COORDINATE);
    glCallList(twoStarts);
    glPopMatrix();

    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawStarts();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SGI P3");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
