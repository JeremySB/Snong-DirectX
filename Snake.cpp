#include "Snake.h"
#include <iostream>

Snake::Snake():initialized(false),linksUsed(0),dead(false),appendNum(SNAKE_HEAD_SIZE){
}

Snake::~Snake(){
}

void Snake::initialize(Graphics *graphics, int x, int y){
	// checks for initialization
	if(initialized)
		throw GameError::exception("Snake was already initialized");

	// makes sure we can make the textures
	if (!this->linkTexture.initialize(graphics,SNAKE_LINK_TEXTURE))
		throw GameError::exception("SnakeLink texture could not be initialized");
	if (!this->headTexture.initialize(graphics, SNAKE_HEAD_TEXTURE))
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
	
		sprite->setX(0);
		sprite->setY(0);
	}
	
	links[linksUsed++].inUse = true;
	links[linksUsed].sprite.setX(BOARD_CELL_WIDTH * defaultX);
	links[linksUsed].sprite.setY(BOARD_CELL_HEIGHT * defaultY);
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
	links[0].x = defaultX;
	links[0].y = defaultY;
	links[0].sprite.
	this->.,,,dead = false;
}

void Snake::move(){
	isInitialized();
	
	Image *sprite;
	int nextX = 0, nextY = 0;
	int Xmovement = 0, Ymovement = 0;
	// demo function showing how append would be 
	if(appendNum > 0){
		links[linksUsed++].inUse = true;
		appendNum--;
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
		links[currentLink].x = links[currentLink - 1].x;
		links[currentLink].y = links[currentLink - 1].y;
		// update sprite location based on the new x/y location of the link
		sprite = &links[currentLink].sprite;
		sprite->setX(links[currentLink].x * BOARD_CELL_WIDTH);
		sprite->setY(links[currentLink].y * BOARD_CELL_HEIGHT);
		if(xDirection)
			sprite->setDegrees(90 *-xDirection);
		else if(yDirection)
			sprite->setDegrees(90 * (yDirection-1));
	}
	
	sprite = &links[0].sprite;
	
	links[0].x = nextX;
	links[0].y = nextY;

	sprite->setX(nextX * BOARD_CELL_WIDTH);
	sprite->setY(nextY * BOARD_CELL_HEIGHT);
	int degrees=0;
	switch(movementDir){
	case(Right):
		degrees = 90;
		break;
	case(Left):
		degrees = 270;
		break;
	case(Up):
		degrees = 0;
		break;
	case(Down):
		degrees = 180;
		break;
	}
	sprite->setDegrees(degrees);
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

	for( int i = 0; i < linksUsed; ++i){
		if(!links[i].inUse)
			break;
		links[i].sprite.draw();
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

bool Snake::isDead() const{
	return dead;
}