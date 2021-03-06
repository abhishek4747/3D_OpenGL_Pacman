#include "Ghost.h"

Ghost::Ghost(){
	Agent::Agent();
	this->color = color4(0.,1.,1.);
	this->shape = "cylinder";
	this->dimentions.resize(0);
	this->dimentions.push_back(.4f), this->dimentions.push_back(1.f);
	this->maze = new Maze(), this->pacman = new Pac();
}

Ghost::Ghost(color4 col, Maze *maze, Pac *pacman, vf pos){
	vf or, ver, dim;
	// pos.push_back(randomm(-maze->size[0]/2, maze->size[0]/2)), pos.push_back(0.f), pos.push_back(randomm(-maze->size[2]/2, maze->size[2]/2));
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(.4f), dim.push_back(1.f);
	string shape("cylinder");
	this->init(pos, or, ver, shape, dim, .1f, col, maze, pacman);
}

Ghost::Ghost(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color, Maze *maze, Pac *pacman){
	this->init(position, orientn, vertical, shape, dimentions, speed, color, maze, pacman);
}

void Ghost::draw(){
	if (!eaten){
		glPushMatrix();
		posmtx.lock();
		glTranslatef(this->position[0], this->position[1], this->position[2]);
		posmtx.unlock();
		glRotatef(90.f, -1.f, 0.f, 0.f);
		if (weak)
			glColor4f(navyblue.r, navyblue.g, navyblue.b, navyblue.a);
		else
			glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
		if (this->shape=="cylinder"){
			glutSolidCylinder(this->dimentions[0], this->dimentions[1], 8, 1);
		}
		glTranslatef(0.f, 0.f, this->dimentions[1]);
		glutSolidSphere(this->dimentions[0], 8, 8);
		//glTranslatef(0.f, 0.f, -this->dimentions[0]*2);
		this->ormtx.lock();
		vf or = this->orientn;
		this->ormtx.unlock();
		glTranslatef(or[0]*this->dimentions[0],or[2]*(this->dimentions[0]*7/8), or[1]*this->dimentions[0]);
		glColor3f(white.r,white.g,white.b);
		glPushMatrix();
		glTranslatef(0.1f*or[2],0.1f*or[0],0.f);
		glutSolidSphere(this->dimentions[0]/4, 8, 8);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-0.1f*or[2],-0.1f*or[0],0.f);
		glutSolidSphere(this->dimentions[0]/4, 8, 8);
		glPopMatrix();
		//glTranslatef(0.f, 0.f, -this->dimentions[1]);
		//glRotatef(-90.f, -1.f, 0.f, 0.f);
		//glTranslatef(-this->position[0], -this->position[1], -this->position[2]);
		glPopMatrix();
	}	
}


void Ghost::init(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color, Maze *maze, Pac *pacman){
	this->position = position, this->orientn = orientn, this->vertical = vertical;
	this->shape = shape, this->dimentions = dimentions;
	this->speed = speed;
	this->color = color;
	this->maze = maze;
	this->pacman = pacman;
	this->moving = false;
	this->weak = false;
	this->eaten = false;
}