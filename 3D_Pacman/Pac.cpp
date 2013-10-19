#include "Pac.h"

Pac::Pac(){
	vf pos, or, ver, dim;
	pos.push_back(0.f), pos.push_back(0.f), pos.push_back(0.f);
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(.2f);
	string shape("sphere");
	color4 col(0.,1.,1.);
	Maze *maze = new Maze();
	this->init(pos, or, ver, shape, dim, .01f, col, maze);
}

Pac::Pac(Maze *maze){
	vf pos, or, ver, dim;
	pos.push_back(0.f), pos.push_back(0.f), pos.push_back(0.f);
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(.2f);
	string shape("sphere");
	color4 col(0.,1.,1.);
	this->init(pos, or, ver, shape, dim, .05f, col, maze);	
}

Pac::Pac(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color, Maze *maze){
	this->init(position, orientn, vertical, shape, dimentions, speed, color, maze);
}

void Pac::draw(){
	glPushMatrix();
	double R = 4*this->dimentions[0];
	int p = 16, q = 16;
	static int mouth = 8;
	static bool mouthOpening = true;
	glTranslatef(this->position[0], this->position[1]+static_cast<float>(R), this->position[2]);
	glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
	
	if (this->shape=="sphere"){
		//glutSolidSphere(this->dimentions[0], 32, 32);

		vf initialv;
		initialv.push_back(1.f);initialv.push_back(0.f);initialv.push_back(0.f);
		float ang = anglebw(orientn,initialv);
		cout<<ang<<endl;
		glRotatef(-90.f,this->orientn[0],this->orientn[1],this->orientn[2]);
		glRotatef(ang,this->vertical[0],this->vertical[1],this->vertical[2]);
		for(int j = -q; j < q; j++){
			// One latitudinal triangle strip.
			glBegin(GL_TRIANGLE_STRIP);
				glColor4f(pink.r,pink.g,pink.b,pink.a);
				glVertex3f(0.f,0.f,0.f);
				for(int i = p/mouth; i <= (mouth-1)*p/mouth; i++){
					glColor4f(yellow.r,yellow.g,yellow.b,yellow.a);
					glVertex3d( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
								R * sin( (float)(j+1)/q * PI/2.0 ),
								R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
					glVertex3d( R * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
								R * sin( (float)j/q * PI/2.0 ),
								R * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );         
					}
				glColor4f(purple.r,purple.g,purple.b,purple.a);
				glVertex3f(0.f,0.f,0.f);
			glEnd();
		}
		glRotatef(-ang,this->vertical[0],this->vertical[1],this->vertical[2]);
		glRotatef(90.f,this->orientn[0],this->orientn[1],this->orientn[2]);
		
	}
	if (mouthOpening){
		mouth *= 2;
	}else{
		mouth /= 2;
	}
	if (mouth<=8 || mouth>8*pow(2,10)){
		mouthOpening = !mouthOpening;
	}
	
	glTranslatef(-this->position[0], -this->position[1]-static_cast<float>(R), -this->position[2]);
	glPopMatrix();
}

void Pac::moveForward(){
	float mag = magnitue(this->orientn);
	float newPos[3];
	bool canMove = true;
	for (size_t i = 0; i < 3; i++){
		newPos[i] = this->position[i]+this->orientn[i]*this->speed/mag;
		canMove &= (newPos[i]>= -this->maze->size[i]/2 && newPos[i]<= this->maze->size[i]/2);
	}
	if (canMove){
		for (size_t i = 0; i < 3; i++){
			this->position[i] = newPos[i];
		}
	}
}

void Pac::moveLeft(){
	moving = true;
	moveSomewhere(90.f,3);
	moving = false;
}

void Pac::moveRight(){
	moving = true;
	moveSomewhere(90.f,3,-1.f);
	moving = false;
}

void Pac::moveBack(){
	moving = true;
	moveSomewhere(180.f,3,1.f);
	moving = false;
}

Pac::~Pac(){
}

void Pac::moveSomewhere(float totaldegree, int fast, float direction){
	mtx.lock();
	vf fin = rotateaboutaxisbyangle(orientn,origin,vertical,totaldegree*direction);
	for (int i = 0; i < 90/fast; i++){
		orientn = rotateaboutaxisbyangle(orientn,origin,vertical,fast*direction);
		Sleep(1*fast);
	}
	orientn = fin;
	mtx.unlock();
}

void Pac::init(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color, Maze *maze){
	this->position = position, this->orientn = orientn, this->vertical = vertical;
	this->shape = shape, this->dimentions = dimentions;
	this->speed = speed;
	this->color = color;
	this->maze = maze;
	this->angle = 0.f;
	this->moving = false;
}
