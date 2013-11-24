/******************************************************************************
* Project	:	3D_Pacman 
* Authors	:	Abhishek Kumar & Nikhil Verma
* Course	:	CSL781 Computer Graphics (Fall, 2013)
* Instructor:	Subodh Kumar
* Started on:	15-Oct-2013
* Ended on	:	28-Nov-2013
* Motivation:	http://freepacmanforacause.webs.com/pacman_1.gif

******************************************************************************/

// TIPS:
	// [Esc] [q] [Q]				--> Quit
	// [F5]							--> Restart
	// [Arrow Keys]					--> Controls Pacman
	// [W] [A] [S] [D]				--> Controls Camera
	// [1] [2] [3] [4] [5] [6] [7]	--> Camera Modes
	// [Enter] [Space]				--> Pause
	
	// Drag Mouse to change direction of camera // TODO: NOT SURE IF SHOULD BE DONE

// RULES: 
	// Code should be well documented and well formatted
	// Never push the code unless dropbox in the task bar shows a green check
	// Code should be generic and hack-less
	// Any line of code should not exceed 80 characters, fold it if does
	// No warnings during compilation
	
// TODO: Before Mid Evaluation
	// [Done] Create Maze	
	// [Done] Create Ghost   -> .obj
	// [Done] Create Pac	 ->.obj
	// [Done] Movement
	// [Done] Animation	
	// [Done] Reflection
	// [Done] Lighting
	// [Done] Collision with walls and eating pallets

// 1. Game.cpp
// 2. Optimizations

// DO:
	// Color3 class is of no use
	// Start Screen
	// Console Controls - Debug Statements
	// Initial Camera Rotation
	// Minimap
	// Skybox
	// Performance Optimizations
	// Sun
	// Water
	// Shadows
	// Environment mapping
	// Documentation
	// Presentations
	// Class game - Object oriented 
	// Level 2
	// Power Up pallets
	// Ghosts movement Algorithms
	// Sun
	// Texture mapping on walls
	// Object loading for ghosts
	// Points on screen

// Not Do
	// Multiplayer
	// Height Map
	// Sounds

// includes all common headers
#include "Headers.h" 
#include "Functions.h"
#include "Camera.h"
#include "Game.h"

// Global Variables
Camera *cam = new Camera();;
Game *game = new Game();

// Keys Capture
bool keyStates[256];// = new bool[256];
bool keySpecialStates[256]; // = new bool[256]; // Create an array of boolean values of length 256 (0-255) 
bool SHIFT = false, ALT = false, CTRL = false;

// Optimization Variables
vf pacPosition;


// If reflection is on
bool IS_REFLECT = false;

// Main Init Function
void mInit(){
	cam = new Camera();
	game = new Game();
	pacPosition.resize(3);
	pacPosition = game->pacman->position;
}

// Fram Calulation
unsigned int iterations = 0, frames = 0;

void frameCalculatorLoop(void){
	Sleep(1000);
	frames = iterations;
	iterations = 0;
}

void keyOperations (void) {  
	// Press Q to Quit
	if (keyStates['q'] || keyStates['Q'] || keyStates[27]){
		exit(0);
	}

	// Press 0 or . move in z-axis
	if(keyStates['0']){
		cam->eyez += 0.1f;
	}else if(keyStates['.']){
		cam->eyez -= 0.1f;
	}
	
	// Press WASD to move camera
	double deg = 1.;
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

	// Press + or - to move camera in y-axis
	if(keyStates['-']){
		cam->eyey += exp(cam->eyey/100.f)/100.f;
	}else if(keyStates['+']){
		cam->eyey -= exp(cam->eyey/100.f)/100.f;
	}

	// Camera Modes
	if (keyStates['1']) { 
		cam->cameratype = ARIEL;
	}else if (keyStates['2']) { 
		cam->cameratype = FREE;
	}else if (keyStates['3']) { 
		cam->cameratype = FOLLOW;
	}else if (keyStates['4']) { 
		cam->cameratype = TOP;
	}else if (keyStates['5']) { 
		cam->cameratype = FRONT;
	}else if (keyStates['6']) { 
		cam->cameratype = C_FIXED;
	}else if (keyStates['7']){
		cam->cameratype = NOTFIXED;
	}
	
	// Press Space or Enter to Pause
	if (keyStates[13] || keyStates[32]){
		keyStates[13] = false;
		keyStates[32] = false;
		game->togglePause();
	}

	// Reflection
	if (keyStates['r']){
		keyStates['r']=false;
		IS_REFLECT = !IS_REFLECT;
	}
} 

