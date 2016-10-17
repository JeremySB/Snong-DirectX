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
	
	//links[linksUsed++].inUse = true;
	links[linksUsed++].setVisible(true);
	updateLink(links[linksUsed], defaultX, defaultY);
	appendNum--;

	this->initialized = true;
}

Snake::Link::Link(): Entity(), boardX(0),boardY(0){
	edge = SNAKE_LINK_RECT;
	spriteData.rect = SNAKE_LINK_RECT;
	radius = SNAKE_LINK_RADIUS;
	mass = SNAKE_LINK_MASS;
	collisionType = entityNS::CIRCLE;
}

void Snake::wipe(){
	isInitialized();
	for ( int i = 1; i < linksUsed; i++){
		links[i].setVisible(false);
		links[i].setActive(false);
	}
	appendNum = SNAKE_HEAD_SIZE - 1;
	linksUsed = 1;
	updateLink(links[0], defaultX, defaultY);
	dead = false;
}

void Snake::move(){
	isInitialized();

	VECTOR2 movement(0,0);//int Xmovement = 0, Ymovement = 0;
	int degrees=0;
	int currentLink = 0;
	// demo function showing how append would be 
	if(appendNum > 0 && linksUsed < SNAKE_MAX_LENGTH){
		if(linksUsed < SNAKE_HEAD_SIZE)
			links[linksUsed].setActive(true);
		links[linksUsed++].setVisible(true);
		appendNum--;
	}

	switch(movementDir){
	case(Right):
		 movement.x++;
		 degrees = 90;
		 break;
	
	case(Left):
		movement.x--;
		degrees = 270;
		break;
	
	case(Up):
		movement.y--;
		degrees = 0;
		break;
	
	case(Down):
		movement.y++;
		degrees = 180;
		break;
	}
	VECTOR2 next(movement.x + links[0].boardX, movement.y + links[0].boardY);
	
	if(next.x < 0 + 1 || next.x >= BOARD_WIDTH - 1 || next.y < 0 || next.y >= BOARD_HEIGHT)
		dead = true;

	for(int currentLink = linksUsed - 1; currentLink > 0; --currentLink){
		// update x/y in accordance with the next link in the chain
		if(links[currentLink - 1].boardX == next.x && links[currentLink - 1].boardY == next.y)
			dead = true;
		
		links[currentLink].setVelocity(VECTOR2(links[currentLink].boardX - links[currentLink - 1].boardX,
			links[currentLink].boardY - links[currentLink - 1].boardY));

		updateLink(links[currentLink], links[currentLink-1].boardX, links[currentLink-1].boardY);
		
		links[currentLink].setDegrees(links[currentLink-1].getDegrees());
	}
	updateLink(links[0], next.x, next.y);
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

	for( int i = 0; i < linksUsed && links[i].getVisible(); ++i){
		links[i].draw();
	}
}

Entity** Snake::getEntities(){
	Entity **ret = new Entity *[SNAKE_HEAD_SIZE];
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