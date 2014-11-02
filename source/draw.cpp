#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

void display(float x, float y)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(255,255,255,255);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-60, 60, -60, 60, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
		glColor3ub(68, 8, 45);
		//glBegin(GL_LINE_STRIP);
		glPointSize(10.0);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		glutSwapBuffers();

	
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("GLUT");
	//glutDisplayFunc(display(5));
	
	bool write = true;
	float x, y;
	while(true){

		//input x, y, and rite

		if (write)
			display(x, y);
	}

	

	glutMainLoop();
	return 0;
}