void keySpecialOperations(void) {  
	if (cam->cameratype==FOLLOW){
		if (keySpecialStates[GLUT_KEY_LEFT]) { // If the left arrow key has been pressed  
			keySpecialStates[GLUT_KEY_LEFT] = false;
			if (!game->pacman->moving){
				thread t1(&Pac::moveLeft,game->pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_RIGHT]) { // If the right arrow key has been pressed  
			keySpecialStates[GLUT_KEY_RIGHT] = false;
			if (!game->pacman->moving){
				thread t1(&Pac::moveRight,game->pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_UP]) { // If the up arrow key has been pressed  
			keySpecialStates[GLUT_KEY_UP] = false;
			if (!game->pacman->moving){
				thread t1(&Pac::moveForward,game->pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_DOWN]) { // If the down arrow key has been pressed  
			keySpecialStates[GLUT_KEY_DOWN] = false;
			if (!game->pacman->moving){
				thread t1(&Pac::moveBack,game->pacman);		
				t1.detach();
			}
		}
	}else if (cam->cameratype==FRONT){
		if (keySpecialStates[GLUT_KEY_LEFT]) { // If the left arrow key has been pressed  
			keySpecialStates[GLUT_KEY_LEFT] = false;
			if (!game->pacman->moving){
				thread t1(&Pac::moveRight,game->pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_RIGHT]) { // If the right arrow key has been pressed  
			keySpecialStates[GLUT_KEY_RIGHT] = false;
			if (!game->pacman->moving){
				thread t1(&Pac::moveLeft,game->pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_UP]) { // If the up arrow key has been pressed  
			keySpecialStates[GLUT_KEY_UP] = false;
			if (!game->pacman->moving){
				thread t1(&Pac::moveBack,game->pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_DOWN]) { // If the down arrow key has been pressed  
			keySpecialStates[GLUT_KEY_DOWN] = false;
			if (!game->pacman->moving){
				thread t1(&Pac::moveForward,game->pacman);		
				t1.detach();
			}
		}
	}
	else{
		if (keySpecialStates[GLUT_KEY_LEFT] && !( game->pacman->orientn[0] == -1 && game->pacman->orientn[1] == 0 && game->pacman->orientn[2] == 0)) { 
			// If the left arrow key has been pressed  
			keySpecialStates[GLUT_KEY_LEFT] = false;
			game->pacman->orientn[0] = -1;
			game->pacman->orientn[1] = 0;
			game->pacman->orientn[2] = 0;
			game->pacman->integralPosition();
		}
		if (keySpecialStates[GLUT_KEY_RIGHT] && !( game->pacman->orientn[0] == 1 && game->pacman->orientn[1] == 0 && game->pacman->orientn[2] == 0)) { 
			// If the right arrow key has been pressed  
			keySpecialStates[GLUT_KEY_RIGHT] = false;
			game->pacman->orientn[0] = 1;
			game->pacman->orientn[1] = 0;
			game->pacman->orientn[2] = 0;
			game->pacman->integralPosition();
		}
		if (keySpecialStates[GLUT_KEY_UP] && !( game->pacman->orientn[0] == 0 && game->pacman->orientn[1] == 0 && game->pacman->orientn[2] == -1)) { 
			// If the up arrow key has been pressed  
			keySpecialStates[GLUT_KEY_UP] = false;
			game->pacman->orientn[0] = 0;
			game->pacman->orientn[1] = 0;
			game->pacman->orientn[2] = -1;
			game->pacman->integralPosition();
		}
		if (keySpecialStates[GLUT_KEY_DOWN] && !( game->pacman->orientn[0] == 0 && game->pacman->orientn[1] == 0 && game->pacman->orientn[2] == 1)) { 
			// If the down arrow key has been pressed  
			keySpecialStates[GLUT_KEY_DOWN] = false;
			game->pacman->orientn[0] = 0;
			game->pacman->orientn[1] = 0;
			game->pacman->orientn[2] = 1;
			game->pacman->integralPosition();
		}
	}

	if (keySpecialStates[GLUT_KEY_F5] || keySpecialStates[GLUT_KEY_F6]){
		if (keySpecialStates[GLUT_KEY_F6]){
		
			keySpecialStates[GLUT_KEY_F6] = false;
		}
		keySpecialStates[GLUT_KEY_F5] = false;
		mInit();
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

	// Write FPS
	if (iterations==0){
		cout<<"FPS: "<<frames<<endl;
		thread fps(frameCalculatorLoop);
		fps.detach();
	}
	iterations++;

	// Background Color: Black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

	//glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity(); 

	// Cache pacman position
	game->pacman->posmtx.lock();
	pacPosition = game->pacman->position;
	game->pacman->posmtx.unlock();
	

	game->pacman->ormtx.lock();
	game->pacman->ormtx.unlock();
	// SetCamera Postion	
	// Camera is Ariel: Full view of board from top at an angle
	if (cam->cameratype==ARIEL){
		gluLookAt(0.,game->maze->size[0],game->maze->size[2],0.,0.,0.,0.,1.,0.);
	}
	// Camera is Free: Camera is free to move with looking at (0,0,0)
	else if (cam->cameratype==FREE){
		gluLookAt(cam->eyex, cam->eyey, cam->eyez, cam->centerx, cam->centery, cam->centerz, cam->upx, cam->upy, cam->upz);
	}
	// Camre is Follow: Camera is following pacman like in temple run
	else if (cam->cameratype==FOLLOW){
		int multiplier = 50*game->pacman->speed;
		gluLookAt(
			pacPosition[0]-multiplier*game->pacman->orientn[0],
			pacPosition[1]+min(10.f,multiplier*game->pacman->orientn[1]+max(game->maze->size[0],game->maze->size[2])/5.f),
			pacPosition[2]-multiplier*game->pacman->orientn[2],
			pacPosition[0],pacPosition[1],pacPosition[2],0.,1.,0.);
	}
	// Camera is Top: Top view of the maze
	else if (cam->cameratype==TOP){
		gluLookAt(0.,max(game->maze->size[0],game->maze->size[2]),0.,0.,0.,0.,0.,0.,-1.);
	}
	// Camera is Front: front view of pacman following
	else if (cam->cameratype==FRONT){
		int multiplier = 100*game->pacman->speed;
		gluLookAt(pacPosition[0]+multiplier*game->pacman->orientn[0],
			pacPosition[1]+multiplier*game->pacman->orientn[1]+max(game->maze->size[0],game->maze->size[2])/5.f,
			pacPosition[2]+multiplier*game->pacman->orientn[2],
			pacPosition[0],pacPosition[1],pacPosition[2],0.,1.,0.);
	}
	// Camera is C_Fixed: Ariel view of pacman following him
	else if (cam->cameratype==C_FIXED){
		gluLookAt(pacPosition[0]+3.f,
			pacPosition[1]+0.f+max(game->maze->size[0],game->maze->size[2])/5.f,
			pacPosition[2]+3.f,
			pacPosition[0],pacPosition[1],pacPosition[2],0.,1.,0.);
	}
	// Camera is NOTFIXED: Camera can move always looking at pacman (like in cricket match following ball)
	else if (cam->cameratype==NOTFIXED){
		gluLookAt(cam->eyex, cam->eyey, cam->eyez,pacPosition[0],pacPosition[1],pacPosition[2], cam->upx, cam->upy, cam->upz);
	}

	// Solid Cylinder
	/*glColor3f(1.0, 0.0, 0.0);
	glutSolidCylinder(0.2, 1.0, 10, 10);*/

	/*************************************************************reflection*************************************************/
	if (IS_REFLECT){

		/* Don't update color or depth. */
		glDisable(GL_DEPTH_TEST);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		/* Draw 1 into the stencil buffer. */
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

		/* Now drawing the floor just tags the floor pixels
			as stencil value 1. */
		glColor4f(0.0f, 0.7f, 0.0f, 0.30);  
		glBegin(GL_QUADS);
		glNormal3f(0.f,1.f,0.f);
			glVertex3f(-game->maze->size[0]/2, 0.0f, -game->maze->size[2]/2);
			glVertex3f(-game->maze->size[0]/2, 0.0f, game->maze->size[2]/2);
			glVertex3f(game->maze->size[0]/2, 0.0f, game->maze->size[2]/2);
			glVertex3f(game->maze->size[0]/2, 0.0f, -game->maze->size[2]/2);
		glEnd();

		/* Re-enable update of color and depth. */ 
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glEnable(GL_DEPTH_TEST);

		/* Now, only render where stencil is set to 1. */
		glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if stencil ==1 */
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		/* Draw reflected ninja, but only where floor is. */
		glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
    
		game->draw();
		glPopMatrix();

		glDisable(GL_STENCIL_TEST);  
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.7f, 0.7f, 0.10f);  
		glBegin(GL_QUADS);
			glNormal3f(0.f,1.f,0.f);
			glVertex3f(-game->maze->size[0]/2, 0.0f, -game->maze->size[2]/2);
			glVertex3f(-game->maze->size[0]/2, 0.0f, game->maze->size[2]/2);
			glVertex3f(game->maze->size[0]/2, 0.0f, game->maze->size[2]/2);
			glVertex3f(game->maze->size[0]/2, 0.0f, -game->maze->size[2]/2);
		glEnd();
		glDisable(GL_BLEND);
	}
	/*********************************************************reflection end*************************************************/

	game->draw();
	glPopMatrix();
	glutSwapBuffers();  
}

int main(int argc, char** argv){
	fInit();	// functions.h init
	mInit();	// main.cpp init

	// Initialise Glut Variables
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH ); // | GLUT_STENCIL 
	glutInitWindowSize (1350, 690);
	glutInitWindowPosition (0, 0); 
	glutCreateWindow ("3D Pacman");

	// Enable Glut Features
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);	//glShadeModel(GL_FLAT);
	glEnable(GL_CULL_FACE);

	glEnable(GL_NORMALIZE);
	glEnable (GL_LIGHTING);
    
	/*GLfloat ambient2[] = {.2f, .2f, .2f, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient2) ;*/


	GLfloat diffuse[] = {0,1,0,1};
	GLfloat ambient[] = {.5,.5,0,1};
	GLfloat specular[] = {.3,.3,.3,1};
	GLfloat shine[]= {100};

	//glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse) ;
	//glLightfv (GL_LIGHT0, GL_AMBIENT, ambient) ;
	//glLightfv (GL_LIGHT0, GL_SPECULAR, specular) ;

	glEnable (GL_LIGHT0);
	GLfloat lightpos1[] = {0., 10., 100., 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient) ;
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);

	/*glEnable (GL_LIGHT1);
	GLfloat lightpos2[] = {-5., 5., 5., 1.};
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);

	glEnable (GL_LIGHT2);
	GLfloat lightpos3[] = {-5., 5.,-5., 1.};
	glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);

	glEnable (GL_LIGHT3);
	GLfloat lightpos4[] = {5., 5., -5., 1.};
	glLightfv(GL_LIGHT3, GL_POSITION, lightpos4);*/

	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// Set display and reshape Triggers
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	
	// KeyBoard Triggers
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events    
	glutSpecialFunc(keySpecial); // Tell GLUT to use the method "keySpecial" for special key presses  
	glutSpecialUpFunc(keySpecialUp); // Tell GLUT to use the method "keySpecialUp" for special up key events  

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Start Main Loop
	glutMainLoop();
	
	return 0;
}
