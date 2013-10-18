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

// TIPS:
	// Esc,q,Q to Quit
	// F5 to restart the program
	// Arrow Keys to control Camera
	// Drag Mouse to change direction of camera

// RULES: 
	// Code should be well documented and well formatted
	// Never push the code unless dropbox in the task bar shows a green check
	// Code should be generic and hack-less
	// Any line of code should not exceed 80 characters, fold it if does
	// No warnings during compilation
	

// TODO: Before Mid Evaluation
	// Create Start Screen - simple in start i.e. press enter to start game
	// Create Maze
	// Camera Movement Controls with Mouse
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
#include "Camera.h"
#include "Functions.h"
#include "Pac.h"
#include "Maze.h"

// Global Variables
Camera *cam;
string cameratype = "follow";
Pac *pacman;
Maze *maze;
bool keyStates[256];// = new bool[256];
bool keySpecialStates[256]; // = new bool[256]; // Create an array of boolean values of length 256 (0-255) 
bool SHIFT = false, ALT = false, CTRL = false;


void keyOperations (void) {  
	if (keyStates['q'] || keyStates['Q'] || keyStates[27]){
		exit(0);
	}
	if(keyStates['0']){
		cam->eyez += 0.1f;
	}else if(keyStates['.']){
		cam->eyez -= 0.1f;
	}
	
	double deg = 5.;
	if (keyStates['a'] || keyStates['A']) { // If the left arrow key has been pressed  
		double x = cam->eyex;
		double z = cam->eyez;
		cam->eyex = x*cos(degreeToRadian(deg)) - z*sin(degreeToRadian(deg));
		cam->eyez = x*sin(degreeToRadian(deg)) + z*cos(degreeToRadian(deg));
	}
	if (keyStates['d'] || keyStates['D']) { // If the right arrow key has been pressed  
		deg = -deg;
		double x = cam->eyex;
		double z = cam->eyez;
		cam->eyex = x*cos(degreeToRadian(deg)) - z*sin(degreeToRadian(deg));
		cam->eyez = x*sin(degreeToRadian(deg)) + z*cos(degreeToRadian(deg));
	}
	if (keyStates['w'] || keyStates['W']) { // If the up arrow key has been pressed  
		cam->eyex /= 1.01f;
		cam->eyey /= 1.01f;
		cam->eyez /= 1.01f;
	}
	if (keyStates['s'] || keyStates['S']) { // If the left arrow key has been pressed  
		cam->eyex *= 1.01f;
		cam->eyey *= 1.01f;
		cam->eyez *= 1.01f;
	}


	if(keyStates['-']){
		cam->eyey += exp(cam->eyey/100.f)/100.f;
	}else if(keyStates['+']){
		cam->eyey -= exp(cam->eyey/100.f)/100.f;
	}


	if (keyStates['1']) { 
		cameratype = "top";
	}else if (keyStates['2']) { 
		cameratype = "free";
	}else if (keyStates['3']) { 
		cameratype = "follow";
	}else if (keyStates['4']) { 
		cameratype = "else";
	}

	if(keyStates['o']){
		size_t h = 0;
		
	} 
	if(keyStates['i']){
		size_t h = 1;
		
	}

	if (keyStates['h']){
		keyStates['h'] = false;
		cout<<cam->eyex<<" "<<cam->eyey<<" "<<cam->eyez<<endl; 
	}
	if (keyStates['g']){
		keyStates['g'] = false;
		
	}

	if (keyStates['p']){
		keyStates['p'] = false;
		
	}else if (keyStates['l']){
		keyStates['l'] = false;
		
	}
	if (keyStates['u']){
		keyStates['u'] = false;
		
	}else if (keyStates['k']){
		keyStates['k'] = false;
		
	}

	if (keyStates['j']){
		keyStates['j']=false;
		size_t u = 1;
		
	}

	if (keyStates[';']){
		keyStates[';']=false;
		size_t u = 0;
		
	}

	if (keyStates['m']){
		keyStates['m']=false;
		size_t u = 1;
		
	}

	if (keyStates['/']){
		keyStates['/']=false;
		size_t u = 0;
		
	}
} 

