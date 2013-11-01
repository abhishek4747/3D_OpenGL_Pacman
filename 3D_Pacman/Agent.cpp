#include "Agent.h"

Agent::Agent(){
	vf pos, or, ver, dim;
	pos.push_back(0.f), pos.push_back(0.f), pos.push_back(0.f);
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(.2f);
	string shape("sphere");
	color4 col(0.,1.,1.);
	this->init(pos, or, ver, shape, dim, .05f, col);
}

Agent::Agent(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color){
	this->init(position, orientn, vertical, shape, dimentions, speed, color);
}

void Agent::draw(){
}

void Agent::moveLeft(){
	moving = true;
	moveSomewhere(90.f,1);
	moving = false;
}

void Agent::moveRight(){
	moving = true;
	moveSomewhere(-90.f,1);
	moving = false;
}

void Agent::moveBack(){
	moving = true;
	moveSomewhere(180.f,1);
	moving = false;
}

void Agent::moveForward(){
	for (size_t i = 0; i < 3; i++){
		posmtx.lock();
		ormtx.lock();
		this->position[i] = this->position[i]+this->orientn[i]*this->speed;
		ormtx.unlock();
		posmtx.unlock();
	}
}


Agent::~Agent(){
}

void Agent::integralPosition(){
	for (int i = 0; i < 3; i++){
		if (i!=1){
			posmtx.lock();
			position[i] = static_cast<float>(static_cast<int>(position[i]+(position[i]<0?-0.5f:0.5f)));
			posmtx.unlock();
		}
	}
}

vf Agent::getIntegralPosition(){
	vf ret;
	for (int i = 0; i < 3; i++){
		posmtx.lock();
		ret.push_back( static_cast<float>( static_cast<int>(position[i]+(position[i]+(position[i]<0?-0.5f:0.5f)<0?-0.5f:0.5f))) );
		posmtx.unlock();
	}
	return ret;
}

void Agent::moveSomewhere(float totaldegree, int fast){
	float direction = totaldegree>0? 1.f: -1.f;
	ormtx.lock();
	vf fin = rotateaboutaxisbyangle(orientn,origin,vertical,totaldegree);
	ormtx.unlock();
	for (int i = 0; i < abs(totaldegree)/fast; i++){
		ormtx.lock();
		orientn = rotateaboutaxisbyangle(orientn,origin,vertical,fast*direction);
		ormtx.unlock();
		Sleep(1*fast);
	}
	ormtx.lock();
	orientn = fin;
	ormtx.unlock();
	
	//integralPosition();
	thread t1(&Agent::translate,this,getIntegralPosition(),200);
	t1.detach();
}

void Agent::translate(vf destination, int millisecs){
	vf delta;
	for (int i = 0; i < 3; i++){
		posmtx.lock();
		delta.push_back((destination[i]-position[i])/100.f);
		posmtx.unlock();
	}
	for (int i = 0; i < 100; i++){
		for (int i = 0; i < 3; i++){
			posmtx.lock();
			position[i] += delta[i];
			posmtx.unlock();
		}
		Sleep(millisecs/100);
	}
}

void Agent::init(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color){
	this->position = position, this->orientn = orientn, this->vertical = vertical;
	this->shape = shape, this->dimentions = dimentions;
	this->speed = speed;
	this->color = color;
	this->moving = false;
}
