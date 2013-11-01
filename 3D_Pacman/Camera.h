#include "Headers.h"

class Camera{
public:
	double eyex, eyey, eyez;
	double centerx, centery, centerz;
	double upx, upy, upz;

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
