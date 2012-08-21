#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>

void onInitialization()
{ //creating the light source
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat pos[] = { 0.0, 0.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glEnable(GL_LIGHT0);
	glTranslatef(0.5, 0.5, 0.0);
	glRotatef(0, 1, 0, 0); //we want to see the top of the teapot
}

void onDisplay()
{
	const float size = 0.25;

	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//rotating on every frame (for testing purposes only)
	glRotated(5, 1, 0, 0);
	glPushMatrix();
	glutSolidCone(0.25*size, size, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.25, 0);
	glutSolidSphere(0.5*size, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 0.25, 0);
	glutSolidTeapot(0.5*size);
	glPopMatrix();

	glFinish();
	glutSwapBuffers();
}

void onKeyboard(unsigned char key, int x, int y)
{
	if (key == 32)
	{ //do rotation upon hitting the Space key
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Teapot");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	onInitialization();

	glutDisplayFunc(onDisplay);
	glutKeyboardFunc(onKeyboard);

	glutMainLoop();

	return 0;
}
