#include "Headers.h"
#include "Functions.h"

#ifndef _AGENT_H
#define _AGENT_H

class Agent{
public:
	vf position;			// Position
	vf orientn;				// Orientation
	vf vertical;			// Vertical vector

	// Shape and Dimentions
	string shape;	
	vf dimentions;		
	
	float speed;
	color4 color; 
	
	bool moving;
	mutex ormtx;
	mutex posmtx;

	Agent();
	Agent(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color);
	void draw();
	void moveForward();
	void moveLeft();
	void moveRight();
	void moveBack();
	void integralPosition();
	vf getIntegralPosition();
	void translate(vf destination, int millisecs=1000);
	~Agent();

private:
	void init(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color);
	void moveSomewhere(float totaldegree, int fast);

};

#endif // !_AGENT_H
