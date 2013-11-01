/******************************************************************************
* Project	:	3D_Pacman 
* Authors	:	Abhishek Kumar & Nikhil Verma
* Course	:	CSL781 Computer Graphics (Fall, 2013)
* Instructor:	Subodh Kumar
* T.A.		:	Nisha Jain	
* Started on:	15-Oct-2013
* Ended on	:	-Oct-2013
* Motivation:	http://freepacmanforacause.webs.com/pacman_1.gif

******************************************************************************/

// TIPS:
	// Esc,q,Q to Quit
	// F5 to restart the program
	// Arrow Keys to control Pacman
	// WASD to control Camera
	// Drag Mouse to change direction of camera // TODO:
	// 1,2,3,4,5,6,7 to change camera View
	// Enter or Space to Pause

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

// CANDO: 
	// Camera Movement Controls with Mouse
	// Ghosts Movement
	// Mutex Bug
	// Draw Power up pallets
	// Maze Complete
	// Collision with Ghosts
	// Performance Improvement
	// Set start position of Pacs and Ghosts
	// Create Sun
	// 

// TODO: After Mid Evalutaion
	// Levels
	// Shaders
	// Create Start Screen - simple in start i.e. press enter to start game
	// Multplayer
	// Height Map
	// Sound Effects
	
	// 

// includes all common headers
#include "Headers.h" 
#include "Camera.h"
#include "Functions.h"
#include "Pac.h"
#include "Maze.h"
#include "Ghost.h"

// Global Variables
Camera *cam;
string cameratype = "follow";
Pac *pacman;
vector<Ghost*> ghost;
bool ghostsMoving = false;
Maze *maze;
bool gamePaused = false;
unsigned int iterations = 0;
bool keyStates[256];// = new bool[256];
bool keySpecialStates[256]; // = new bool[256]; // Create an array of boolean values of length 256 (0-255) 
bool SHIFT = false, ALT = false, CTRL = false;

void mInit(){
	cam = new Camera();
	maze = new Maze("TheGameMatrix.txt");
	pacman = new Pac(maze);
	ghost.resize(0);
	ghost.push_back(new Ghost(yellow, maze, pacman));
	ghost.push_back(new Ghost(purple, maze, pacman));
	ghost.push_back(new Ghost(pink, maze, pacman));
	ghost.push_back(new Ghost(green, maze, pacman));
}

bool canMove(Agent *p, Maze *m){
	vf next(3);
	for (int i = 0; i < 3; i++){
		p->posmtx.lock();
		p->ormtx.lock();
		next[i] = p->position[i] + p->orientn[i]*p->dimentions[0]/2;
		p->ormtx.unlock();
		p->posmtx.unlock();
	}

	int x = static_cast<int>(next[0]+m->size[0]/2) ;
	int z = static_cast<int>(next[2]+m->size[2]/2) ;
	
	if (x<0|| z<0 || x>m->size[0] || z>m->size[2] || m->mazeMat[z][x]>10){
		return false;
	}else if(m->mazeMat[z][x]==6){
		m->mazeMat[z][x] = 0;
	}
	return true;
}

void randomMoveGhost(int i,int turn = 1){
	if (!ghost[i]->moving){
		int m = 30;
		int r = random(0,m);
		if (r==0){
			thread t1(&Ghost::moveLeft,ghost[i]);
			t1.detach();
			// ghost[i]->moveLeft();
		}else if (r==1){
			thread t1(&Ghost::moveRight,ghost[i]);
			t1.detach();
			// ghost[i]->moveRight();
		}else if (r==2){
			thread t1(&Ghost::moveBack,ghost[i]);
			t1.detach();
			// ghost[i]->moveBack();
		}
	}
}

