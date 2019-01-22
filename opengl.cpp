#include<GL/gl.h>
#include<GL/glut.h>
//compile-g++ opengl.cpp  gl -lGL -lGLU -lglut
using namespace std;

void display(void){
	//clear all pixels.
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
        glVertex3f (0.25, 0.25, 0.0);
        glVertex3f (0.75, 0.25, 0.0);
        glVertex3f (0.75, 0.75, 0.0);
        glVertex3f (0.25, 0.75, 0.0);
    glEnd();
	//flush actually renders the coordinates to the screen.	
	glFlush();
}

void init(){
	//initialises with the color.
	glClearColor(0.0,0.0,0.0,0.0);
	//selects the matrix which we want to modify in subsequent calls.
	//here we have selected projection matrix.
	//projection matrix is used for converting 3D coordinates to 2D coordinates. 
	glMatrixMode(GL_PROJECTION);
	//initialises the matrix with identity matrix.(default state)
	glLoadIdentity();
	//args-left,right,bottom,top,near,far.
	//a kind of transformation.
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//single buffer with rgb mode.
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("assignment1");
	init();
	glutDisplayFunc(display); 
	glutMainLoop();
	return 0;
}
