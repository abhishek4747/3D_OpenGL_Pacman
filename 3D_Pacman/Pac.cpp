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
	this->init(pos, or, ver, shape, dim, .1f, col, maze);

}

Pac::Pac(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color, Maze *maze){
	this->init(position, orientn, vertical, shape, dimentions, speed, color, maze);
}

void Pac::draw(){
	glPushMatrix();
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	//glRotatef(this->angle, this->orientn[0], this->orientn[1], this->orientn[2]);
	glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
	if (this->shape=="sphere"){
		glutSolidSphere(this->dimentions[0], 32, 32);
	}
	//glRotatef(-this->angle, this->orientn[0], this->orientn[1], this->orientn[2]);
	glTranslatef(-this->position[0], -this->position[1], -this->position[2]);
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
	orientn = rotateaboutaxisbyangle(orientn,origin,vertical,90.f);
}

void Pac::moveRight(){
	orientn = rotateaboutaxisbyangle(orientn,origin,vertical,-90.f);
}

void Pac::moveBack(){
	orientn = rotateaboutaxisbyangle(orientn,origin,vertical,180.f);
}

Pac::~Pac(){
}

void Pac::init(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color, Maze *maze){
	this->position = position, this->orientn = orientn, this->vertical = vertical;
	this->shape = shape, this->dimentions = dimentions;
	this->speed = speed;
	this->color = color;
	this->maze = maze;
	this->angle = 0.f;
}