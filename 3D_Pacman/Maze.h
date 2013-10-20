#include "Headers.h"
#include "Functions.h"

#ifndef _MAZE_H
#define _MAZE_H

class Maze{
public:
	vf size;
	vf position;			// Position
	vf normal;
	vf gravity;
	string shape;
	int level;
	color4 color;
	vector<vector<int>> mazeMat;

	Maze();
	Maze(string filename);
	void draw();
	void mazeReader(string filename);
	~Maze();

private:
	void init(vf size);

};

#endif