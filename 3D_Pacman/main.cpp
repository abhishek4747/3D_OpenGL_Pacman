#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<GL/glew.h>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<math.h>

#define PI 3.14159265

using namespace std;

class node {
public:
	string name, p_name, shape;
	int ch_num;
	float tx, ty, tz, ang, vx, vy, vz, sz1, sz2;

	vector<node*> children; 

	node(string nm, string p_nm, string shp, int c_num, float t1, float t2, float t3, float ag, float v1, float v2, float v3){
		name = nm;
		p_name = p_nm;
		shape = shp;
		ch_num = c_num;
		tx = t1;
		ty = t2;
		tz = t3;
		ang = ag;
		vx = v1;
		vy = v2;
		vz = v3;
	}
};

node* rt;

float finger_ang = 3.0f;
bool finger_gen = true;
vector<node*> finger_vec;

bool turn_gen = true;
vector<node*> turn_vec;

bool hand_gen = true;
vector<node*> hand_vec;

vector<node*> arm_vec;
vector<node*> forearm_vec;

bool arm_gen = true;

bool move_arm1 = false;
bool move_arm1_more = false;
bool arm1_reset = false;
float arm1_ang = 4.0f;
float forearm1_ang = 4.0f;


bool move_arm2 = false;
bool move_arm2_more = false;
bool arm2_reset = false;
float arm2_ang = 4.0f;
float forearm2_ang = 4.0f;

bool move_arm3 = false;
bool move_arm3_more = false;
bool arm3_reset = false;
float arm3_ang = 4.0f;
float forearm3_ang = 4.0f;

bool move_arm4 = false;
bool move_arm4_more = false;
bool arm4_reset = false;
float arm4_ang = 4.0f;
float forearm4_ang = 4.0f;

node* nodemaker(string raw_input){
	
	stringstream iss(raw_input);

	string nm, p_nm, shp;
	int c_num;
	float t1, t2, t3, ag, v1, v2, v3;

	iss >> nm >> p_nm >> shp >> c_num >> t1 >> t2 >> t3 >> ag >> v1 >> v2 >> v3;

	node* leaf = new node(nm, p_nm, shp, c_num, t1, t2, t3, ag, v1, v2, v3);

	leaf->sz1 = 0.0;
	leaf->sz2 = 0.0;

    float output;
	if (iss >> output){
		leaf->sz1 = output;
	}

	if (iss >> output){
		leaf->sz2 = output;
	}
	return leaf;
} 

node* parser(ifstream &filename){
	string output;
	getline(filename, output);
	//output = trim(output);
	node* root = nodemaker(output);
    
	for (int i = 0; i < root->ch_num; i++){
		root->children.push_back(parser(filename));
	}	
	return root;
}

void print(node* rr){

	cout << rr->name << rr->p_name << rr->shape << rr->ch_num << rr->tx << rr->ty << rr->tz << rr->ang << rr->vx << rr->vy << rr->vz << rr->sz1 << rr->sz2;

	for(int i = 0; i < rr->children.size(); i++){
		print(rr->children[i]);
	}

}

void vec_gen_help(node* root, string str, vector<node*> &component){
	//cout << " step 1 " << root->name << endl;
	if ((root->name).compare(str) == 0){
		component.push_back(root);
	}
	for (int i = 0; i < root->ch_num; i++){
		//cout << " step 2 " << root->name << endl;	
		vec_gen_help(root->children[i], str, component);
		//cout << " step 3 " << root->name << endl;	
		//cout << "inccc" << component.size();
	}
}

void tMatrix(float x, float y, float z){

	GLfloat tM[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1};

	glMultMatrixf(&tM[0]);
}

