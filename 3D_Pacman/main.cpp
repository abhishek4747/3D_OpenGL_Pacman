/******************************************************************************
* Project	:	3D_Pacman 
* Authors	:	Abhishek Kumar & Nikhil Verma
* Course	:	CSL781 Computer Graphics (Fall, 2013)
* Instructor:	Subodh Kumar
* Started on:	15-Oct-2013
* Ended on	:	28-Nov-2013
* Motivation:	http://freepacmanforacause.webs.com/pacman_1.gif

******************************************************************************/

// Controls:
	// [Esc] [q] [Q]				--> Quit
	// [F5]							--> Restart
	// [F11]						--> Full Screen
	// [Arrow Keys]					--> Controls Pacman
	// [W] [A] [S] [D]				--> Controls Camera
	// [1] [2] [3] [4] [5] [6] [7]	--> Camera Modes
	// [Enter] [Space]				--> Pause
	// [r] [R]						--> Reflection
	// [v] [V]						--> Minimap
	// [p] [P]						--> Polygon Modal
	// [k] [K]						--> Sky Box

// RULES: 
	// Code should be well documented and well formatted
	// Never push the code unless dropbox in the task bar shows a green check
	// Code should be generic and hack-less
	// Any line of code should not exceed 80 characters, fold it if does
	// No warnings during compilation
	
// TODO: Before Mid Evaluation
	// [Done] Create Maze	
	// [Done] Create Ghost   
	// [Done] Create Pac
	// [Done] Movement
	// [Done] Animation	
	// [Done] Reflection
	// [Done] Lighting
	// [Done] Collision with walls and eating pallets

// 1. Game.cpp
// 2. Optimizations
// 3. Minimap
// 4. Warp Gate

// Finishing: 
	// Eyes for pacman
	// Eyes for Ghosts
	// Pacman Mouth Animation
	// Abort Error Fix
	// Level 2 

// DO:
	// Start Screen
	// Initial Camera Rotation
	// Ghosts movement Algorithms

	// Texture mapping on walls

	// Sun
	// Water
	// Shadows
	// Shaders
	// Environment mapping
	// Fog

	// [3 hour] [Post 12 PM]
	// Finishing
	// Documentation
	// Presentations

// Not Doing
	// Multiplayer : Less Time
	// AI : Less Time 
	// Height Map :  
	// Sounds : Do not use opengl So didn't do
	
	// Drag Mouse Change camera
	// Object Loading for Ghosts

// includes all common headers
#include "Headers.h" 
#include "Functions.h"
#include "Camera.h"
#include "Game.h"

// Global Variables
Camera *cam = new Camera();;
Game *game = new Game();

// Main Global Variables
BOOL fullscreen = TRUE;
bool polygonModal = false;

bool first = true;
bool IS_REFLECT = false; // If reflection is on
bool miniMapOn = true;
bool skyBoxOn = false;
string message = "";

// 0. Tex
// 1. Front
// 2. Back
// 3. Top
// 4. Bottom
// 5. Right
// 6. Left

// Constants
const int W_WIDTH = 1350;
const int W_HEIGHT = 690;
const int W_POS_X = 0;
const int W_POS_Y = 0;
const float heightHUD = 40.f;

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

// Keys Capture
bool keyStates[256];// = new bool[256];
bool keySpecialStates[256]; // = new bool[256]; // Create an array of boolean values of length 256 (0-255) 
bool SHIFT = false, ALT = false, CTRL = false;

// Optimization Variables
vf pacPosition;

// Main Init Function
bool mInit(){
	cam = new Camera();
	game = new Game();
	pacPosition.resize(3);
	pacPosition = game->pacman->position;

	// Ask User to switch to full screen or not
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO){
		fullscreen=FALSE;							// Windowed Mode
	}
	return true;
}

