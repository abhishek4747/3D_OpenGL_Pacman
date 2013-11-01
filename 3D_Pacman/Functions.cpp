#include "Functions.h"

vf origin;
color4 red, blue, green, yellow, purple, pink, white, black, grey, navyblue;

color3::color3(){
	this->init(0., 0., 0., 1.);
}

color3::color3(float r, float g, float b, float max){
	this->init(r, g, b, max);
}

void color3::init(float r, float g, float b, float max){
	this->r = r/max, this->g = g/max, this->b = b/max;
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
	this->r = r/max, this->g = g/max, this->b = b/max, this->a = a/max;
}

int random (int low, int high) {
	srand(time(0)*rand());
    if (low > high) return high;
    return low + (std::rand() % (high - low + 1));
}

void fInit(){
	for (int i = 0; i < 3; i++)
		origin.push_back(0.f);
	red		= color4(1.f,0.f,0.f);
	green	= color4(0.f,1.f,0.f);
	blue	= color4(0.f,0.f,1.f);
	yellow	= color4(1.f,1.f,0.f);
	purple	= color4(160.f,  32.f,	240.f,  255.f,  255.f);
	pink	= color4(255.f, 105.f,	180.f,  255.f,  255.f); 
	grey	= color4(105.f, 105.f,	105.f,  255.f,  255.f);
	navyblue= color4(0.f,	0.f,	128.f,	255.f,	255.f);
	white	= color4(1.f,1.f,1.f);
	black   = color4(0.f,0.f,0.f);


}

void newl(){
	cout<<endl;
}

void DrawEllipsoid(float fA, float fB, float fC, unsigned int uiStacks, unsigned int uiSlices){
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	for(float t = -PI/2; t <= (PI/2)+.0001; t += tStep){
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -PI; s <= PI+.0001; s += sStep){
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
			glVertex3f(fA * cos(t+tStep) * cos(s), fB * cos(t+tStep) * sin(s), fC * sin(t+tStep));
		}
		glEnd();
	}
}
  
