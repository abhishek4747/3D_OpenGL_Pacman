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
	int timer;

	Game();
	
	void startGame();
	void changeLevel();
	
	void startTimer();
	
	bool isPaused();
	void togglePause();

	vf canAgentMove(Agent *p, Maze *m);
	void randomMoveGhost(int i,int turn = 1);
	
	void draw();
	void moveObjects();
	void MainLoop();
private:
	bool gamePaused;
	void initGame();

};