// Frame Calulation
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
		keyStates['1'] = false;
		cam->cameratype = ARIEL;
	}else if (keyStates['2']) { 
		keyStates['2'] = false;
		cam->cameratype = FREE;
	}else if (keyStates['3']) { 
		keyStates['3'] = false;
		cam->cameratype = FOLLOW;
	}else if (keyStates['4']) { 
		keyStates['4'] = false;
		cam->cameratype = TOP;
	}else if (keyStates['5']) { 
		keyStates['5'] = false;
		cam->cameratype = FRONT;
	}else if (keyStates['6']) { 
		keyStates['6'] = false;
		cam->cameratype = C_FIXED;
	}else if (keyStates['7']){
		keyStates['7'] = false;
		cam->cameratype = NOTFIXED;
	}
	
	// Press Space or Enter to Pause
	if (keyStates[13] || keyStates[32]){
		keyStates[13] = false;
		keyStates[32] = false;
		game->togglePause();
	}

	// Reflection
	if (keyStates['r'] || keyStates['R']){
		keyStates['r'] = false;
		keyStates['R'] = false;
		IS_REFLECT = !IS_REFLECT;
	}

	// Minimap
	if (keyStates['v'] || keyStates['V']){
		keyStates['v'] = false;
		keyStates['V'] = false;
		miniMapOn = !miniMapOn;
	}

	// SkyBox
	if (keyStates['k'] || keyStates['K']){
		keyStates['k'] = false;
		keyStates['K'] = false;
		skyBoxOn = !skyBoxOn;
	}

	// Polygon Modal
	if (keyStates['p'] || keyStates['P']){
		keyStates['p'] = false;
		keyStates['P'] = false;
		polygonModal = !polygonModal;
		if (polygonModal){
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}else{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
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

	if (keySpecialStates[GLUT_KEY_F11]){
		keySpecialStates[GLUT_KEY_F11] = false;
		fullscreen = !fullscreen;
		if (fullscreen){
			glutFullScreen();
		}else{
			glutPositionWindow(W_POS_X,W_POS_Y);
			glutReshapeWindow(W_WIDTH, W_HEIGHT);
		}
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
	if (game->isPaused()) game->togglePause();
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
	gluPerspective(60, (GLfloat)width / (GLfloat)height, .1, 1000.0); 	
	
	// Switch back to the model view matrix, so that we can start drawing 
	// shapes correctly
	glMatrixMode(GL_MODELVIEW);   
}

void adjustCamera(){
	// Cache pacman position
	game->pacman->posmtx.lock();
	pacPosition = game->pacman->position;
	game->pacman->posmtx.unlock();
	
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
}

void primaryView(bool called_from_secondary = false){
	if (IS_REFLECT && !called_from_secondary){

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
	game->draw();
}

void secondaryView(){
	glDisable(GL_DEPTH_TEST);
	gluLookAt(0.,max(game->maze->size[0],game->maze->size[2]),0.,0.,0.,0.,0.,0.,-1.);
	primaryView(true);
}

void scissor_viewport(GLint x, GLint y, GLsizei w, GLsizei h){
    glScissor(x,y,w,h);
    glViewport(x,y,w,h);
}

void printText(int x, int y, float r, float g, float b, char *string){
	glPushMatrix();
	//glLoadIdentity();
	glColor3f( r, g, b );
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
	glPopMatrix();	
}

AUX_RGBImageRec *LoadBMP(char *Filename){				// Loads A Bitmap Image
	FILE *File=NULL;									// File Handle
	if (!Filename){										// Make Sure A Filename Was Given
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File){											// Does The File Exist?
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}
	return NULL;										// If Load Failed Return NULL
}

bool LoadGLTextures(){									// Load Bitmaps And Convert To Textures
	bool Status = true;									// Status Indicator
	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture
	char *textureFileNames[] = {"images/tex.bmp","images/front.bmp","images/back.bmp","images/up.bmp","images/down.bmp","images/right.bmp","images/left.bmp", "images/Reflect.bmp"};
	int textureFilesCount = sizeof(textureFileNames)/sizeof(textureFileNames[0]);
	for (int i = 0; i <textureFilesCount && Status ; i++){
		memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL
		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if (TextureImage[0]=LoadBMP(textureFileNames[i])){
			glGenTextures(1, &texture[i]);					// Create The Texture

			// Typical Texture Generation Using Data From The Bitmap
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}else{
			cout<<textureFileNames[i]<<" Unable to read!!"<<endl;
			Status = false;
		}

		if (TextureImage[0]){									// If Texture Exists
			if (TextureImage[0]->data){							// If Texture Image Exists
				free(TextureImage[0]->data);					// Free The Texture Image Memory
			}
			free(TextureImage[0]);								// Free The Image Structure
		}
	}
	
	return Status;										// Return The Status
}

bool skyBox(float siz){
	// Save Current Matrix
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	
	glColor4f(1.0, 1.0, 1.0,1.0f);
	int rn = -1; // reverse normal
	// Second Move the render space to the correct position (Translate)
	//glTranslatef(position.x,position.y,position.z);

	glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);        
    glBindTexture(GL_TEXTURE_2D,texture[2]);  
    glBegin(GL_QUADS);      
            //back face
            glTexCoord2f(0,0);
            glVertex3f(siz/2,siz/2,siz/2);
			glNormal3f(0.f,0.f,rn*1.f);
            
			glTexCoord2f(1,0);      
            glVertex3f(-siz/2,siz/2,siz/2);
            glNormal3f(0.f,0.f,rn*1.f);

			glTexCoord2f(1,1);
            glVertex3f(-siz/2,-siz/2,siz/2);
            glNormal3f(0.f,0.f,rn*1.f);
			
			glTexCoord2f(0,1);
            glVertex3f(siz/2,-siz/2,siz/2);
			glNormal3f(0.f,0.f,rn*1.f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,texture[6]);
    glBegin(GL_QUADS);     
            //left face
            glTexCoord2f(0,0);
            glVertex3f(-siz/2,siz/2,siz/2);
			glNormal3f(-1.f*rn,0.f,0.f);

            glTexCoord2f(1,0);
            glVertex3f(-siz/2,siz/2,-siz/2);
            glNormal3f(-1.f*rn,0.f,0.f);

			glTexCoord2f(1,1);
            glVertex3f(-siz/2,-siz/2,-siz/2);
            glNormal3f(-1.f*rn,0.f,0.f);

			glTexCoord2f(0,1);
            glVertex3f(-siz/2,-siz/2,siz/2);
			glNormal3f(-1.f*rn,0.f,0.f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    glBegin(GL_QUADS);     
            //front face
            glTexCoord2f(1,0);
            glVertex3f(siz/2,siz/2,-siz/2);
			glNormal3f(0.f,0.f,-1.f*rn);

            glTexCoord2f(0,0);
            glVertex3f(-siz/2,siz/2,-siz/2);
            glNormal3f(0.f,0.f,-1.f*rn);

			glTexCoord2f(0,1);
            glVertex3f(-siz/2,-siz/2,-siz/2);
            glNormal3f(0.f,0.f,-1.f*rn);

			glTexCoord2f(1,1);
            glVertex3f(siz/2,-siz/2,-siz/2);
			glNormal3f(0.f,0.f,-1.f*rn);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    glBegin(GL_QUADS);     
            //right face
            glTexCoord2f(0,0);
            glVertex3f(siz/2,siz/2,-siz/2);
			glNormal3f(1.f*rn,0.f,0.f);

            glTexCoord2f(1,0);
            glVertex3f(siz/2,siz/2,siz/2);
			glNormal3f(1.f*rn,0.f,0.f);

            glTexCoord2f(1,1);
            glVertex3f(siz/2,-siz/2,siz/2);
			glNormal3f(1.f*rn,0.f,0.f);

            glTexCoord2f(0,1);
            glVertex3f(siz/2,-siz/2,-siz/2);
			glNormal3f(1.f*rn,0.f,0.f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,texture[3]);          
    glBegin(GL_QUADS);                      //top face
            glTexCoord2f(1,0);
            glVertex3f(siz/2,siz/2,siz/2);
			glNormal3f(0.f,1.f*rn,0.f);

            glTexCoord2f(0,0);
            glVertex3f(-siz/2,siz/2,siz/2);
			glNormal3f(0.f,1.f*rn,0.f);

            glTexCoord2f(0,1);
            glVertex3f(-siz/2,siz/2,-siz/2);
			glNormal3f(0.f,1.f*rn,0.f);

            glTexCoord2f(1,1);
            glVertex3f(siz/2,siz/2,-siz/2);
			glNormal3f(0.f,1.f*rn,0.f);
    glEnd();
	glBindTexture(GL_TEXTURE_2D,texture[4]);               
    glBegin(GL_QUADS);     
            //bottom face
            glTexCoord2f(1,1);
            glVertex3f(siz/2,-10.f,siz/2);
			//glVertex3f(siz/2,-siz/2,siz/2);
			glNormal3f(0.f,-1.f*rn,0.f);

            glTexCoord2f(0,1);
            glVertex3f(-siz/2,-10.f,siz/2);
			//glVertex3f(-siz/2,-siz/2,siz/2);
			glNormal3f(0.f,-1.f*rn,0.f);

            glTexCoord2f(0,0);
            glVertex3f(-siz/2,-10.f,-siz/2);
			//glVertex3f(-siz/2,-siz/2,-siz/2);
			glNormal3f(0.f,-1.f*rn,0.f);

            glTexCoord2f(1,0);
            glVertex3f(siz/2,-10.f,-siz/2);
			//glVertex3f(siz/2,-siz/2,-siz/2);
			glNormal3f(0.f,-1.f*rn,0.f);
    glEnd();
	glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

	// Load Saved Matrix
	glPopAttrib();
	glPopMatrix();
	return true;
}

bool drawBox(GLvoid){									// Here's Where We Do All The Drawing
	glPushMatrix();
	//glLoadIdentity();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	//glLoadIdentity();									// Reset The View

	glBindTexture(GL_TEXTURE_2D, texture[0]); //
	vf one, two;
	one.push_back(1.f); one.push_back(1.f); one.push_back(1.f);
	two.push_back(-1.f); two.push_back(-1.f); two.push_back(-1.f);
	glColor3f(1.f,1.f,1.f);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); glNormal3f(0.0f, 0.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); glNormal3f(0.0f, 0.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); glNormal3f(0.0f, 0.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); glNormal3f(0.0f, 0.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); glNormal3f(0.0f, 0.0f,  -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); glNormal3f(0.0f, 0.0f,  -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); glNormal3f(0.0f, 0.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); glNormal3f(0.0f, 0.0f,  -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); glNormal3f(0.0f, 1.0f,  0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f); glNormal3f(0.0f, 1.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f); glNormal3f(0.0f, 1.0f,  0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); glNormal3f(0.0f, 1.0f,  0.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); glNormal3f(0.0f, -1.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); glNormal3f(0.0f, -1.0f,  0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); glNormal3f(0.0f, -1.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); glNormal3f(0.0f, -1.0f,  0.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); glNormal3f(1.0f, 0.0f,  0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); glNormal3f(1.0f, 0.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); glNormal3f(1.0f, 0.0f,  0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); glNormal3f(1.0f, 0.0f,  0.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); glNormal3f(-1.0f, 0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); glNormal3f(-1.0f, 0.0f,  0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); glNormal3f(-1.0f, 0.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); glNormal3f(-1.0f, 0.0f,  0.0f);
	glEnd();
	glPopMatrix();
	return true;										// Keep Going
}

void drawHUD(float SCREEN_WIDTH, float SCREEN_HEIGHT ){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();  //      ----Not sure if I need this
	glLoadIdentity();
	//glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);


	glBegin(GL_QUADS);
		glColor3f(yellow.r, yellow.g, yellow.b);
		glVertex2f(0.0, SCREEN_HEIGHT - heightHUD);
		glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT - heightHUD);
		glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
		glVertex2f(0.0, SCREEN_HEIGHT);
	glEnd();
	//drawText("Hello Pacman");
	string HUD_text1 = "FPS: "+to_string(frames);
	printText(40,SCREEN_HEIGHT - 12.f,black.r,black.g,black.b,&HUD_text1[0]);

	string HUD_text2 = "Lives: " + to_string(game->lives);
	printText(240,SCREEN_HEIGHT - 12.f,black.r,black.g,black.b,&HUD_text2[0]);

	string HUD_text3 = "Timer: "+ to_string(game->timer);
	printText(440,SCREEN_HEIGHT - 12.f,black.r,black.g,black.b,&HUD_text3[0]);

	string HUD_text4 = "Score: "+ to_string(game->score);
	printText(640,SCREEN_HEIGHT - 12.f,black.r,black.g,black.b,&HUD_text4[0]);

	if (game->isPaused()){
		message = "Press any key to continue...";
	}else{
		message = "Press space to pause.";
	}

	string HUD_text5 = " "+ message;
	printText(840,SCREEN_HEIGHT - 12.f,black.r,black.g,black.b,&HUD_text5[0]);





	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();     //   ----and this?
}

void display (void) {
	// KeyBoard Operations
	keyOperations();
	keySpecialOperations();

	// Write FPS
	if (iterations==0){
		// cout<<"FPS: "<<frames<<endl;
		thread fps(frameCalculatorLoop);
		fps.detach();
	}
	iterations++;	

	// Background Color: Black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
	glLoadIdentity();

	GLint m_viewport[4];
	glGetIntegerv( GL_VIEWPORT, m_viewport );
	
	glLoadIdentity();
	adjustCamera();
	if (skyBoxOn){
		skyBox(game->maze->size[0]*4);
	}
	
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);
    scissor_viewport(m_viewport[0],m_viewport[1],m_viewport[2],m_viewport[3]);
    primaryView();

	if (miniMapOn){
		glLoadIdentity();
		glClear(GL_DEPTH_BUFFER_BIT);
		scissor_viewport(m_viewport[0],(m_viewport[1]*4)/5 + heightHUD,m_viewport[2]/5,m_viewport[3]/5);
		secondaryView();
	}
	scissor_viewport(m_viewport[0],m_viewport[1],m_viewport[2],m_viewport[3]);

	drawHUD(m_viewport[2],m_viewport[3]);
	glutSwapBuffers();  
}

