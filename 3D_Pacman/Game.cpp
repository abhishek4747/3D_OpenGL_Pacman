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
	this->timer = 0;
}

void Game::startGame(){
	thread t1(&Game::MainLoop,this);
	t1.detach();
}


vf Game::canAgentMove(Agent *p, Maze *m){
	// Get Next position of the agent
	vf next(3),nextP(3);
	for (int i = 0; i < 3; i++){
		p->posmtx.lock();
		p->ormtx.lock();
		next[i] = p->position[i] + p->orientn[i]*0.5f;
		nextP[i] = p->position[i] + p->orientn[i]*p->speed;
		p->ormtx.unlock();
		p->posmtx.unlock();
	}
	int x = static_cast<int>(next[0]+m->size[0]/2) ;
	int z = static_cast<int>(next[2]+m->size[2]/2) ;

	
	// Check if next is valid postion
	if (x<0|| z<0 || x>=m->mazeMat[0].size() || z>=m->mazeMat.size() || m->mazeMat[z][x]>10){
		// Going out of Maze or Hitting a wall
		nextP.resize(0);
		return nextP;
	}
	x = static_cast<int>(nextP[0]+m->size[0]/2) ;
	z = static_cast<int>(nextP[2]+m->size[2]/2) ;
	if (p==this->pacman){
		if(m->mazeMat[z][x]==6){
			m->mazeMat[z][x] = 0;
		}else if(m->mazeMat[z][x]==8){
			m->mazeMat[z][x] = 0;
			for (size_t i = 0; i < ghost.size(); i++){
				ghost[i]->weak = true;
			}
			if (this->timer==0){
				this->timer = 15;
				thread t1(&Game::startTimer,this);
				t1.detach();
				//startTimer();
			}else{
				this->timer = 15;
			}	
		}
	}
	if(m->mazeMat[z][x] > 0 && m->mazeMat[z][x]<6){
		for (size_t i = 0; i < m->mazeMat.size(); i++){
			for (size_t j = 0; j < m->mazeMat[0].size(); j++){
				if (!(i==z && j==x) && m->mazeMat[i][j]==m->mazeMat[z][x]){
					p->ormtx.lock();
					p->posmtx.lock();
					p->position[0] = j - m->size[0]/2 + 2*p->orientn[0];
					p->position[2] = i - m->size[2]/2 + 2*p->orientn[2];
					p->posmtx.unlock();
					p->ormtx.unlock();
					p->integralPosition();
					
					return canAgentMove(p,m);
				}
			}
		}
	} 
	return nextP;
}

void Game::randomMoveGhost(int i,int turn){
	if (!ghost[i]->moving){
		int m = 100;
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
				//this->pacman->moveForwardTo(next[0],next[1],next[2]);
				this->pacman->moveForward();
			}
			
			//this->pacman->moveForward();
			
		}
		// Ghosts
		for (size_t i = 0; i < this->ghost.size(); i++){
			vf next = this->canAgentMove(this->ghost[i],this->maze);
			if (next.size()==3) {
				//thread t1(&Ghost::moveForward,this->ghost[i]);
				//t1.detach();
				ghost[i]->moveForwardTo(next[0],next[1],next[2]);
			}
			if (!this->ghostsMoving & !this->isPaused()){
				//thread t1 (randomMoveGhost,i,0);
				//t1.detach();
				this->randomMoveGhost(i,0);
			}		
		}
	}
}


void Game::MainLoop(){
	while (true){
		moveObjects();
		Sleep(10);
	}
}

void Game::startTimer(){
	while(this->timer){
		// cout<<"Timer: "<<this->timer<<endl;
		this->timer--;
		Sleep(1000);
	}
	for (size_t i = 0; i < ghost.size(); i++){
		ghost[i]->weak = false;
	}
}