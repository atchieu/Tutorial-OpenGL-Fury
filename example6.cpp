#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include "GLUT/glut.h"
#endif

float xrot = 0.0f;
float yrot = 0.0f;

bool fullscreen = false;

bool init()
{
	glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

	return true;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// TRIANGLE
	glPushMatrix();

		glTranslatef(0.25f, 0.5f, 0.0f);

		glScalef(0.5f, 0.5f, 0.5f);
		glRotatef(xrot, 1.0f, 0.0f, 0.0f);

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.25f, -0.25f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f( 0.25f, -0.25f, 0.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-0.25f,  0.25f, 0.0f);
		glEnd();

	glPopMatrix();

	// SQUARE
	glPushMatrix();

		glTranslatef(0.75f, 0.5f ,0.0f);
		glScalef(0.5f, 0.5f, 0.5f);
		glRotatef(yrot, 0.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(-0.25f, -0.25f);
			glVertex2f( 0.25f, -0.25f);
			glVertex2f( 0.25f,  0.25f);
			glVertex2f(-0.25f,  0.25f);
		glEnd();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	xrot += 0.2f;
	yrot += 0.3f;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27 : 
		exit(1); break;
	}
}

void specialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		fullscreen = !fullscreen;

		if (fullscreen)
			glutFullScreen();
		else
		{
			glutReshapeWindow(500, 500);
			glutPositionWindow(50, 50);
		}
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
	glutCreateWindow("10 - Transformations");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);

	if (!init())
		return 1;

	glutMainLoop();

	return 0;
}

