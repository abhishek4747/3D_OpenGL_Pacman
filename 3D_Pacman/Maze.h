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

	vf pacInitPos;
	vf ghostInitPos[4];

	Maze();
	Maze(string filename);
	void draw();
	void mazeReader(string filename);
	vf getPosxyfromij(int i, int j);
private:
	void init(vf size);

};

#endif