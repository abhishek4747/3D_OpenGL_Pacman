#include "Headers.h"
#include "Functions.h"
#include "Maze.h"
#include "Agent.h"

#ifndef _PAC_H
#define _PAC_H

class Pac : public Agent{
public:
	Maze *maze;

	Pac();
	Pac(Maze *maze);
	Pac(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color, Maze *maze);
	void draw();
	void moveForward();

private:
	void init(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color, Maze *maze);

};

#endif // !_PAC_H