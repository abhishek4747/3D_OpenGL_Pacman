/******************************************************************************
* Project	:	3D_Pacman 
* Authors	:	Abhishek Kumar & Nikhil Verma
* Course	:	CSL781 Computer Graphics (Fall, 2013)
* Instructor:	Subodh Kumar
* T.A.		:	Nisha Jain	
* Started on:	15-Oct-2013
* Ended on	:	-Oct-2013
* Motivation:	http://freepacmanforacause.webs.com/pacman_1.gif

* Features:
	* 
	*
******************************************************************************/

// RULES: 
	// Code should be well documented and well formatted
	// No git push Unless permitted by other team member
	// Code should be generic and hack-less
	// Any line of code should not exceed 80 characters, fold it if does
	// No warnings during compilation
	

// TODO: Before Mid Evaluation
	// Create Start Screen - simple in start i.e. press enter to start game
	// Create Maze
	// Camera Movement Controls
	// Create Ghost .obj
	// Create Pac	.obj
	// Movement
	// Animation
	// Levels
	// 

// TODO: After Mid Evalutaion
	// Multplayer
	// Height Map
	// Sound Effects

// includes all common headers
#include "Headers.h" 


void reshape (int width, int height) {  
	// Set our viewport to the size of our window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Switch to the projection matrix so that we can manipulate how our 
	// scene is viewed
	glMatrixMode(GL_PROJECTION);   
	
	// Reset the projection matrix to the identity matrix so that we don't 
	// get any artifacts (cleaning up)  
	glLoadIdentity(); 
	
	// Set the Field of view angle (in degrees), the aspect ratio of our 
	// window, and the new and far planes (fovy,W,H,Znear,Zfar)
	gluPerspective(60, (GLfloat)width / (GLfloat)height, .1, 100.0); 	
	
	// Switch back to the model view matrix, so that we can start drawing 
	// shapes correctly
	glMatrixMode(GL_MODELVIEW);   
}

void display (void) {  
	// Background Color: Black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	gluLookAt (0., 0., 0., 0.0, -5., 0., 0., 1., 0.);
	glColor3f(1.0, 0.5, 0.0);
	glutSolidCylinder(0.2, 1.0, 10, 10);
	// A white colored mesh 
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
		glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
		glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
	}
	glEnd();

	glutSwapBuffers();  
}

int main(int argc, char** argv){

	// Initialise Glut Variables
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH); 
	glutInitWindowSize (1350, 690);
	glutInitWindowPosition (0, 0); 
	glutCreateWindow ("3D Pacman");

	// Enable Glut Features
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// Set Triggers
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	// Start Main Loop
	glutMainLoop();   
	
	return 0;
}

/*******************************COLOR TABLE************************************
http://gucky.uni-muenster.de/cgi-bin/rgbtab-en

Black:	0.f, 0.f, 0.f
White:	1.f, 1.f, 1.f
Red:	1.f, 0.f, 0.f
Green:	0.f, 1.f, 0.f
Blue:	0.f, 0.f, 1.f
Write More Colors Here If needed For Example
MazeColor: x,y,z etc

******************************************************************************/