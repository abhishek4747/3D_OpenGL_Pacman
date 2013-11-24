#include "Headers.h"
#include "Functions.h"
#include "Pac.h"
#include "Ghost.h"
#include "Maze.h"

class Game{
public:
	int level;
	Pac *pacman;
	vector<Ghost*> ghost;
	Maze *maze;
	bool ghostsMoving;
	
	Game();
	
	void startGame();
	void changeLevel();
	
	bool isPaused();
	void togglePause();

	vf canAgentMove(Agent *p, Maze *m);
	void randomMoveGhost(int i,int turn = 1);
	
	void draw();
	void moveObjects();
private:
	bool gamePaused;
	void initGame();

};