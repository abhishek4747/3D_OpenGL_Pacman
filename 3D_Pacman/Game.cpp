#include "Game.h"

Game::Game(){
	this->initGame();
}

bool Game::isPaused(){
	return this->gamePaused;
}

void Game::togglePause(){
	this->gamePaused = !this->gamePaused;
}

void Game::initGame(){
	this->gamePaused = false;
	this->level = 1;
	this->ghostsMoving = false;
	maze = new Maze("TheGameMatrix.txt");
	pacman = new Pac(maze);
	ghost.resize(0);
	ghost.push_back(new Ghost(yellow, maze, pacman));
	ghost.push_back(new Ghost(purple, maze, pacman));
	ghost.push_back(new Ghost(pink, maze, pacman));
	ghost.push_back(new Ghost(green, maze, pacman));

}


bool Game::canAgentMove(Agent *p, Maze *m){
	vf next(3);
	for (int i = 0; i < 3; i++){
		p->posmtx.lock();
		p->ormtx.lock();
		next[i] = p->position[i] + p->orientn[i]*p->dimentions[0]/2;
		p->ormtx.unlock();
		p->posmtx.unlock();
	}

	int x = static_cast<int>(next[0]+m->size[0]/2) ;
	int z = static_cast<int>(next[2]+m->size[2]/2) ;
	
	if (x<0|| z<0 || x>m->size[0] || z>m->size[2] || m->mazeMat[z][x]>10){
		return false;
	}else if(m->mazeMat[z][x]==6){
		m->mazeMat[z][x] = 0;
	}
	return true;
}

void Game::randomMoveGhost(int i,int turn){
	if (!ghost[i]->moving){
		int m = 30;
		int r = random(0,m);
		if (r==0){
			thread t1(&Ghost::moveLeft,ghost[i]);
			t1.detach();
			// ghost[i]->moveLeft();
		}else if (r==1){
			thread t1(&Ghost::moveRight,ghost[i]);
			t1.detach();
			// ghost[i]->moveRight();
		}else if (r==2){
			thread t1(&Ghost::moveBack,ghost[i]);
			t1.detach();
			// ghost[i]->moveBack();
		}
	}
}

