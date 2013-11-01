#include "Headers.h"

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#define PI 3.14159265

typedef vector<double> vd;
typedef vector<float>  vf;

extern vf origin;

void fInit();

void newl();

template <typename T> T setPrecision(T number, int digits){
	double p = pow(10.,digits);
	return static_cast<T>(static_cast<int>(number*p)/p);
}

template <typename T> void print(T v){
	cout<<v<<" "; 
}

template <typename T> void printVar(T v){
	cout<<v<<" "; newl();
}

template <typename T> void printVector(vector<T> v){
	for (size_t i = 0; i < v.size(); i++)
		print(v[i]);
	newl();
}

template <typename T> T degreeToRadian(T degree){
	/*T c180 = static_cast<T>(180);
	T c22 = static_cast<T>(2);
	T c7 = static_cast<T>(7);
	return ((degree/c180)*(c22/c7));*/
	double angleradians = degree * 22.0 / (180.0 * 7.);
	return static_cast<T>(angleradians);
}

template <typename T> T magnitue(vector<T> vec){
	return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

template <typename T> T dotproduct(vector<T> u, vector<T> v){
	return u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
}

template <typename T> T crossproduct(T u, T v){
	T ret;
	ret.push_back(u[1]*v[2] - u[2]*v[1]);
	ret.push_back(u[2]*v[0] - u[0]*v[2]);
	ret.push_back(u[0]*v[1] - u[1]*v[0]);
	return ret;
}

template <typename T> T anglebw(vector<T> u, vector<T> v){
	vector<T> c = crossproduct(u,v);
	return static_cast<T>((acos(dotproduct(u,v)/(magnitue(u)*magnitue(v))) * 180. * 7.)/22.)*(c[1]>0?-1:1);
}

template <typename T> vector<T> rotateaboutaxisbyangle(vector<T> point, vector<T> abc, vector<T> uvw, T angle){
	/*
	(1) Translate space so that the rotation axis passes through the origin.
	(2) Rotate space about the z axis so that the rotation axis lies in the xz plane.
	(3) Rotate space about the y axis so that the rotation axis lies along the z axis.
	(4) Perform the desired rotation by   about the z axis.
	(5) Apply the inverse of step (3).
	(6) Apply the inverse of step (2).
	(7) Apply the inverse of step (1).
	http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
	*/
	/*T uvwMag = magnitue(uvw);
	if (uvwMag)
		for (size_t i = 0; i < uvw.size(); i++)
			uvw[i] /= uvwMag;*/
	T	x = point[0], y = point[1], z = point[2],
		a = abc[0], b = abc[1], c = abc[2],
		u = uvw[0], v = uvw[1], w = uvw[2];
	T cosTheta = setPrecision(cos(degreeToRadian(angle)),3), sinTheta = setPrecision(sin(degreeToRadian(angle)),3) ;
	vector<T> ret;
	ret.push_back((a*(v*v + w*w) - u*(b*v + c*w - u*x - v*y - w*z))*(1 - cosTheta) + x*cosTheta + (-c*v + b*w - w*y + v*z)*sinTheta);
	ret.push_back((b*(u*u + w*w) - v*(a*u + c*w - u*x - v*y - w*z))*(1 - cosTheta) + y*cosTheta + ( c*u - a*w - w*x + u*z)*sinTheta);
	ret.push_back((c*(u*u + v*v) - w*(a*u + b*v - u*x - v*y - w*z))*(1 - cosTheta) + z*cosTheta + (-b*u + a*v - v*x + u*y)*sinTheta);
	return ret;
}

template <typename T> T randomm(T max, T min){
	return static_cast<T>((static_cast<double>(rand()) / (RAND_MAX)) * (max-min+1)) + min;
}

int random (int low, int high);

class color3{
public:
	float r, g, b;
	color3();
	color3(float r, float g, float b, float max= 1.);
	~color3();
private:
	void init(float r, float g, float b, float max);
};

class color4{
public:
	float r, g, b, a;
	color4();
	color4(float r, float g, float b, float a=1., float max= 1.);
	~color4();

private:
	void init(float r, float g, float b, float a, float max);
};

void DrawEllipsoid(float fA, float fB, float fC, unsigned int uiStacks = 32, unsigned int uiSlices = 32);

/*******************************COLOR TABLE************************************
			http://gucky.uni-muenster.de/cgi-bin/rgbtab-en					  
******************************************************************************/
extern color4 red;
extern color4 blue;
extern color4 green;
extern color4 yellow;
extern color4 purple;
extern color4 pink;
extern color4 white,black;
extern color4 grey;
extern color4 navyblue;


#endif

