#include "Headers.h"
#include "Functions.h"
#include "Maze.h"
#include "Pac.h"

#ifndef _GHOST_H
#define _GHOST_H

class Ghost{
public:
	vf position;			// Position
	vf orientn;				// Orientation
	vf vertical;			// Vertical vector
	string shape;
	vf dimentions;			// dimentions
	float speed, angle;
	color4 color; 
	Maze *maze;
	bool moving;
	Pac *pacman;
	
	Ghost();
	Ghost(color4 col, Maze *maze, Pac *pacman);
	Ghost(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color, Maze *maze, Pac *pacman);
	void draw();
	void moveForward();
	void moveLeft();
	void moveRight();
	void moveBack();
	~Ghost();

private:
	void init(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color, Maze *maze, Pac *pacman);

};

#endif