

#include <iostream>
#include <cmath>
#include <gl/freeglut.h>

#define PI 3.1341592
#define CAMERA_X 20
#define CAMERA_Y 10
#define CAMERA_Z 10

GLuint trianguloSup, trianguloInf, estrella;

void dibujaEstrella()
{
	float radioIn = 0.7;
	float radioOut = 1.0;
	float inc = 2.0 * PI / 3.0;
	trianguloSup = glGenLists(1);
	glNewList(trianguloSup, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(radioIn * cos(i * inc + (PI / 2.0)), radioIn * sin(i * inc + (PI / 2.0)));
		glVertex2f(radioOut * cos(i * inc + (PI / 2.0)), radioOut * sin(i * inc + (PI / 2.0)));
	}
	glEnd();
	glEndList();

	trianguloInf = glGenLists(1);
	glNewList(trianguloInf, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(radioIn * cos(i * inc + (3 * PI / 2.0)), radioIn * sin(i * inc + (3 * PI / 2.0)));
		glVertex2f(radioOut * cos(i * inc + (3 * PI / 2.0)), radioOut * sin(i * inc + (3 * PI / 2.0)));
	}
	glEnd();
	glEndList();

	glCallList(trianguloSup);
	glCallList(trianguloInf);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(CAMERA_X, CAMERA_Y, CAMERA_Z, 0, 0, 0, 0, 1, 0);

	glColor3f(0, 0, -1);
	glutWireSphere(1, 20, 20);

	for (int i = 0; i < 360 / 60; i++)
	{
		glPushMatrix();
		float color_inc = (float) i * 30.0 / 360.0;
		glColor3f(0.0, 1.0 - color_inc, 0.0 + color_inc);
		glRotatef(30 * i, 0, 1, 0);
		dibujaEstrella();
		glPopMatrix();
	}
	
	glFlush();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ra = (float)width / height;
	float camera_distance = sqrt(pow(CAMERA_X, 2) + pow(CAMERA_Y, 2) + pow(CAMERA_Z, 2));
	float fovy = 2.0 * asin(1 / camera_distance) * 180.0 / PI;
	gluPerspective(fovy, ra, 0.1, 100);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Estrella3D");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}