#include "Maze.h"

/*
Maze is defined in "TheGameMatrix.txt".
First Line- Length Width
   wall:a:11	h:15	b:12
		v:16	m:10	v:16
		c:13	h:15	d:14

hhh      x        v        v     
 w      hhh      yv        vz     
		          v        v       

w:21, x:22, y:23, z:24, l:25 
p- path with pellets:6, e- empty path:0
g- ghosts place:7, warp gates- using nos:1, 2, 3, 4, 5.
s- boost pellets:8
*/

Maze::Maze(){
	vf size;
	size.push_back(10.f), size.push_back(static_cast<float>(INT_MAX)),size.push_back(15.f);
	this->init(size);
}

Maze::Maze(string filename){
	mazeReader(filename);
}

void Maze::mazeReader(string filename){
	ifstream mazeInf;
	string dimension;
	int len; int wid;

	mazeInf.open(filename);
	
	if(!mazeInf.good()){
		cout << "File not found or corrupted. File: " << filename << endl;
	}

	getline(mazeInf, dimension);
	stringstream lwSS(dimension);

	lwSS >> len >> wid;

	vf s(3);
	s[0] = wid; s[1] = static_cast<float> (INT_MAX); s[2] = len;
	this->init(s);

	
	char feature;
	this->mazeMat.resize(len);
	for(int i = 0; i < len; i++){
		
		getline(mazeInf, dimension);
		stringstream featureSS(dimension);
		this->mazeMat[i].resize(wid);
		for(int j = 0; j < wid; j++){
			featureSS >> feature;

			switch(feature){
			case 'm':
				this->mazeMat[i][j] = 10;
				break;
			case 'a':
				this->mazeMat[i][j] = 11;
				break;
			case 'b':
				this->mazeMat[i][j] = 12;
				break;
			case 'c':
				this->mazeMat[i][j] = 13;
				break;
			case 'd':
				this->mazeMat[i][j] = 14;
				break;
			case 'h':
				this->mazeMat[i][j] = 15;
				break;
			case 'v':
				this->mazeMat[i][j] = 16;
				break;
			case 'w':
				this->mazeMat[i][j] = 21;
				break;
			case 'x':
				this->mazeMat[i][j] = 22;
				break;
			case 'y':
				this->mazeMat[i][j] = 23;
				break;
			case 'z':
				this->mazeMat[i][j] = 24;
				break;
			case 'l':
				this->mazeMat[i][j] = 25;
				break;
			case 'p':
				this->mazeMat[i][j] = 6;
				break;
			case 'e':
				this->mazeMat[i][j] = 0;
				break;
			case 'g':
				this->mazeMat[i][j] = 7;
				break;
			case 's':
				this->mazeMat[i][j] = 8;
				break;
			default:
				this->mazeMat[i][j] = static_cast<int> (feature);
				break;
			}
		}
	}	
}
/*
static void torus(int numc, int numt)
{
   int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * 3.14;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt/4; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}
*/
void Maze::draw(){
	/*
	//This is a Mesh
	glPushMatrix();
	
	// A yellow colored mesh
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	glBegin(GL_LINES);
	for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
		glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
		glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
	}
	for (GLfloat i = -this->size[0]/2; i <= this->size[0]/2; i += 1.f){
		glVertex3f(i, 0, -this->size[2]/2); glVertex3f(i, 0, this->size[2]/2);
	}
	for (GLfloat i = -this->size[2]/2; i <= this->size[2]/2; i += 1.f){
		glVertex3f(-this->size[0]/2, 0 ,i); glVertex3f(this->size[0]/2, 0, i);
	}
	glEnd();
	glTranslatef(-this->position[0], -this->position[1], -this->position[2]);
	glPopMatrix();
	*/

	/*using maze matrix
		(x1, z1)	(x2, z1)
		(x1, z2)	(x2, z2)
	*/
	int len = this->size[2]; int wid = this->size[0];

	float ln = ((float)len-1.0f)/2.0f; float wd = ((float)wid-1.0)/2.0;

	for (int i = 0; i < len; i++){
		for(int j = 0; j < wid; j++){
			int feature = mazeMat[i][j];
			float x1 = (float)j-wd-0.5f; float x2 = (float)j-wd+0.5f;
			float z1 = (float)i-ln-0.5f; float z2 = (float)i-ln+0.5f;
			
			GLfloat cyan[] = {0.f, .0f, .1f, 1.f};
			glColor3f(0.0f, 0.0f, 1.0f);

			switch(feature){
			case 11:
				
				break;

			case 12:
				
				break;

			case 13:
				
				break;

			case 14:
				
				break;

			case 15:
				glColor3f(0.0f, 0.0f, 1.0f);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
				glPushMatrix();
				glTranslatef((float)j-wd, 0.5f, (float)i-ln);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, -0.5f);
				glutSolidCylinder(0.25f, 1.0f, 8, 8);
				glTranslatef(0.0f, 0.0f, 0.5f);
				glRotatef(-90, 0.0f, 1.0f, 0.0f);
				glTranslatef(-((float)j-wd), -0.5f, -((float)i-ln));
				glPopMatrix();
				break;

			case 16:
				glColor3f(0.0f, 0.0f, 1.0f);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
				glPushMatrix();
				glTranslatef((float)j-wd, 0.5f, (float)i-ln-0.5f);
				glutSolidCylinder(0.25f, 1.0f, 8, 8);
				glTranslatef(-((float)j-wd), -0.5f, -((float)i-ln-0.5f));
				glPopMatrix();
				break;

			case 21:
				glPushMatrix();
				glTranslatef((float)j-wd, 0.5f, (float)i-ln-1.0f);
				glutSolidCylinder(0.25f, 1.5f, 8, 8);
				glTranslatef(-((float)j-wd), -0.5f, -((float)i-ln-1.0f));
				glPopMatrix();
				break;

			case 22:
				glPushMatrix();
				glTranslatef((float)j-wd, 0.5f, (float)i-ln-0.5f);
				glutSolidCylinder(0.25f, 1.5f, 8, 8);
				glTranslatef(-((float)j-wd), -0.5f, -((float)i-ln-0.5f));
				glPopMatrix();
				break;

			case 23:
				glPushMatrix();
				glTranslatef((float)j-wd, 0.5f, (float)i-ln);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, -0.5f);
				glutSolidCylinder(0.25f, 1.5f, 8, 8);
				glTranslatef(0.0f, 0.0f, 0.5f);
				glRotatef(-90, 0.0f, 1.0f, 0.0f);
				glTranslatef(-((float)j-wd), -0.5f, -((float)i-ln));
				glPopMatrix();
				break;

			case 24:
				glPushMatrix();
				glTranslatef((float)j-wd, 0.5f, (float)i-ln);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, -1.0f);
				glutSolidCylinder(0.25f, 1.5f, 8, 8);
				glTranslatef(0.0f, 0.0f, 1.0f);
				glRotatef(-90, 0.0f, 1.0f, 0.0f);
				glTranslatef(-((float)j-wd), -0.5f, -((float)i-ln));
				glPopMatrix();
				break;

			case 25:
				
				break;

			case 6:
				glColor3f(yellow.r, yellow.g, yellow.b);
				glPushMatrix();	
				glTranslatef((float)j-wd, 0.25f, (float)i-ln);
				glutSolidSphere(0.2f, 24, 24);
				glTranslatef(-((float)j-wd), -0.25, -((float)i-ln));
				glPopMatrix();
				break;

			default:
				break;
			}
		}
	}

}

Maze::~Maze(){

}

void Maze::init(vf size){
	this->size = size;
	vf pos; pos.push_back(0.f); pos.push_back(0.f); pos.push_back(0.f);
	vf norm; pos.push_back(0.f); pos.push_back(1.f); pos.push_back(0.f);
	vf grav; pos.push_back(0.f); pos.push_back(-1.f); pos.push_back(0.f);
	this->position = pos;
	this->normal = norm;
	this->gravity = grav;
}