void rMatrix(int angl, float vx,float vy, float vz){
	float s= sin(angl * PI/ 180.0);
	float c= cos(angl* PI/ 180.0);
	float rM[16]={vx*vx*(1-c)+c, vy*vx*(1-c)+vz*s, vx*vz*(1-c)-vy*s, 0,
		vy*vx*(1-c)-vz*s, vy*vy*(1-c)+c, vy*vz*(1-c)+vx*s, 0,
		vx*vz*(1-c)+vy*s, vy*vz*(1-c)-vx*s, vz*vz*(1-c)+c, 0,
		0, 0, 0, 1};
	glMultMatrixf(&rM[0]);
}

vector<node*> vec_gen(node* root, string str){
	vector<node*> component;
	vec_gen_help(root, str, component);
	return component;
}

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  
 
float k0 = 0.0;
float k1 = 5.0;
float k2 = 0.0;

void keyOperations (void) {  
if (keyStates['a']) { 
	k0 = k0 + 0.1;
}
if (keyStates['s']) { 
	k1 = k1 + 0.1;
}
if (keyStates['d']) { 
	k2 = k2 + 0.1;
}
if (keyStates['z']) { 
	k0 = k0 - 0.1;
}
if (keyStates['x']) { 
	k1 = k1 - 0.1;
}
if (keyStates['c']) { 
	k2 = k2 - 0.1;
}
if (keyStates['g']){
	if (turn_gen == true){
		turn_vec = vec_gen(rt, "turn");
		turn_gen = false;
	}

	if (arm_gen == true){
		arm_vec = vec_gen(rt, "arm");
		forearm_vec = vec_gen(rt, "forearm");
		arm_gen = false;
	}

	turn_vec[0]->tx = turn_vec[1]->tx+(arm_vec[0]->sz2 + forearm_vec[0]->sz2)*sin(turn_vec[1]->ang*PI/180);
	turn_vec[0]->ty = turn_vec[1]->ty;
	turn_vec[0]->tz = turn_vec[1]->tz+(arm_vec[0]->sz2 + forearm_vec[0]->sz2)*cos(turn_vec[1]->ang*PI/180);

	turn_vec[0]->vy = 1;

	turn_vec[0]->ang  = turn_vec[1]->ang + 180.0;

}

if (keyStates['h']){
	if (turn_gen == true){
		turn_vec = vec_gen(rt, "turn");
		turn_gen = false;
	}

	if (arm_gen == true){
		arm_vec = vec_gen(rt, "arm");
		forearm_vec = vec_gen(rt, "forearm");
		arm_gen = false;
	}

	turn_vec[1]->tx = turn_vec[0]->tx+(arm_vec[2]->sz2 + forearm_vec[2]->sz2)*sin(turn_vec[0]->ang*PI/180);
	turn_vec[1]->ty = turn_vec[0]->ty;
	turn_vec[1]->tz = turn_vec[0]->tz+(arm_vec[2]->sz2 + forearm_vec[2]->sz2)*cos(turn_vec[0]->ang*PI/180);

	turn_vec[1]->vy = 1;

	turn_vec[1]->ang  = turn_vec[0]->ang + 180.0;

}
if (keyStates['m']){
	if (finger_gen == true){
		finger_vec = vec_gen(rt, "finger");
		finger_gen = false;
	}
	if (finger_vec[0]->ang > 100.0){
		finger_ang = -3.0f;
	}
	if (finger_vec[0]->ang < 0.05){
		finger_ang = 3.0f;
	}
	for (int i = 0; i < finger_vec.size()/2; i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
	}
}if (keyStates['n']){
	if (finger_gen == true){
		finger_vec = vec_gen(rt, "finger");
		finger_gen = false;
	}
	if (finger_vec[finger_vec.size()-1]->ang > 0.05){
		finger_ang = -3.0f;
	}
	if (finger_vec[finger_vec.size()-1]->ang < -100.0){
		finger_ang = 3.0f;
	} 
	for (int i = finger_vec.size()/2; i < finger_vec.size(); i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
	}
}
if (keyStates['o']){
	move_arm1 = true;
}
if (keyStates['O']){
	arm1_reset = true;
}
if (keyStates['p']){
	move_arm2 = true;
}
if (keyStates['P']){
	arm2_reset = true;
}
if (keyStates['k']){
	move_arm3 = true;
}
if (keyStates['K']){
	arm3_reset = true;
}
if (keyStates['l']){
	move_arm4 = true;
}
if (keyStates['L']){
	arm4_reset = true;
}

if (keyStates['r']){
	k0 = 0.0;
	k1 = 5.0;
	k2 = 0.0;

	ifstream myF;
 	myF.open("text.txt");

 	node* rt2 = parser(myF);

	rt = rt2;

	myF.close();

	finger_ang = 3.0f;
	finger_gen = true;

	turn_gen = true;

	hand_gen = true;
	arm_gen = true;

	move_arm1 = false;
	move_arm1_more = false;
	arm1_reset = false;
	arm1_ang = 4.0f;
	forearm1_ang = 4.0f;

	move_arm2 = false;
	move_arm2_more = false;
	arm2_reset = false;
	arm2_ang = 4.0f;
	forearm2_ang = 4.0f;

	move_arm3 = false;
	move_arm3_more = false;
	arm3_reset = false;
	arm3_ang = 4.0f;
	forearm3_ang = 4.0f;
	
	move_arm4 = false;
	move_arm4_more = false;
	arm4_reset = false;
	arm4_ang = 4.0f;
	forearm4_ang = 4.0f;
}
return;
} 



