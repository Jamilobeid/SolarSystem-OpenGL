
#include <GL/glut.h>

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0); //(left, right, bottom, top)
	//this function specifies the drawing coordinate system 

}

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	glBegin(GL_LINES);
	glVertex2i(190, 145);
	glVertex2i(10, 145);
	glVertex2i(100, 145);
	glVertex2i(100,20);
	glVertex2i(100, 20);
	glVertex2i(20,20);
	glVertex2i(20,20);
	glVertex2i(20, 50);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("an example opengl program");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
	return 0;
}