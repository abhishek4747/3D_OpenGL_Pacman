#include "Agent.h"

Agent::Agent(){
	vf pos, or, ver, dim;
	pos.push_back(0.f), pos.push_back(0.f), pos.push_back(0.f);
	or.push_back(0.f),  or.push_back(0.f),  or.push_back(-1.f);
	ver.push_back(0.f), ver.push_back(1.f), ver.push_back(0.f);
	dim.push_back(.2f);
	string shape("sphere");
	color4 col(0.,1.,1.);
	this->init(pos, or, ver, shape, dim, .01f, col);
}

Agent::Agent(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color){
	this->init(position, orientn, vertical, shape, dimentions, speed, color);
}

void Agent::draw(){
}

void Agent::moveForward(){

}

void Agent::moveLeft(){
	moving = true;
	moveSomewhere(90.f,3);
	moving = false;
}

void Agent::moveRight(){
	moving = true;
	moveSomewhere(-90.f,3);
	moving = false;
}

void Agent::moveBack(){
	moving = true;
	moveSomewhere(180.f,3);
	moving = false;
}

Agent::~Agent(){
}

void Agent::integralPosition(){
	for (int i = 0; i < 3; i++){
		if (i!=1)
			position[i] = static_cast<float>(static_cast<int>(position[i]+(position[i]<0?-0.5f:0.5f)));
	}
}

vf Agent::getIntegralPosition(){
	vf ret;
	for (int i = 0; i < 3; i++){
		ret.push_back( static_cast<float>( static_cast<int>(position[i]+(position[i]<0?-0.5f:0.5f)) ) );
	}
	return ret;
}

void Agent::moveSomewhere(float totaldegree, int fast){
	mtx.lock();
	float direction = totaldegree>0? 1.f: -1.f;
	vf fin = rotateaboutaxisbyangle(orientn,origin,vertical,totaldegree);
	mtx.unlock();
	for (int i = 0; i < abs(totaldegree)/fast; i++){
		mtx.lock();
		orientn = rotateaboutaxisbyangle(orientn,origin,vertical,fast*direction);
		mtx.unlock();
		Sleep(1*fast);
	}
	mtx.lock();
	orientn = fin;
	mtx.unlock();
	
	//integralPosition();
	thread t1(&Agent::translate,this,getIntegralPosition(),100);
	t1.detach();
}

void Agent::translate(vf destination, int millisecs){
	vf delta;
	for (int i = 0; i < 3; i++){
		delta.push_back((destination[i]-position[i])/100.f);
	}
	for (int i = 0; i < 100; i++){
		for (int i = 0; i < 3; i++){
			position[i] += delta[i];
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
