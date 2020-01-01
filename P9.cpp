#define PROYECTO "Interfaz de conducción, Velocidad = 0 m/s"
	
#include <sstream>
#include <Utilidades.h>

float camera_pos_x = 0, camera_pos_y = 2, camera_pos_z = 0;
float camera_view_x = 20, camera_view_y = 1, camera_view_z = 0;

GLfloat v0[3] = { 0, 0, 5 }, v1[3] = { 1000, 0, 5 }, v2[3] = { 1000, 0, -5 }, v3[3] = { 0, 0, -5 };

float velocity = 0;
static const float velocityInc = 0.1;

static GLuint road, desert;

void init()
// Inicializaciones
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Texturas (carga de texturas)
	glGenTextures(1, &road);
	glBindTexture(GL_TEXTURE_2D, road);
	loadImageFile((char*)"carretera.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenTextures(1, &desert);
	glBindTexture(GL_TEXTURE_2D, desert);
	loadImageFile((char*)"desierto.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	// Configurar el motor de render
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, desert);
	texturarFondo();

	// Seleccion de la matriz modelo-vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Situamos y orientamos la camara
	gluLookAt(camera_pos_x, camera_pos_y, camera_pos_z, camera_view_x, camera_view_y, camera_view_z, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, road);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_POLYGON);

	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 5);

	glTexCoord2f(1, 100);
	glVertex3f(2000, 0, 5);

	glTexCoord2f(0, 100);
	glVertex3f(2000, 0, -5);

	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -5);

	glEnd();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	float ra = (float)w / h;

	// Fijamos el marco dentro de la ventana de dibujo
	glViewport(0, 0, w, h);

	// Seleccionar la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Camara perspectiva
	gluPerspective(45, ra, 0.1, 100);
}

void onSpecialKey(int specialKey, int x, int y)
{
	// Callback de atencion al pulsado de letras y numeros
	switch (specialKey) {
	case GLUT_KEY_UP:
		velocity = velocity + velocityInc;
		break;
	case GLUT_KEY_DOWN:
		if (velocity > 0) {
			velocity = velocity - velocityInc;
		}
		else {
			velocity = 0.0;
		}
		break;
	}

	stringstream titulo;
	titulo << "Interfaz de conducción, Velocidad = "<< velocity << " m/s";
	glutSetWindowTitle(titulo.str().c_str());
}

void onTimer(int valor)
{
	camera_pos_x = camera_pos_x + (velocity * valor / 1000);
	camera_view_x = camera_view_x + (velocity * valor / 1000);

	glutTimerFunc(20, onTimer, valor);

	glutPostRedisplay();
}

void main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(onSpecialKey);
	glutTimerFunc(20, onTimer, 20);

	// Bucle de atencion a eventos
	glutMainLoop();
	FreeImage_DeInitialise();
}