void keyOperations (void) {  
	if (keyStates['q'] || keyStates['Q'] || keyStates[27]){
		exit(0);
	}
	if(keyStates['0']){
		cam->eyez += 0.1f;
	}else if(keyStates['.']){
		cam->eyez -= 0.1f;
	}
	
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


	if(keyStates['-']){
		cam->eyey += exp(cam->eyey/100.f)/100.f;
	}else if(keyStates['+']){
		cam->eyey -= exp(cam->eyey/100.f)/100.f;
	}


	if (keyStates['1']) { 
		cameratype = "ariel";
	}else if (keyStates['2']) { 
		cameratype = "free";
	}else if (keyStates['3']) { 
		cameratype = "follow";
	}else if (keyStates['4']) { 
		cameratype = "top";
	}else if (keyStates['5']) { 
		cameratype = "front";
	}else if (keyStates['6']) { 
		cameratype = "fixed";
	}else if (keyStates['7']){
		cameratype = "notfixed";
	}
	if (keyStates[13] || keyStates[32]){
		keyStates[13] = false;
		keyStates[32] = false;
		gamePaused = !gamePaused;
	}

	if(keyStates['o']){
		size_t h = 0;
		
	} 
	if(keyStates['i']){
		size_t h = 1;
		
	}

	if (keyStates['h']){
		keyStates['h'] = false;
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
	}else if (cameratype=="front"){
		if (keySpecialStates[GLUT_KEY_LEFT]) { // If the left arrow key has been pressed  
			keySpecialStates[GLUT_KEY_LEFT] = false;
			if (!pacman->moving){
				thread t1(&Pac::moveRight,pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_RIGHT]) { // If the right arrow key has been pressed  
			keySpecialStates[GLUT_KEY_RIGHT] = false;
			if (!pacman->moving){
				thread t1(&Pac::moveLeft,pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_UP]) { // If the up arrow key has been pressed  
			keySpecialStates[GLUT_KEY_UP] = false;
			if (!pacman->moving){
				thread t1(&Pac::moveBack,pacman);		
				t1.detach();
			}
		}
		if (keySpecialStates[GLUT_KEY_DOWN]) { // If the down arrow key has been pressed  
			keySpecialStates[GLUT_KEY_DOWN] = false;
			if (!pacman->moving){
				thread t1(&Pac::moveForward,pacman);		
				t1.detach();
			}
		}
	}
	else{
		if (keySpecialStates[GLUT_KEY_LEFT] && !( pacman->orientn[0] == -1 && pacman->orientn[1] == 0 && pacman->orientn[2] == 0)) { // If the left arrow key has been pressed  
			keySpecialStates[GLUT_KEY_LEFT] = false;
			pacman->orientn[0] = -1;
			pacman->orientn[1] = 0;
			pacman->orientn[2] = 0;
			pacman->integralPosition();
		}
		if (keySpecialStates[GLUT_KEY_RIGHT] && !( pacman->orientn[0] == 1 && pacman->orientn[1] == 0 && pacman->orientn[2] == 0)) { // If the right arrow key has been pressed  
			keySpecialStates[GLUT_KEY_RIGHT] = false;
			pacman->orientn[0] = 1;
			pacman->orientn[1] = 0;
			pacman->orientn[2] = 0;
			pacman->integralPosition();
		}
		if (keySpecialStates[GLUT_KEY_UP] && !( pacman->orientn[0] == 0 && pacman->orientn[1] == 0 && pacman->orientn[2] == -1)) { // If the up arrow key has been pressed  
			keySpecialStates[GLUT_KEY_UP] = false;
			pacman->orientn[0] = 0;
			pacman->orientn[1] = 0;
			pacman->orientn[2] = -1;
			pacman->integralPosition();
		}
		if (keySpecialStates[GLUT_KEY_DOWN] && !( pacman->orientn[0] == 0 && pacman->orientn[1] == 0 && pacman->orientn[2] == 1)) { // If the down arrow key has been pressed  
			keySpecialStates[GLUT_KEY_DOWN] = false;
			pacman->orientn[0] = 0;
			pacman->orientn[1] = 0;
			pacman->orientn[2] = 1;
			pacman->integralPosition();
		}
	}

	if (keySpecialStates[GLUT_KEY_F5] || keySpecialStates[GLUT_KEY_F6]){
		if (keySpecialStates[GLUT_KEY_F6]){
		
			keySpecialStates[GLUT_KEY_F6] = false;
		}
		keySpecialStates[GLUT_KEY_F5] = false;
		mInit();
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

void drawEverything(){
	if (maze ){
		maze->draw();
	}
	if (pacman ){
		if (!pacman->moving && !gamePaused && canMove(pacman,maze)) {
			/*thread t1(&Pac::moveForward,pacman);
			t1.detach();*/
			pacman->moveForward();
		}
		pacman->draw();
	}
	if (ghost.size() ){
		for (size_t i = 0; i < ghost.size(); i++){
			if (!gamePaused && canMove(ghost[i],maze)) {
				thread t1(&Ghost::moveForward,ghost[i]);
				t1.detach();
				//ghost[i]->moveForward();
			}
			ghost[i]->draw();
			if (!ghostsMoving & !gamePaused){
				randomMoveGhost(i,0);
				/*thread t1 (randomMoveGhost,i,0);
				t1.detach();*/
			}
		}
	}
}

void display (void) {
	iterations++;
	// KeyBoard Operations
	keyOperations();
	keySpecialOperations();

	// Background Color: Black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
	//glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity(); 
	pacman->posmtx.lock();
	pacman->ormtx.lock();
	if (cameratype=="free"){
		gluLookAt(cam->eyex, cam->eyey, cam->eyez, cam->centerx, cam->centery, cam->centerz, cam->upx, cam->upy, cam->upz);
	}else if (cameratype=="ariel"){
		gluLookAt(0.,maze->size[0],maze->size[2],0.,0.,0.,0.,1.,0.);
	}else if (cameratype=="follow"){
		int multiplier = 50*pacman->speed;
		gluLookAt(pacman->position[0]-multiplier*pacman->orientn[0],
			pacman->position[1]-multiplier*pacman->orientn[1]+max(maze->size[0],maze->size[2])/5.f,
			pacman->position[2]-multiplier*pacman->orientn[2],
			pacman->position[0],pacman->position[1],pacman->position[2],0.,1.,0.);
	}else if (cameratype=="front"){
		int multiplier = 100*pacman->speed;
		gluLookAt(pacman->position[0]+multiplier*pacman->orientn[0],
			pacman->position[1]+multiplier*pacman->orientn[1]+max(maze->size[0],maze->size[2])/5.f,
			pacman->position[2]+multiplier*pacman->orientn[2],
			pacman->position[0],pacman->position[1],pacman->position[2],0.,1.,0.);
	}else if (cameratype=="fixed"){
		gluLookAt(pacman->position[0]+3.f,
			pacman->position[1]+0.f+max(maze->size[0],maze->size[2])/5.f,
			pacman->position[2]+3.f,
			pacman->position[0],pacman->position[1],pacman->position[2],0.,1.,0.);
	}else if (cameratype=="notfixed"){
		gluLookAt(cam->eyex, cam->eyey, cam->eyez,pacman->position[0],pacman->position[1],pacman->position[2], cam->upx, cam->upy, cam->upz);
	}
	else{
		gluLookAt(0.,max(maze->size[0],maze->size[2]),0.,0.,0.,0.,0.,0.,-1.);
	}
	pacman->posmtx.unlock();
	pacman->ormtx.unlock();
	// Solid Cylinder
	/*glColor3f(1.0, 0.0, 0.0);
	glutSolidCylinder(0.2, 1.0, 10, 10);*/

/*************************************************************reflection*************************************************/
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
		glVertex3f(-maze->size[0]/2, 0.0f, -maze->size[2]/2);
		glVertex3f(-maze->size[0]/2, 0.0f, maze->size[2]/2);
		glVertex3f(maze->size[0]/2, 0.0f, maze->size[2]/2);
		glVertex3f(maze->size[0]/2, 0.0f, -maze->size[2]/2);
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
    
	drawEverything();
	glPopMatrix();

	glDisable(GL_STENCIL_TEST);  
	
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.7f, 0.7f, 0.10f);  
    glBegin(GL_QUADS);
		glNormal3f(0.f,1.f,0.f);
        glVertex3f(-maze->size[0]/2, 0.0f, -maze->size[2]/2);
        glVertex3f(-maze->size[0]/2, 0.0f, maze->size[2]/2);
        glVertex3f(maze->size[0]/2, 0.0f, maze->size[2]/2);
        glVertex3f(maze->size[0]/2, 0.0f, -maze->size[2]/2);
    glEnd();
	glDisable(GL_BLEND);

	drawEverything();
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
