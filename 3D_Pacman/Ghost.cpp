#include "Ghost.h"

Ghost::Ghost(){
	vf pos, or, ver, dim;
	pos.push_back(0.f), pos.push_back(0.f), pos.push_back(0.f);
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(.2f), dim.push_back(1.f);
	string shape("cylinder");
	color4 col(0.,1.,1.);
	Maze *maze = new Maze();
	this->init(pos, or, ver, shape, dim, .01f, col, maze);
}

Ghost::Ghost(color4 col, Maze *maze){
	vf pos, or, ver, dim;
	pos.push_back(randomm(-maze->size[0]/2, maze->size[0]/2)), pos.push_back(0.f), pos.push_back(randomm(-maze->size[2]/2, maze->size[2]/2));
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(.2f), dim.push_back(1.f);
	string shape("cylinder");
	this->init(pos, or, ver, shape, dim, .1f, col, maze);
}

Ghost::Ghost(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color, Maze *maze){
	this->init(position, orientn, vertical, shape, dimentions, speed, color, maze);
}

void Ghost::draw(){
	glPushMatrix();
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	glRotatef(90.f, -1.f, 0.f, 0.f);
	glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
	if (this->shape=="cylinder"){
		glutSolidCylinder(this->dimentions[0], this->dimentions[1], 32, 32);
	}
	glRotatef(-90.f, -1.f, 0.f, 0.f);
	glTranslatef(-this->position[0], -this->position[1], -this->position[2]);
	glPopMatrix();
}

void Ghost::moveForward(){
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

void Ghost::moveLeft(){
	moving = true;
	vf fin = rotateaboutaxisbyangle(orientn,origin,vertical,90.f);
	for (int i = 0; i < 90; i++){
		orientn = rotateaboutaxisbyangle(orientn,origin,vertical,1.f);
		Sleep(1);
	}
	orientn = fin;
	moving = false;
}

void Ghost::moveRight(){
	moving = true;
	vf fin = rotateaboutaxisbyangle(orientn,origin,vertical,-90.f);
	for (int i = 0; i < 90; i++){
		orientn = rotateaboutaxisbyangle(orientn,origin,vertical,-1.f);
		Sleep(1);
	}
	orientn = fin;
	moving = false;
}

void Ghost::moveBack(){
	moving = true;
	vf fin = rotateaboutaxisbyangle(orientn,origin,vertical,180.f);
	for (int i = 0; i < 180; i++){
		orientn = rotateaboutaxisbyangle(orientn,origin,vertical,1.f);
		Sleep(1);
	}
	orientn = fin;
	moving = false;
}

Ghost::~Ghost(){
}

void Ghost::init(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color, Maze *maze){
	this->position = position, this->orientn = orientn, this->vertical = vertical;
	this->shape = shape, this->dimentions = dimentions;
	this->speed = speed;
	this->color = color;
	this->maze = maze;
	this->angle = 0.f;
	this->moving = false;
}