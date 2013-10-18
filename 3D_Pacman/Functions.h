#include "Headers.h"

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

typedef vector<double> vd;
typedef vector<float>  vf;

extern vf origin;

void fInit();

void newl();

template <typename T> T setPrecision(T number, int digits){
	double p = pow(10.,digits);
	return static_cast<T>(static_cast<int>(number*p)/p);
}

template <typename T> void printVar(T v){
	cout<<v<<" ";
}

template <typename T> void printVector(vector<T> v){
	for (size_t i = 0; i < v.size(); i++)
		printVar(v[i]);
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

	cout<<"point :";printVar(x);printVar(y);printVar(z);printVector(point);
	cout<<"abc :";printVar(a);printVar(b);printVar(c);printVector(abc);
	cout<<"uvw :";printVar(u);printVar(v);printVar(w);printVector(uvw);
	cout<<"angle :";printVar(angle);newl();
	cout<<"cosT  :";printVar(cosTheta);newl();
	cout<<"sinT  :";printVar(sinTheta);newl();


	vector<T> ret;
	ret.push_back((a*(v*v + w*w) - u*(b*v + c*w - u*x - v*y - w*z))*(1 - cosTheta) + x*cosTheta + (-c*v + b*w - w*y + v*z)*sinTheta);
	ret.push_back((b*(u*u + w*w) - v*(a*u + c*w - u*x - v*y - w*z))*(1 - cosTheta) + y*cosTheta + ( c*u - a*w - w*x + u*z)*sinTheta);
	ret.push_back((c*(u*u + v*v) - w*(a*u + b*v - u*x - v*y - w*z))*(1 - cosTheta) + z*cosTheta + (-b*u + a*v - v*x + u*y)*sinTheta);
	return ret;
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