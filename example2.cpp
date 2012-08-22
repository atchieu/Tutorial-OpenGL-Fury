#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include "GLUT/glut.h"
#endif

#define KEY_ESCAPE 27

bool fullscreen = false;

void display()
{
	const float size = 0.25;

	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//rotating on every frame (for testing purposes only)
//	glRotated(5, 1, 0, 0);
	glPushMatrix();
	glutSolidCone(0.25 * size, size, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.25, 0);
	glutSolidSphere(0.5 * size, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 0.25, 0);
	glutSolidTeapot(0.5 * size);
	glPopMatrix();

	glFinish();
	glutSwapBuffers();

//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen and Depth Buffer
//	glLoadIdentity();
//	glTranslatef(0.0f, 0.0f, -3.0f);
//
//	/*
//	 * Triangle code starts here
//	 * 3 verteces, 3 colors.
//	 */
//	glBegin(GL_TRIANGLES);
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glVertex3f(0.0f, 1.0f, 0.0f);
//	glColor3f(0.0f, 1.0f, 0.0f);
//	glVertex3f(-1.0f, -1.0f, 0.0f);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, -1.0f, 0.0f);
//	glEnd();
//
//	glutSwapBuffers();
}

void initialize()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat pos[] = { 0.0, 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);

//	glTranslatef(0.5, 0.5, 0.0);
//	glRotatef(0, 1, 0, 0); //we want to see the top of the teapot

//	glMatrixMode(GL_PROJECTION); // select projection matrix
//	glViewport(0, 0, DEFAULT_SIZE, DEFAULT_SIZE); // set the viewport
//	glMatrixMode(GL_PROJECTION); // set matrix mode
//	glLoadIdentity(); // reset projection matrix
//	GLfloat aspect = (GLfloat) DEFAULT_SIZE / DEFAULT_SIZE;
//	gluPerspective(45, aspect, 1, 500); // set up a perspective projection matrix
//	glMatrixMode(GL_MODELVIEW); // specify which matrix is the current matrix
//	glShadeModel(GL_SMOOTH);
//	glClearDepth(1.0f); // specify the clear value for the depth buffer
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LEQUAL);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // specify implementation-specific hints
//	glClearColor(0.0, 0.0, 0.0, 1.0); // specify clear values for the color buffers
}

void keyboardExit(unsigned char key, int mousePositionX, int mousePositionY)
{
	switch (key)
	{
	case KEY_ESCAPE:
		exit(0);
		break;
	case 32:
		glutPostRedisplay();
	default:
		break;
	}
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double) w / (double) h, -1.0f, 1.0f);
}

void keyboardFullscreen(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		fullscreen = !fullscreen;

		if (fullscreen)
		{
			glutFullScreen();
		}
		else
		{
			glutReshapeWindow(640, 640);
		}
	}
}

int main(int argc, char **argv)
{
	// INITIALIZATION AND SETUP
	glutInit(&argc, argv); // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // display mode
	glutInitWindowSize(640, 640); // set window size
	glutCreateWindow("Testing"); // create window

	initialize();

	// WHAT TO DISPLAY
	glutDisplayFunc(display); // register Display Function
//	glutIdleFunc(display); // register Idle Function

	// SPECIAL KEYBOARD FUNCTIONS
	glutSpecialFunc(keyboardFullscreen); // register fullscreen as F1
	glutKeyboardFunc(keyboardExit); // register exit as escape

	// RESIZE
	glutReshapeFunc(resize);

	// RUN
	glutMainLoop();

	return 0;
}
