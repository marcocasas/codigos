#include "GL/glut.h"
#include <math.h>

#define PI 3.141592654

void init(void) {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,700.0,0.0,500.0);
}

void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.8,0.9,0.4);
	static int radius = 175;

	glBegin(GL_LINE_LOOP);
		//glVertex3f(200,200,-1);
		//glVertex3f(250,180,-1);
		//glVertex3f(-180, 0, 1);
		//glVertex3f(0, -180, 1);
		

		for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
			glVertex3f(350 - cos(i) * radius, 325 - sin(i) * radius, 0.0);	

		//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
		//	glVertex3f(cos(i) * radius, 325 - sin(i) * radius, 0.0);

		//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
		//	glVertex3f(175 - cos(i) * radius, 175 - sin(i) * radius, 0.0);

		//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
		//	glVertex3f(525 - cos(i) * radius, 175 - sin(i) * radius, 0.0);

	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);
	//glVertex3f(200,200,-1);
	//glVertex3f(250,180,-1);
	//glVertex3f(-180, 0, 1);
	//glVertex3f(0, -180, 1);
	//static int radius = 175;

	//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
	//	glVertex3f(350 - cos(i) * radius, 325 - sin(i) * radius, 0.0);

	//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
	//	glVertex3f(cos(i) * radius, 325 - sin(i) * radius, 0.0);

	for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
		glVertex3f(175 - cos(i) * radius, 175 - sin(i) * radius, 0.0);

	//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
	//	glVertex3f(525 - cos(i) * radius, 175 - sin(i) * radius, 0.0);

	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);
	//glVertex3f(200,200,-1);
	//glVertex3f(250,180,-1);
	//glVertex3f(-180, 0, 1);
	//glVertex3f(0, -180, 1);
	//static int radius = 175;

	//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
	//	glVertex3f(350 - cos(i) * radius, 325 - sin(i) * radius, 0.0);

	for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
		glVertex3f(cos(i) * radius, 325 - sin(i) * radius, 0.0);

	//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
	//	glVertex3f(175 - cos(i) * radius, 175 - sin(i) * radius, 0.0);

	//for (double i = 0; i < 2 * PI; i += PI / 18) //<-- Change this Value
	//	glVertex3f(525 - cos(i) * radius, 175 - sin(i) * radius, 0.0);

	glEnd();
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(700,500);
	glutCreateWindow("Ejemplo");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
}
	