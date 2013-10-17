#include "Maze.h"

Maze::Maze(){
	vf size;
	size.push_back(10.f), size.push_back(static_cast<float>(INT_MAX)),size.push_back(15.f);
	this->init(size);
}

void Maze::draw(){
	glPushMatrix();
	
	// A white colored mesh
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	glBegin(GL_LINES);
	/*for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
		glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
		glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
	}*/
	for (GLfloat i = -this->size[0]/2; i <= this->size[0]/2; i += 0.25){
		glVertex3f(i, 0, -this->size[2]/2); glVertex3f(i, 0, this->size[2]/2);
	}
	for (GLfloat i = -this->size[2]/2; i <= this->size[2]/2; i += 0.25){
		glVertex3f(-this->size[0]/2, 0 ,i); glVertex3f(this->size[0]/2, 0, i);
	}
	glEnd();
	glTranslatef(-this->position[0], -this->position[1], -this->position[2]);
	glPopMatrix();
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