void display (void) {  
keyOperations();

if (move_arm1 == true){
	if (arm_gen == true){
		arm_vec = vec_gen(rt, "arm");
		forearm_vec = vec_gen(rt, "forearm");
		arm_gen = false;
	}
	if (//arm_vec[0]->ang < 50.0f &&
		move_arm1_more == false){
		arm1_ang = 4.0;
		forearm1_ang = -10.0;
		
		if (finger_gen == true){
		finger_vec = vec_gen(rt, "finger");
		finger_gen = false;
		}
		if (finger_vec[0]->ang > 100.0){
			finger_ang = -8.0f;
		}
		//if (finger_vec[0]->ang < 0.05){
			//finger_ang = 1.0f;
		//}
		for (int i = 0; i < finger_vec.size()/2; i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
		}
		//arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
		//forearm_vec[0]->ang = forearm_vec[0]->ang + forearm1_ang;

		if (arm_vec[0]->ang >= 50.0f){
			move_arm1_more = true;
		}
	}
	if (move_arm1_more == true){
		
		/*if (hand_gen == true){
			hand_vec = vec_gen(rt, "hand");
			hand_vec[0]->vx = 0.0;
			hand_vec[0]->vy = 1.0;
			hand_gen = false;
		}

		if (hand_vec[0]->ang < 180.0){
			hand_vec[0]->ang = hand_vec[0]->ang + 1.0;
		}*/

		if (arm_vec[0]->ang > -90.0){
			arm1_ang = -4.0;
			forearm1_ang = 3.6;
			//arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
			///forearm_vec[0]->ang = forearm_vec[0]->angx + forearm1_ang;
		}
	if (arm_vec[0]->ang <= -90.0){
			move_arm1 = false;
			move_arm1_more = false;
		}
	}
	
	arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
		forearm_vec[0]->ang = forearm_vec[0]->ang + forearm1_ang;
}
if (arm1_reset == true){
		if (arm_vec[0]->ang < 0.0){
			arm_vec[0]->ang = arm_vec[0]->ang + 4.0;
		}
		if (finger_vec[0]->ang < 0.05){
			finger_ang = 4.0f;
		}
		for (int i = 0; i < finger_vec.size()/2; i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
		}
		if (arm_vec[0]->ang >= 0.0){
			arm1_reset = false;
		}
}

if (move_arm2 == true){
	if (arm_gen == true){
		arm_vec = vec_gen(rt, "arm");
		forearm_vec = vec_gen(rt, "forearm");
		arm_gen = false;
	}
	if (//arm_vec[0]->ang < 50.0f &&
		move_arm2_more == false){
		arm2_ang = 4.0;
		forearm2_ang = -10.0;
		
		if (finger_gen == true){
		finger_vec = vec_gen(rt, "finger");
		finger_gen = false;
		}
		if (finger_vec[0]->ang > 100.0){
			finger_ang = -8.0f;
		}
		//if (finger_vec[0]->ang < 0.05){
			//finger_ang = 1.0f;
		//}
		for (int i = 0; i < finger_vec.size()/2; i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
		}

		//arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
		//forearm_vec[0]->ang = forearm_vec[0]->ang + forearm1_ang;

		if (arm_vec[1]->ang >= 50.0f){
			move_arm2_more = true;
		}
	}
	if (move_arm2_more == true){
		if (arm_vec[1]->ang > -90.0){
			arm2_ang = -4.0;
			forearm2_ang = 3.6;
			//arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
			///forearm_vec[0]->ang = forearm_vec[0]->ang + forearm1_ang;
		}
	if (arm_vec[1]->ang <= -90.0){
			move_arm2 = false;
			move_arm2_more = false;
		}
	}
	arm_vec[1]->ang = arm_vec[1]->ang + arm2_ang;
		forearm_vec[1]->ang = forearm_vec[1]->ang + forearm2_ang;
}
if (arm2_reset == true){
		if (arm_vec[1]->ang < 0.0){
			arm_vec[1]->ang = arm_vec[1]->ang + 4.0;
		}
		if (finger_vec[0]->ang < 0.05){
			finger_ang = 4.0f;
		}
		for (int i = 0; i < finger_vec.size()/2; i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
		}
		if (arm_vec[1]->ang >= 0.0){
			arm2_reset = false;
		}
}

if (move_arm3 == true){
	if (arm_gen == true){
		arm_vec = vec_gen(rt, "arm");
		forearm_vec = vec_gen(rt, "forearm");
		arm_gen = false;
	}
	if (//arm_vec[0]->ang < 50.0f &&
		move_arm3_more == false){
		arm3_ang = 4.0;
		forearm3_ang = -10.0;
		
		if (finger_gen == true){
		finger_vec = vec_gen(rt, "finger");
		finger_gen = false;
		}
		if (finger_vec[7]->ang > 100.0){
			finger_ang = -8.0f;
		}
		//if (finger_vec[0]->ang < 0.05){
			//finger_ang = 1.0f;
		//}
		for (int i = finger_vec.size()/2; i < finger_vec.size()/2; i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
		}

		//arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
		//forearm_vec[0]->ang = forearm_vec[0]->ang + forearm1_ang;

		if (arm_vec[2]->ang >= 50.0f){
			move_arm3_more = true;
		}
	}
	if (move_arm3_more == true){
		if (arm_vec[2]->ang > -90.0){
			arm3_ang = -4.0;
			forearm3_ang = 3.6;
			//arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
			///forearm_vec[0]->ang = forearm_vec[0]->ang + forearm1_ang;
		}
	if (arm_vec[2]->ang <= -90.0){
			move_arm3 = false;
			move_arm3_more = false;
		}
	}
	arm_vec[2]->ang = arm_vec[2]->ang + arm3_ang;
	forearm_vec[2]->ang = forearm_vec[2]->ang + forearm3_ang;
}
if (arm3_reset == true){
		if (arm_vec[2]->ang < 0.0){
			arm_vec[2]->ang = arm_vec[2]->ang + 4.0;
		}
		if (finger_vec[7]->ang < 0.05){
			finger_ang = 4.0f;
		}
		for (int i = finger_vec.size()/2; i < finger_vec.size(); i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
		}
		if (arm_vec[2]->ang >= 0.0){
			arm3_reset = false;
		}
}





if (move_arm4 == true){
	if (arm_gen == true){
		arm_vec = vec_gen(rt, "arm");
		forearm_vec = vec_gen(rt, "forearm");
		arm_gen = false;
	}
	if (//arm_vec[0]->ang < 50.0f &&
		move_arm4_more == false){
		arm4_ang = 4.0;
		forearm4_ang = -10.0;
		
		if (finger_gen == true){
		finger_vec = vec_gen(rt, "finger");
		finger_gen = false;
		}
		if (finger_vec[7]->ang > 100.0){
			finger_ang = -8.0f;
		}
		//if (finger_vec[0]->ang < 0.05){
			//finger_ang = 1.0f;
		//}
		for (int i = finger_vec.size()/2; i < finger_vec.size(); i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
		}

		//arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
		//forearm_vec[0]->ang = forearm_vec[0]->ang + forearm1_ang;

		if (arm_vec[3]->ang >= 50.0f){
			move_arm4_more = true;
		}
	}
	if (move_arm4_more == true){
		if (arm_vec[3]->ang > -90.0){
			arm4_ang = -4.0;
			forearm4_ang = 3.6;
			//arm_vec[0]->ang = arm_vec[0]->ang + arm1_ang;
			///forearm_vec[0]->ang = forearm_vec[0]->ang + forearm1_ang;
		}
	if (arm_vec[3]->ang <= -90.0){
			move_arm4 = false;
			move_arm4_more = false;
		}
	}
	arm_vec[3]->ang = arm_vec[3]->ang + arm4_ang;
		forearm_vec[3]->ang = forearm_vec[3]->ang + forearm4_ang;
}
if (arm4_reset == true){
		if (arm_vec[3]->ang < 0.0){
			arm_vec[3]->ang = arm_vec[3]->ang + 4.0;
		}
		if (finger_vec[7]->ang < 0.05){
			finger_ang = 4.0f;
		}
		for (int i = finger_vec.size()/2; i < finger_vec.size(); i++){
				finger_vec[i]->ang = finger_vec[i]->ang + finger_ang;
		}
		if (arm_vec[3]->ang >= 0.0){
			arm4_reset = false;
		}
}














glClearColor(0.5f, 0.5f, 0.0f, 1.0f); 
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
glMatrixMode(GL_MODELVIEW);
glLoadIdentity(); 
gluLookAt(k0, k1, k2, 0.0, 0.0, -5.0, 0.0, 1.0, 0.0);
//glTranslatef(0.0, 0.0, -5.0);
//glTranslatef(0.0, -2.0, 0.0);
glutSolidCylinder(0.2, 1.0, 10, 10);
//draw(rt);
 // Push eveything 5 units back into the scene, otherwise we won't see the primitive  
  
glutSwapBuffers();  
}  
  
