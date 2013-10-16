#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<GL/glew.h>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<math.h>


using namespace std;


void display (void) {  


glClearColor(0.5f, 0.5f, 0.0f, 1.0f); 
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
glMatrixMode(GL_MODELVIEW);
glLoadIdentity(); 
gluLookAt(0, 0, 0, 0.0, 0.0, -5.0, 0.0, 1.0, 0.0);

glColor3f(1.0, 0.0, 0.0);

glutSolidCylinder(0.2, 1.0, 10, 10);

glutSwapBuffers();  
}






int main(int argc, char** argv){
	cout<<"Hello World";
	glutInit(&argc, argv); 
	glutInitDisplayMode (GLUT_DOUBLE); 
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100); 
	glutCreateWindow ("Boxers");  
  
	glutDisplayFunc(display);
	glutIdleFunc(display);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);

	glutMainLoop();   

	getchar();
	return 0;
}