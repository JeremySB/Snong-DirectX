#include "Snake.h"
#include <iostream>

Snake::Snake():initialized(false),linksUsed(0),dead(false),appendNum(SNAKE_HEAD_SIZE){
}

Snake::~Snake(){
}

void Snake::initialize(Graphics *graphics, int x, int y,  const char *headTexture, const char *linkTexture){
	// checks for initialization
	if(initialized)
		throw GameError::exception("Snake was already initialized");

	// makes sure we can make the textures
	if (!this->linkTexture.initialize(graphics, linkTexture))
		throw GameError::exception("SnakeLink texture could not be initialized");

	if (!this->headTexture.initialize(graphics, headTexture))
		throw GameError::exception("Snake Head texture could not be initialized");
	
	defaultX = x;
	defaultY = y;
	
	// initializes all of the links we will use 
	for ( int i = 0; i < SNAKE_MAX_LENGTH; i++){
		Image* sprite = &links[i].sprite;

		if(i < SNAKE_HEAD_SIZE && !sprite->initialize(graphics, headTexture.getWidth(),headTexture.getHeight(), 1, &headTexture))
			throw GameError::exception("Snake link not able to initialize");
		
		if(i >= SNAKE_HEAD_SIZE && !sprite->initialize(graphics, linkTexture.getWidth(),linkTexture.getHeight(), 1, &linkTexture))
			throw GameError::exception("Snake link not able to initialize");
		
		sprite->setScale( BOARD_CELL_HEIGHT / (float)(i < SNAKE_HEAD_SIZE ? headTexture : linkTexture).getHeight());
		updateLink(links[i], defaultX, defaultY);
	}
	
	links[linksUsed++].inUse = true;
	updateLink(links[linksUsed], defaultX, defaultY);
	appendNum--;

	this->initialized = true;
}

void Snake::updateLink(Link &input, int newX, int newY){
	input.x = newX;
	input.y = newY;
	input.sprite.setX(newX * BOARD_CELL_WIDTH);
	input.sprite.setY(newY * BOARD_CELL_HEIGHT);
}

void Snake::wipe(){
	isInitialized();
	for ( int i = 1; i < linksUsed; i++){
		links[i].inUse = false;
	}
	appendNum = SNAKE_HEAD_SIZE - 1;
	linksUsed = 1;
	//links[0].x = defaultX;
	//links[0].y = defaultY;
	//links[0].sprite.;
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
	
	nextX = Xmovement + links[0].x;
	nextY = Ymovement + links[0].y;
	
	if(nextX < 0 || nextX > BOARD_WIDTH || nextY < 0 || nextY > BOARD_HEIGHT)
		dead = true;

	for(int currentLink = linksUsed - 1; currentLink > 0; --currentLink){
		int xDirection = links[currentLink].x - links[currentLink-1].x;
		int yDirection = links[currentLink].y - links[currentLink-1].y;
		// update x/y in accordance with the next link in the chain
		if(links[currentLink - 1].x == nextX && links[currentLink - 1].y == nextY)
			dead = true;

		if(xDirection)
			links[currentLink].sprite.setDegrees(90 *-xDirection);
		else if(yDirection)
			links[currentLink].sprite.setDegrees(90 * (yDirection-1));

		updateLink(links[currentLink], links[currentLink-1].x, links[currentLink-1].y);
	}

	updateLink(links[0], nextX, nextY);
	links[0].sprite.setDegrees(degrees);
}

void Snake::append(UINT toAdd){
	appendNum += toAdd;
}

/*Snake::Link::Link(Graphics* graphics, TextureManager* texture, int ncols):x(0),y(0){

}*/

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
		links[i].sprite.draw();
	}
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

bool Snake::isDead() const{
	return dead;
}