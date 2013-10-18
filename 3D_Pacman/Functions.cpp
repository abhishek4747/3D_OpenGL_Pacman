#include "Functions.h"

vf origin;

color3::color3(){
	this->init(0., 0., 0., 1.);
}

color3::color3(float r, float g, float b, float max){
	this->init(r, g, b, max);
}

void color3::init(float r, float g, float b, float max){
	this->r = r, this->g = g, this->b = b, this->max = max;
}

color3::~color3(){
}


color4::color4(){
	this->init(0.,0.,0.,1.,1.);
}

color4::color4(float r, float g, float b, float a, float max){
	this->init(r,g,b,a,max);
}

color4::~color4(){
}

void color4::init(float r, float g, float b, float a, float max){
	this->r = r, this->g = g, this->b = b, this->a = a, this->max = max;
}

void fInit(){
	for (int i = 0; i < 3; i++)
		origin.push_back(0.f);
}

void newl(){
	cout<<endl;
}