bool glInit(int argc, char** argv){
	// Initialise Glut Window
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH ); // | GLUT_STENCIL 
	if (fullscreen){
		glutCreateWindow ("3D Pacman");
		glutFullScreen();
	}else{
		glutInitWindowSize (W_WIDTH, W_HEIGHT);
		glutInitWindowPosition (W_POS_X, W_POS_Y); 
		glutCreateWindow ("3D Pacman");
	}

	// Load Textures to be used later
	if (!LoadGLTextures()){
		cout<<"Unable to load textures!!"<<endl;
		return false;
	}

	// Enable required parameters for glut
	glEnable(GL_TEXTURE_2D);	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);	//or glShadeModel(GL_FLAT);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One

	quadratic=gluNewQuadric();							// Create A Pointer To The Quadric Object (Return 0 If No Memory)
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals 
	gluQuadricTexture(quadratic, GL_TRUE);				// Create Texture Coords 

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For T To Sphere Mapping (NEW)


	// Set display and reshape Triggers
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	
	// KeyBoard Triggers
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events    
	glutSpecialFunc(keySpecial); // Tell GLUT to use the method "keySpecial" for special key presses  
	glutSpecialUpFunc(keySpecialUp); // Tell GLUT to use the method "keySpecialUp" for special up key events  

	////////////// Lighting ////////////////////
	/*GLfloat ambient2[] = {.2f, .2f, .2f, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient2) ;*/


	//GLfloat diffuse[] = {0,1,0,1};
	//GLfloat ambient[] = {.5,.5,0,1};
	//GLfloat specular[] = {.3,.3,.3,1};
	//GLfloat shine[]= {100};

	////glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse) ;
	////glLightfv (GL_LIGHT0, GL_AMBIENT, ambient) ;
	////glLightfv (GL_LIGHT0, GL_SPECULAR, specular) ;

	//glEnable (GL_LIGHT0);
	//GLfloat lightpos1[] = {0., 10., 100., 1.};
	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient) ;
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, shine);

	///*glEnable (GL_LIGHT1);
	//GLfloat lightpos2[] = {-5., 5., 5., 1.};
	//glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);

	//glEnable (GL_LIGHT2);
	//GLfloat lightpos3[] = {-5., 5.,-5., 1.};
	//glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);

	//glEnable (GL_LIGHT3);
	//GLfloat lightpos4[] = {5., 5., -5., 1.};
	//glLightfv(GL_LIGHT3, GL_POSITION, lightpos4);*/

	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	return true;
}

/******************************************************************************
 * main() : is called when program starts
 *	Initializes functions.h variables
 *  Initializes global main variables
 *	Initializes opengl window and set different glut variables
 *  starts game display and movement
******************************************************************************/
int main(int argc, char** argv){

	if (!fInit()){	// functions.h init
		cout<<"Unable to Initialize Functions in function.cpp"<<endl;
		getchar();
		return 0;
	}
	if (!mInit()){	// main.cpp init
		cout<<"Unable to Initialize Functions in main.cpp"<<endl;
		getchar();
		return 0;
	}
	if (!glInit(argc, argv)){ // glFunctions Init
		cout<<"Unable to Initialize gl Window"<<endl;
		getchar();
		return 0;
	}

	// Two Most Important Main Loops
	game->startGame();	// Game movement in one thread
	glutMainLoop();		// Game display in other thread

	return 0;
}

/******************************************************************************
 * Documentation Template
 * 
******************************************************************************/
