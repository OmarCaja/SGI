#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#define PI 3.1415
#define Z_COORDINATE 0.0
#define RADIO_INT 0.7
#define RADIO_EXT 1.0

static GLuint triangle;
static GLuint start;
static GLuint sixStarts;

static int startAngle = 0;
static int initalSeconds = 0;

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
    for (int i = 0; i < 6; i++)
    {
        glPushMatrix();
        glScalef(0.2, 0.2, 0.2);
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

    sixStarts = glGenLists(3);
    glNewList(sixStarts, GL_COMPILE);
    drawSixStarts();
    glEndList();
}

void drawHours()
{
    double initialAngle = PI / 6.0;

    for (int i = 0; i < 12; i = i + 2)
    {
        glColor3f(0, 0.1 * i, 0.1 * i);
        glPushMatrix();
        glTranslatef(RADIO_EXT * cos(initialAngle * i), RADIO_EXT * sin(initialAngle * i), Z_COORDINATE);
        glutSolidCube(0.05);
        glPopMatrix();
    }

    for (int i = 1; i < 12; i = i + 2)
    {
        glColor3f(0, 0.1 * i, 0.1 * i);
        glPushMatrix();
        glTranslatef(RADIO_EXT * cos(initialAngle * i), RADIO_EXT * sin(initialAngle * i), Z_COORDINATE);
        glutSolidSphere(0.05, 20, 20);
        glPopMatrix();
    }
}

void drawHour()
{
    glColor3f(0, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
}

void drawMinute()
{
    glColor3f(0, 0.3, 0.3);
    glPushMatrix();
    glTranslatef(0, 0.7, 0);
    glutSolidSphere(0.075, 20, 20);
    glPopMatrix();
}

void drawSecond()
{
    glColor3f(0, 0.6, 0.6);
    glPushMatrix();
    glTranslatef(0, 0.4, 0);
    glutSolidSphere(0.05, 20, 20);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glRotatef(startAngle, 0, 1, 0);
    glCallList(sixStarts);
    glPopMatrix();

    drawHours();
    drawHour();
    drawMinute();
    drawSecond();

    glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float razon = (float)w / h;
    gluPerspective(45, razon, 0.1, 100);
}

void onTimer(int value)
{
    startAngle = startAngle + value;

    glutTimerFunc(10, onTimer, 3);

    glutPostRedisplay();
}

void onTimerSeconds(int value)
{
    initalSeconds = initalSeconds + value;

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Reloj 3D");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, onTimerSeconds, 1);
    glutTimerFunc(10, onTimer, 3);
    glutMainLoop();
    return 0;
}