void reshape (int width, int height) {  
glViewport(0, 0, (GLsizei)width, (GLsizei)height); 
glMatrixMode(GL_PROJECTION); 
glLoadIdentity(); 
gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); 
glMatrixMode(GL_MODELVIEW); 
} 

void keyPressed (unsigned char key, int x, int y) {  
keyStates[key] = true; // Set the state of the current key to pressed  
}  
  
void keyUp (unsigned char key, int x, int y) {  
keyStates[key] = false; // Set the state of the current key to not pressed  
}  

int main(int argc, char** argv){
	
	for (int i = 0; i < 256; i++){
		keyStates[i] = false; 
	}

	ifstream myFile;
 	myFile.open("text.txt");

 	rt = parser(myFile);

	//print(rt);

	myFile.close();
	//getchar();

glutInit(&argc, argv); 
glutInitDisplayMode (GLUT_DOUBLE); 
glutInitWindowSize (500, 500); 
glutInitWindowPosition (100, 100); 
glutCreateWindow ("Boxers");  
  
glutDisplayFunc(display);
glutIdleFunc(display);
glutReshapeFunc(reshape);

glEnable(GL_DEPTH_TEST);
glEnable(GL_SMOOTH);

glutKeyboardFunc(keyPressed); 
glutKeyboardUpFunc(keyUp);

glutMainLoop();   
	return 0;
}