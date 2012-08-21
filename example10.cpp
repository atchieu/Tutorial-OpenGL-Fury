#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#define VIEW_TURN_RATE  10
#define GLUT
#define GLUT_KEY
#define GLUT_SPEC

float t1 = 30;
float t2 = 45;
float t3 = 45;
float t4 = 0;
float t5 = 0;
float l = 1.5;
float h = 0.2 * l;
double m = 0.2;
double n = 0.2;
double p = 0.2;

float eyex, eyey = 0;
float eyez = 6;
float lx, ly, lz = 0;

int turn = 0, turn1 = 0;

void TurnRight(void)
{
	turn = (turn - VIEW_TURN_RATE) % 360;
}

void TurnLeft(void)
{
	turn = (turn + VIEW_TURN_RATE) % 360;
}

void TurnForwards(void)
{
	turn1 = (turn1 - VIEW_TURN_RATE) % 360;
}

void TurnBackwards(void)
{
	turn1 = (turn1 + VIEW_TURN_RATE) % 360;
}

void myidlefunc()
{
	if (t1 < 100) t1 += 2;
	else
	{
		if (t2 < 150) t2 += 2;
		else
		{

			if (t3 < 150) t3 += 2;
			else
			{

				if (t4 < 150) t4 += 2;
				else
				{

					if (t5 < 120) t5 += 2;
					else
					{
						glutIdleFunc(0);
					}
				}
			}
		}
	}

	glutPostRedisplay();
}

#ifdef GLUT
#ifdef GLUT_SPEC
void special(int key, int x, int y)
{

	int i = 0;
	printf("this is special keyboard: %d \n", key);
	switch (key)
	{
	/* start of view position functions */
	case 'r':
	{
		TurnRight();
		i++;
	}
		break;
	case GLUT_KEY_LEFT:
	{
		TurnLeft();
		i++;
	}
		break;
	case GLUT_KEY_DOWN:
	{
		TurnForwards();
		i++;
	}
		break;
	case GLUT_KEY_UP:
	{
		TurnBackwards();
		i++;
	}
		break;
		/* end of view postions functions */
	}
	if (i) glutPostRedisplay();
}
#endif

#ifdef GLUT_KEY
void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27:
		exit(0);
		break;

	case 's':
		if (t1 < 50)
		{
			t1++;
		}
		break;
	case 'S':
		//if (t1 < 80) {
		t1--;
		//}
		break;
	case 'q':
		glutIdleFunc(myidlefunc);
		break;
	case 'f':
		if (t2 < 160)
		{
			t2++;
		}
		break;
	case 'F':
		t2--;
		break;
	case 'g':
		t3++;
		break;
	case 'h':
		t4++;
		break;
	case 'k':
		t5++;
		break;
	}
	glutPostRedisplay();
}
#endif
#endif

void drawFloor(void)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.8, 0.8);
	glVertex3f(-20.0, 0.0, 100.0);
	glVertex3f(20.0, 0.0, 100.0);
	glVertex3f(20.0, 0.0, -100.0);
	glVertex3f(-20.0, 0.0, -100.0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Base(float l)
{
	glPushMatrix();
	//glColor3f(0.4,0.6,0.5);
	glScaled(1.0 * l, 0.2 * l, 1.0 * l);
	glutSolidCube(1);
	glPopMatrix();
}

void obst(float radius, int slices, int stacks)
{
	glTranslated(0, -0.5, 0.0);
	glPushMatrix();
	glutSolidSphere(radius, slices, stacks);
	glPopMatrix();
}

void arm(float l, float r, int slices, int stacks, float rotat)
{
	float d;
	d = 0.2 * l;

	glTranslated(0, l / 2 + d / 2, 0);
	glPushMatrix();
	glScaled(d / l, 1, d / l);
	glutSolidCube(l);
	glPopMatrix();

	glTranslated(0, l / 2, 0);
	glRotated(rotat, 0, 0, 1);
	glPushMatrix();
	glutSolidSphere(r, slices, stacks);
	glPopMatrix();
}

void Base2(float l, float r, int slices, int stacks, float rotat)
{
	float d;
	d = 0.2 * l;

	glTranslated(d / 2, d / 2, d / 2);
	glPushMatrix();
	glScaled(d, d / 2, d);
	glutSolidCube(2);
	glPopMatrix();
}

void hand(float d, float x)
{
	glColor3f(0.0, 0.4, 0.3);
	glRotated(t5, 0, 1, 0);
	glPushMatrix();
	glTranslated(0, -d / 2 + x / 2, 0);
	glScaled(1, x / d, 1);
	glutSolidCube(d);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-d / 2 + x / 2, x / 2, 0);
	glScaled(x / (d - x), 1, d / (d - x));
	glutSolidCube(d - x);
	glPopMatrix();

	glPushMatrix();
	glTranslated(d / 2 - x / 2, x / 2, 0);
	glScaled(x / (d - x), 1, d / (d - x));
	glutSolidCube(d - x);
	glPopMatrix();
}

void display()
{
	float l, T, r, x, d;
	double radius, height;
	int slices, stacks;
	l = 1.5;
	T = 30;
	d = 0.2 * l;
	x = 0.2 * d;
	r = d / 2;
	radius = 1.0;
	height = 3;
	slices = 1000;
	stacks = 202;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	//lightning start here
	glEnable(GL_LIGHT0);
	GLfloat light0_pos[] = { lx, ly + 1, lz + 1, 1 };
	GLfloat light0_diffuse[] = { 1, 0, 0, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

	GLfloat light0_Ambient[] = { 0, 1, 1, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_Ambient);

	gluLookAt(0.2, 0.8, 0.0, 5.0, 3.0, 5.0, 0.0, 0.1, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

	glScaled(0.2, 0.2, 0.2);
	glRotated(90, 0.0, 1.0, 0.0);

	/* Draw "bottom" of floor in blue. */
	glColor3f(0.0, 0.8, 0.8);
	drawFloor();

	//base
	glColor3f(0.0, 0.0, 0.0);
	Base(2);

	//base2
	glColor3f(1.0, 0.0, 0.0);
	Base2(l, r, 60, 60, t1);

	glPushMatrix();

	//arm1

	glColor3f(1.0, 0.0, 0.8);
	arm(l, r, 60, 60, t1);

	glColor3f(0.0, 1.0, 0.0);
	arm(l, r, 60, 60, t2);

	glColor3f(1.0, 0.8, 0.5);
	arm(l, r, 60, 60, t3);

	//hand
	glTranslated(0, d / 2 + r, 0);
	hand(d, x);

	glPopMatrix();

	//obst
	glTranslated(-1, 3, 0);
	glColor3f(0.0, 0.0, 1.0);
	obst(radius, slices, stacks);
	//glRotated(0.0,0.0,1.0,0.0);

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	float aspect = (float) width / (float) height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);

	//glOrtho(-aspect,aspect,-1,+1,-1,+1);
	gluPerspective(60.0, 0.0, 0.0, 8);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0, 0.0, 0.0);  /* viewing transform  */
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	static int window = glutCreateWindow("OpenGL!");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
#ifdef GLUT_SPEC
	glutSpecialFunc(special);
#endif

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glutMainLoop();
	exit(0);
}
