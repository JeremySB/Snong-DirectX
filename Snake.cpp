#include "Snake.h"
#include <iostream>

Snake::Snake():initialized(false),linksUsed(0),dead(false),appendNum(SNAKE_HEAD_SIZE){
}

Snake::~Snake(){
}

void Snake::initialize(Game *game, int x, int y,  const char *headTexture, const char *linkTexture){
	// checks for initialization
	if(initialized)
		throw GameError::exception("Snake was already initialized");

	// makes sure we can make the textures
	if (!this->linkTexture.initialize(game->getGraphics(), linkTexture))
		throw GameError::exception("SnakeLink texture could not be initialized");

	if (!this->headTexture.initialize(game->getGraphics(), headTexture))
		throw GameError::exception("Snake Head texture could not be initialized");
	
	defaultX = x;
	defaultY = y;
	
	// initializes all of the links we will use 
	for ( int i = 0; i < SNAKE_MAX_LENGTH; i++){
		//Image* sprite = &links[i];
		if(i < SNAKE_HEAD_SIZE && !links[i].initialize(game, this->headTexture.getWidth(),this->headTexture.getHeight(), 1, &this->headTexture))
			throw GameError::exception("Snake link not able to initialize");
		
		if(i >= SNAKE_HEAD_SIZE && !links[i].initialize(game, this->linkTexture.getWidth(),this->linkTexture.getHeight(), 1, &this->linkTexture))
			throw GameError::exception("Snake link not able to initialize");
		
		links[i].setScale( BOARD_CELL_HEIGHT / (float)(i < SNAKE_HEAD_SIZE ? this->headTexture : this->linkTexture).getHeight());
		updateLink(links[i], defaultX, defaultY);
	}
	
	links[linksUsed++].inUse = true;
	updateLink(links[linksUsed], defaultX, defaultY);
	appendNum--;

	this->initialized = true;
}

void Snake::wipe(){
	isInitialized();
	for ( int i = 1; i < linksUsed; i++){
		links[i].inUse = false;
	}
	appendNum = SNAKE_HEAD_SIZE - 1;
	linksUsed = 1;
	updateLink(links[0], defaultX, defaultY);
	dead = false;
}

void Snake::move(){
	isInitialized();

	int nextX = 0, nextY = 0;
	int Xmovement = 0, Ymovement = 0;
	int degrees=0;
	// demo function showing how append would be 
	if(appendNum > 0 && linksUsed < SNAKE_MAX_LENGTH){
		links[linksUsed++].inUse = true;
		appendNum--;
	}

	switch(movementDir){
	case(Right):
		 Xmovement++;
		 degrees = 90;
		 break;
	
	case(Left):
		Xmovement--;
		degrees = 270;
		break;
	
	case(Up):
		Ymovement--;
		degrees = 0;
		break;
	
	case(Down):
		Ymovement++;
		degrees = 180;
		break;
	}
	
	nextX = Xmovement + links[0].boardX;
	nextY = Ymovement + links[0].boardY;
	
	if(nextX < 0 || nextX > BOARD_WIDTH || nextY < 0 || nextY > BOARD_HEIGHT)
		dead = true;

	for(int currentLink = linksUsed - 1; currentLink > 0; --currentLink){
		D3DXVECTOR2 direction;
		direction.x = links[currentLink].boardX - links[currentLink-1].boardX;
		direction.y = links[currentLink].boardY - links[currentLink-1].boardY;
		// update x/y in accordance with the next link in the chain
		if(links[currentLink - 1].boardX == nextX && links[currentLink - 1].boardY == nextY)
			dead = true;
		links[currentLink].setVelocity(direction);
		updateLink(links[currentLink], links[currentLink-1].boardX, links[currentLink-1].boardY);
		links[currentLink].setDegrees(links[currentLink-1].getDegrees());
	}

	updateLink(links[0], nextX, nextY);
	links[0].setDegrees(degrees);
}

void Snake::append(UINT toAdd){
	appendNum += toAdd;
}

Direction Snake::getMovementDirection(){
	isInitialized();
	return movementDir;
}

void Snake::setMovementDirection(Direction newDir){
	isInitialized();
	movementDir = newDir;
}

void Snake::draw(){
	isInitialized();

	for( int i = 0; i < linksUsed && links[i].inUse; ++i){
		links[i].draw();
	}
}

Entity** Snake::getEntities(){
	Entity *ret[SNAKE_HEAD_SIZE];
	for(int currentHead = 0; currentHead < SNAKE_HEAD_SIZE; currentHead++){
		ret[currentHead] = &links[currentHead];
	}
	return ret;
}

void Snake::setDead(bool state){
	dead = state;
}

bool Snake::isDead() const{
	return dead;
}

void Snake::onLostDevice(){
	isInitialized();
	headTexture.onLostDevice();
	linkTexture.onLostDevice();
	headTexture.onLostDevice();
}

void Snake::onResetDevice(){
	isInitialized();
	headTexture.onResetDevice();
	linkTexture.onResetDevice();
	headTexture.onResetDevice();
}

inline void Snake::isInitialized(){
	if(!this->initialized)
		throw GameError::exception("Snake is not initialized");
}

void Snake::updateLink(Link &input, int newX, int newY){
	input.boardX = newX;
	input.boardY = newY;
	input.setX(newX * BOARD_CELL_WIDTH);
	input.setY(newY * BOARD_CELL_HEIGHT);
}