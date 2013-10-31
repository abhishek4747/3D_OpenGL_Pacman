#include "Pac.h"

Pac::Pac(){
	Agent::Agent();
	this->maze = new Maze();
}

Pac::Pac(Maze *maze){
	vf pos, or, ver, dim;
	pos.push_back(0.f), pos.push_back(0.f), pos.push_back(0.f);
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(1.f);
	string shape("sphere");
	color4 col(0.,1.,1.);
	this->init(pos, or, ver, shape, dim, .1f, col, maze);	
}

Pac::Pac(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color, Maze *maze){
	this->init(position, orientn, vertical, shape, dimentions, speed, color, maze);
}

void Pac::draw(){
	glPushMatrix();
	double R = this->dimentions[0]/2;
	int p = 16, q = 16;
	static int mouth = 8;
	static bool mouthOpening = true;
	glTranslatef(this->position[0], this->position[1]+static_cast<float>(R), this->position[2]);
	glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
	if (this->shape=="sphere"){
		//glutSolidSphere(this->dimentions[0], 32, 32);
		vf initialv;
		initialv.push_back(1.f);initialv.push_back(0.f);initialv.push_back(0.f);
		mtx.lock();
		float ang = anglebw(orientn,initialv);
		mtx.unlock();
		mtx.lock();
		glRotatef(-90.f,this->orientn[0],this->orientn[1],this->orientn[2]);
		mtx.unlock();
		glRotatef(ang,this->vertical[0],this->vertical[1],this->vertical[2]);
		
		for(int j = -q; j < q; j++){
			// One latitudinal triangle strip.
			glBegin(GL_TRIANGLE_STRIP);
				//glColor4f(pink.r,pink.g,pink.b,pink.a);
				glColor4f(yellow.r,yellow.g,yellow.b,yellow.a);
				glVertex3f(0.f,0.f,0.f);
				for(int i = p/mouth; i <= (mouth-1)*p/mouth; i++){
					glColor4f(yellow.r,yellow.g,yellow.b,yellow.a);
					/*GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
					GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
					glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
					glMaterialfv(GL_FRONT, GL_SPECULAR, white);
					GLfloat shininess[] = {50};
					glMaterialfv(GL_FRONT, GL_SHININESS, shininess);*/
					glVertex3d( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
								R * sin( (float)(j+1)/q * PI/2.0 ),
								R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
					glVertex3d( R * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
								R * sin( (float)j/q * PI/2.0 ),
								R * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );         
					}
				glColor4f(yellow.r,yellow.g,yellow.b,yellow.a);
				//glColor4f(purple.r,purple.g,purple.b,purple.a);
				glVertex3f(0.f,0.f,0.f);
			glEnd();
		}
		glRotatef(-ang,this->vertical[0],this->vertical[1],this->vertical[2]);
		mtx.lock();
		glRotatef(90.f,this->orientn[0],this->orientn[1],this->orientn[2]);
		mtx.unlock();
		float R2 = 7*R/8;
		float dist = 100.f;
		mtx.lock();
		glTranslatef(this->orientn[0]/dist, this->orientn[1]/dist,this->orientn[2]/dist);
		glRotatef(-90.f,this->orientn[0],this->orientn[1],this->orientn[2]);
		mtx.unlock();
		glRotatef(ang,this->vertical[0],this->vertical[1],this->vertical[2]);
		for(int j = -q; j < q; j++){
			// One latitudinal triangle strip.
			glBegin(GL_TRIANGLE_STRIP);
				glColor4f(red.r,red.g,red.b,red.a);
				glVertex3f(0.f,0.f,0.f);
				for(int i = p/mouth; i <= (mouth-1)*p/mouth; i++){
					glColor4f(red.r,red.g,red.b,red.a);
					glVertex3d( R2 * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
								R2 * sin( (float)(j+1)/q * PI/2.0 ),
								R2 * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
					glVertex3d( R2 * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
								R2 * sin( (float)j/q * PI/2.0 ),
								R2 * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );         
					}
				glColor4f(red.r,red.g,red.b,red.a);
				glVertex3f(0.f,0.f,0.f);
			glEnd();
		}
		glRotatef(-ang,this->vertical[0],this->vertical[1],this->vertical[2]);
		mtx.lock();
		glRotatef(90.f,this->orientn[0],this->orientn[1],this->orientn[2]);
		glTranslatef(-this->orientn[0]/dist, -this->orientn[1]/dist, -this->orientn[2]/dist);		
		mtx.unlock();
	}
	if (mouthOpening){
		mouth *= 2;
	}else{
		mouth /= 2;
	}
	if (mouth<=8 || mouth>8*pow(2,10)){
		mouthOpening = !mouthOpening;
	}
	//eyes
	float dbweye = R/5; 
	float sqrt3 = sqrt(3);
	glPushMatrix();
	glTranslatef(R*this->orientn[0]/sqrt3 + (this->orientn[0]==0.f?dbweye:0.f),R*this->orientn[1]+R/sqrt(2),R*this->orientn[2]/sqrt3 +(this->orientn[2]==0.f?dbweye:0.f));
	glColor3f(green.r,green.g,green.b);
	float rEyebrow = R/10;
	glutSolidSphere(R/4, 32, 32);
	glTranslatef(0.f,dbweye,0.f);
	glColor3f(black.r,black.g,black.b);
	
	glRotatef(90.f, this->orientn[0], this->orientn[1], this->orientn[2]);
	DrawEllipsoid(rEyebrow,rEyebrow,2*rEyebrow);
	glTranslatef(0.f,-dbweye,0.f);
	glRotatef(90.f, -this->orientn[0], -this->orientn[1], -this->orientn[2]);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(R*this->orientn[0]/sqrt3 - (this->orientn[0]==0.f?dbweye:0.f),R*this->orientn[1]+R/sqrt(2),R*this->orientn[2]/sqrt3-(this->orientn[2]==0.f?dbweye:0.f));
	glColor3f(green.r,green.g,green.b);
	glutSolidSphere(R/4, 32, 32);
	glPopMatrix();

	glTranslatef(-this->position[0], -this->position[1]-static_cast<float>(R), -this->position[2]);
	glPopMatrix();
}

void Pac::moveForward(){
	mtx.lock();
	float mag = magnitue(this->orientn);
	mtx.unlock();
	float newPos[3];
	bool canMove = true;
	for (size_t i = 0; i < 3; i++){
		mtx.lock();
		newPos[i] = this->position[i]+this->orientn[i]*this->speed/mag;
		mtx.unlock();
		canMove &= (newPos[i]>= -this->maze->size[i]/2 && newPos[i]<= this->maze->size[i]/2);
	}
	if (canMove){
		for (size_t i = 0; i < 3; i++){
			this->position[i] = newPos[i];
		}
	}
}

void Pac::init(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color, Maze *maze){
	this->position = position, this->orientn = orientn, this->vertical = vertical;
	this->shape = shape, this->dimentions = dimentions;
	this->speed = speed;
	this->color = color;
	this->maze = maze;
	this->moving = false;
}
