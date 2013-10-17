#include "Headers.h"
#include "Functions.h"

class Pac{
	vf position;			// Position
	vf orientn;				// Orientation
	vf vertical;			// Vertical vector
	string shape;
	vf dimentions;			// dimentions
	double speed;
	color4 color; 

public:
	Pac();
	Pac(vf position, vf orientn, vf vertical, string shape,	vf dimentions, double speed, color4 color);
	void draw();
	void moveForward();
	~Pac();

private:
	void init(vf position, vf orientn, vf vertical, string shape, vf dimentions, double speed, color4 color);

};