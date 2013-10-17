#include "Pac.h"

Pac::Pac(){
	vf pos, or, ver, dim;
	pos.push_back(0.f), pos.push_back(0.f), pos.push_back(0.f);
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(.2f);
	string shape("sphere");
	color4 col(0.,1.,1.);
	this->init(pos, or, ver, shape, dim, .01, col);
}

Pac::Pac(vf position, vf orientn, vf vertical, string shape, vf dimentions, double speed, color4 color){
	this->init(position, orientn, vertical, shape, dimentions, speed, color);
}

void Pac::draw(){
	glPushMatrix();
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
	if (this->shape=="sphere"){
		glutSolidSphere(this->dimentions[0], 32, 32);
	}
	glTranslatef(-this->position[0], -this->position[1], -this->position[2]);
	glPopMatrix();
}

void Pac::moveForward(){
	double mag = magnitue(this->orientn);
	for (size_t i = 0; i < this->position.size(); i++){
		this->position[i] += this->orientn[i]*this->speed/mag;
	}
	
}

Pac::~Pac(){
}

void Pac::init(vf position, vf orientn, vf vertical, string shape,	vf dimentions, double speed, color4 color){
	this->position = position, this->orientn = orientn, this->vertical = orientn;
	this->shape = shape, this->dimentions = dimentions;
	this->speed = speed;
	this->color = color;
}