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


vf Game::canAgentMove(Agent *p, Maze *m){
	// Get Next position of the agent
	vf next(3),nextP(3);
	for (int i = 0; i < 3; i++){
		p->posmtx.lock();
		p->ormtx.lock();
		next[i] = p->position[i] + p->orientn[i]*p->dimentions[0]/2;
		nextP[i] = p->position[i] + p->orientn[i]*p->speed;
		p->ormtx.unlock();
		p->posmtx.unlock();
	}
	int x = static_cast<int>(next[0]+m->size[0]/2) ;
	int z = static_cast<int>(next[2]+m->size[2]/2) ;

	
	// Check if next is valid postion
	if (x<0|| z<0 || x>m->size[0] || z>m->size[2] || m->mazeMat[z][x]>10){
		// Going out of Maze or Hitting a wall
		nextP.resize(0);
		return nextP;
	}
	
	x = static_cast<int>(nextP[0]+m->size[0]/2) ;
	z = static_cast<int>(nextP[2]+m->size[2]/2) ;

	if(m->mazeMat[z][x]==6){
		m->mazeMat[z][x] = 0;
	}
	return nextP;
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

void Game::draw(){
	// Draw Maze
	if (this->maze ){
		this->maze->draw();
	}

	// Draw Pacman
	if (this->pacman){
		this->pacman->draw();
	}

	// Draw All Ghosts
	for (size_t i = 0; i < this->ghost.size(); i++){
		this->ghost[i]->draw();
	}
}

void Game::moveObjects(){
	if (!this->isPaused()){
		// Pacman
		if (this->pacman && !this->pacman->moving) {
			
			vf next = this->canAgentMove(this->pacman,this->maze);
			if (next.size()==3){
				//thread t1(&Pac::moveForwardTo,this->pacman,next[0],next[1],next[2]);
				//t1.detach();
				this->pacman->moveForwardTo(next[0],next[1],next[2]);
			}
			
			//this->pacman->moveForward();
			
		}
		// Ghosts
		for (size_t i = 0; i < this->ghost.size(); i++){
			/*
			if (!this->isPaused() && this->canAgentMove(this->ghost[i],this->maze)) {
				thread t1(&Ghost::moveForward,this->ghost[i]);
				t1.detach();
				//ghost[i]->moveForward();
			}
			if (!this->ghostsMoving & !this->isPaused()){
				this->randomMoveGhost(i,0);
				//thread t1 (randomMoveGhost,i,0);
				//t1.detach();
			}
			*/
		}
	}
}


void Game::MainLoop(){
	while (true){
		moveObjects();
		Sleep(10);
	}
}