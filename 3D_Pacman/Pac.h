#include "Headers.h"
#include "Functions.h"
#include "Maze.h"

class Pac{
public:
	vf position;			// Position
	vf orientn;				// Orientation
	vf vertical;			// Vertical vector
	string shape;
	vf dimentions;			// dimentions
	float speed;
	color4 color; 
	Maze *maze;

	Pac();
	Pac(Maze *maze);
	Pac(vf position, vf orientn, vf vertical, string shape,	vf dimentions, float speed, color4 color, Maze *maze);
	void draw();
	void moveForward();
	void moveLeft();
	~Pac();

private:
	void init(vf position, vf orientn, vf vertical, string shape, vf dimentions, float speed, color4 color, Maze *maze);

};