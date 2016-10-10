#include "Snake.h"
#include <iostream>


Snake::~Snake(){

}

void Snake::initialize(Graphics *graphics, int append){
	if(initialized)
		throw GameError::exception("Snake was already initialized");

	if (!this->linkTexture.initialize(graphics,SNAKE_LINK_TEXTURE))
		throw GameError::exception("SnakeLink texture could not be initialized");
	if (!this->headTexture.initialize(graphics, SNAKE_HEAD_TEXTURE))
		throw GameError::exception("Snake Head texture could not be initialized");
	this->append = append;
	this->links[linksUsed++] = Link(graphics, &headTexture);
	append--;
	this->initialized = true;
}

void Snake::wipe(){
	isInitialized();
	for ( int i = SNAKE_MAX_LENGTH; i >= 0; i--){
		links[i].inUse = false;
	}
}

void Snake::move(){
	isInitialized();
	
	std::list<Link>::iterator currentLink;
	std::list<Link>::iterator nextLink;
	
	Image *sprite;
	int nextX = 0, nextY = 0;
	int Xmovement = 0, Ymovement = 0;

	if(append > 0){
		// demo function showing how append would be 
		links[].inUse = true;
		append--;
	}

	switch(movementDir){
	case(Right):
		 Xmovement++;
		 break;
	
	case(Left):
		Xmovement--;
		break;
	
	case(Up):
		Ymovement--;
		break;
	
	case(Down):
		Ymovement++;
		break;
	}
	currentLink = links.begin();
	nextX = Xmovement + currentLink->x;
	nextY = Ymovement + currentLink->y;
	if(nextX < 0 || nextX > BOARD_WIDTH || nextY < 0 || nextY > BOARD_HEIGHT)
		dead = true;
	if(!links.empty()){
	for(currentLink = --links.end(); currentLink != (++links.begin()) && currentLink != links.begin(); --currentLink){
		//getting the next link in the chain to update the current link's location
		nextLink = currentLink;
		--nextLink;
		// update x/y in accordance with the next link in the chain
		if(nextLink->x == nextX && nextLink->y == nextY)
			dead = true;
		currentLink->x = nextLink->x;
		currentLink->y = nextLink->y;
		// update sprite location based on the new x/y location of the link
		sprite = &currentLink->sprite;
		sprite->setX(currentLink->x * ((float)GAME_WIDTH/BOARD_WIDTH));
		sprite->setY(currentLink->y * ((float)GAME_HEIGHT/BOARD_HEIGHT));
	}
	}
	currentLink = links.begin();
	
	sprite = &currentLink->sprite;
	
	currentLink->x = nextX;
	currentLink->y = nextY;

	sprite->setX(nextX * ((float)GAME_WIDTH/BOARD_WIDTH));
	sprite->setY(nextY * ((float)GAME_HEIGHT/BOARD_HEIGHT));
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
	//links.begin()->sprite.draw();
	for(std::list<Link>::iterator currentLink = links.begin(); currentLink != links.end(); ++currentLink){
		currentLink->sprite.draw();
	}
}

void Snake::onLostDevice(){
	isInitialized();
	linkTexture.onLostDevice();
	headTexture.onLostDevice();
}

void Snake::onResetDevice(){
	isInitialized();
	linkTexture.onResetDevice();
	headTexture.onResetDevice();
}
inline void Snake::isInitialized(){
	if(!this->initialized)
		throw GameError::exception("Snake is not initialized");
}