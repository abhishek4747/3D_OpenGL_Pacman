#include "Headers.h"

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

typedef vector<double> vd;
typedef vector<float>  vf;

template <typename T> T degreeToRadian(T degree){
	T c180 = static_cast<T>(180);
	T c22 = static_cast<T>(2);
	T c7 = static_cast<T>(7);
	return ((degree/c180)*(c22/c7));
}

template <typename T> T magnitue(vector<T> vec){
	return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

class color3{
public:
	float r, g, b, max;
	color3();
	color3(float r, float g, float b, float max= 1.);
	~color3();
private:
	void init(float r, float g, float b, float max);

};

class color4{
public:
	float r, g, b, a, max;
	color4();
	color4(float r, float g, float b, float a=1., float max= 1.);
	~color4();

private:
	void init(float r, float g, float b, float a, float max);

};

#endif