void keySpecialOperations(void) {  
	if (cameratype=="follow"){
		if (keySpecialStates[GLUT_KEY_LEFT]) { // If the left arrow key has been pressed  
			keySpecialStates[GLUT_KEY_LEFT] = false;
			if (!pacman->moving){
				thread t1(&Pac::moveLeft,pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_RIGHT]) { // If the right arrow key has been pressed  
			keySpecialStates[GLUT_KEY_RIGHT] = false;
			if (!pacman->moving){
				thread t1(&Pac::moveRight,pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_UP]) { // If the up arrow key has been pressed  
			keySpecialStates[GLUT_KEY_UP] = false;
			if (!pacman->moving){
				thread t1(&Pac::moveForward,pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_DOWN]) { // If the down arrow key has been pressed  
			keySpecialStates[GLUT_KEY_DOWN] = false;
			if (!pacman->moving){
				thread t1(&Pac::moveBack,pacman);		
				t1.detach();
			}
		}
	}else{
		if (keySpecialStates[GLUT_KEY_LEFT]) { // If the left arrow key has been pressed  
			keySpecialStates[GLUT_KEY_LEFT] = false;
			pacman->orientn[0] = -1;
			pacman->orientn[1] = 0;
			pacman->orientn[2] = 0;
		}
		if (keySpecialStates[GLUT_KEY_RIGHT]) { // If the right arrow key has been pressed  
			keySpecialStates[GLUT_KEY_RIGHT] = false;
			pacman->orientn[0] = 1;
			pacman->orientn[1] = 0;
			pacman->orientn[2] = 0;
		}
		if (keySpecialStates[GLUT_KEY_UP]) { // If the up arrow key has been pressed  
			keySpecialStates[GLUT_KEY_UP] = false;
			pacman->orientn[0] = 0;
			pacman->orientn[1] = 0;
			pacman->orientn[2] = -1;
		}
		if (keySpecialStates[GLUT_KEY_DOWN]) { // If the down arrow key has been pressed  
			keySpecialStates[GLUT_KEY_DOWN] = false;
			pacman->orientn[0] = 0;
			pacman->orientn[1] = 0;
			pacman->orientn[2] = 1;
		}
	}

	if (keySpecialStates[GLUT_KEY_F5] || keySpecialStates[GLUT_KEY_F6]){
		if (keySpecialStates[GLUT_KEY_F6]){
		
			keySpecialStates[GLUT_KEY_F6] = false;
		}
		keySpecialStates[GLUT_KEY_F5] = false;
		
	}

	if (keySpecialStates[GLUT_KEY_F7]){
		keySpecialStates[GLUT_KEY_F7] = false;
		
	}else if (keySpecialStates[GLUT_KEY_F8]){
		keySpecialStates[GLUT_KEY_F8] = false;
		
	}
}

void keyPressed (unsigned char key, int x, int y) {  
	keyStates[key] = true; // Set the state of the current key to pressed 
	if (glutGetModifiers() & GLUT_ACTIVE_SHIFT){
		SHIFT = true;
	}else {
		SHIFT = false;
	}
	if (glutGetModifiers() & GLUT_ACTIVE_CTRL){
		CTRL = true;
	}else {
		CTRL = false;
	}
	if (glutGetModifiers() & GLUT_ACTIVE_ALT){
		ALT = true;
	}else {
		ALT = false;
	}
}  

void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false; // Set the state of the current key to not pressed  
}

void keySpecial (int key, int x, int y) {
	keySpecialStates[key] = true;
} 

void keySpecialUp (int key, int x, int y) {  
	keySpecialStates[key] = false;
}

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
	// KeyBoard Operations
	keyOperations();
	keySpecialOperations();

	// Background Color: Black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity(); 
	if (cameratype=="free"){
		gluLookAt(cam->eyex, cam->eyey, cam->eyez, cam->centerx, cam->centery, cam->centerz, cam->upx, cam->upy, cam->upz);
	}else if (cameratype=="top"){
		gluLookAt(0.,maze->size[0],maze->size[2],0.,0.,0.,0.,1.,0.);
	}else if (cameratype=="follow"){
		gluLookAt(pacman->position[0]-3*pacman->orientn[0],
			pacman->position[1]-3*pacman->orientn[1]+max(maze->size[0],maze->size[2])/5.f,
			pacman->position[2]-3*pacman->orientn[2],
			pacman->position[0],pacman->position[1],pacman->position[2],0.,1.,0.);
	}else{
		gluLookAt(0.,max(maze->size[0],maze->size[2]),0.,0.,0.,0.,0.,0.,-1.);
	}
	
	// Solid Cylinder
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCylinder(0.2, 1.0, 10, 10);
	
	if (maze){
		maze->draw();
	}
	if (pacman){
		if (!pacman->moving) pacman->moveForward();
		pacman->draw();
	}
	glPopMatrix();
	
	glutSwapBuffers();  
}

int main(int argc, char** argv){
	fInit();
	cam = new Camera();
	maze = new Maze();
	pacman = new Pac(maze);
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
	
	// KeyBoard Triggers
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events    
	glutSpecialFunc(keySpecial); // Tell GLUT to use the method "keySpecial" for special key presses  
	glutSpecialUpFunc(keySpecialUp); // Tell GLUT to use the method "keySpecialUp" for special up key events  

	



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