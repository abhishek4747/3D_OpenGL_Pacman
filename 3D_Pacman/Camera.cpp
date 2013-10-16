#include "Camera.h"

Camera::Camera(){
	this->init(5., 5., 5., 0., 0., 0., 0., 1., 0.);
}

Camera::Camera(double eyex, double eyey, double eyez, 
			   double centerx, double centery, double centerz, 
			   double upx, double upy, double upz){
	this->init(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void Camera::init(double eyex, double eyey, double eyez, 
		double centerx, double centery, double centerz, 
		double upx, double upy, double upz){
	this->eyex = eyex, this->eyey = eyey, this->eyez = eyez;
	this->centerx = centerx, this->centery = centery, this->centerz = centerz;
	this->upx = upx, this->upy = upy, this->upz = upz;
}

Camera::~Camera(){
}

