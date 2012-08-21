/**
 * Tutorial for rotating and translating in OpenGL
 */

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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	glEnable(GL_LIGHTING);
//	GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
//	glShadeModel(GL_SMOOTH);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading

	return true;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Add ambient light
	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	// TRIANGLE
	glPushMatrix();

	glTranslatef(0.25f, 0.5f, 0.0f);

	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);

//	glBegin(GL_TRIANGLES);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(-0.25f, -0.25f, 0.0f);
//	glColor3f(0.0f, 1.0f, 0.0f);
//	glVertex3f(0.25f, -0.25f, 0.0f);
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glVertex3f(-0.25f, 0.25f, 0.0f);
//	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidTeapot(0.25f);

	glPopMatrix();

	// SQUARE
	glPushMatrix();

	glTranslatef(0.75f, 0.5f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

//	glBegin(GL_QUADS);
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glVertex2f(-0.25f, -0.25f);
//	glVertex2f(0.25f, -0.25f);
//	glVertex2f(0.25f, 0.25f);
//	glVertex2f(-0.25f, 0.25f);
//	glEnd();

	glutSolidCone(0.25f, 0.50f, 25, 25);

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

//Called when the window is resized
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double) w / (double) h, 1.0, 200.0);
}


void idle()
{
	xrot += 0.2f;
	yrot += 0.3f;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(1);
		break;
	}
}

void specialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		fullscreen = !fullscreen;

		if (fullscreen)
		{
			glutReshapeWindow(1152, 1152);
			glutPositionWindow(0, 0);
//			glutFullScreen();
		}
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
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("translations and rotations");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);

	if (!init()) return 1;

	glutMainLoop();

	return 0;
}

