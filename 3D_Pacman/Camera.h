#include "Headers.h"

#ifndef _CAMERA
#define _CAMERA

typedef enum cameraType{ARIEL, FREE, FOLLOW, TOP, FRONT, C_FIXED, NOTFIXED} cameraType;

class Camera{
public:
	double eyex, eyey, eyez;
	double centerx, centery, centerz;
	double upx, upy, upz;
	cameraType cameratype;

	Camera();
	Camera(double eyex, double eyey, double eyez, 
		double centerx, double centery, double centerz, 
		double upx, double upy, double upz);
	~Camera();

private:
	void init(double eyex, double eyey, double eyez, 
		double centerx, double centery, double centerz, 
		double upx, double upy, double upz);
};

#endif