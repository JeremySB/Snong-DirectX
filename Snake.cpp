#include "Snake.h"



Snake::~Snake(){

}

void Snake::initialize(Graphics *graphics, int append){
	if(initialized)
		throw GameError::exception("Snake was already initialized");

	this->linkTexture.initialize(graphics,SNAKE_LINK_TEXTURE);
	this->headTexture.initialize(graphics, SNAKE_HEAD_TEXTURE);
	this->append = append;
	this->initialized = true;
	this->links.push_back(Link(graphics, &headTexture));
}
void Snake::wipe(){
	isInitialized();
	while(links.size() > SNAKE_HEAD_SIZE){
		links.pop_back();
	}
}

void Snake::move(){
	isInitialized();
	std::list<Link>::iterator currentLink;
	std::list<Link>::iterator nextLink;
	Image *sprite;
	if(append){
		// demo function showing how append would be used
		if(links.size() < SNAKE_HEAD_SIZE){
			links.push_back(Link(graphics, &headTexture));
			links.back().head = true;
		}
		else{
			links.push_back(Link(graphics, &linkTexture));
		}
		append--;
	}
	for(currentLink = links.end(); currentLink != (--links.begin()); --currentLink){
		//getting the next link in the chain to update the current link's location
		nextLink = currentLink;
		--nextLink;
		// update x/y in accordance with the next link in the chain
		currentLink->x = nextLink->x;
		currentLink->y = nextLink->y;
		// update sprite location based on the new x/y location of the link
		sprite = &currentLink->sprite;
		sprite->setX(currentLink->x * ((float)GAME_WIDTH/BOARD_WIDTH));
		sprite->setY(currentLink->y * ((float)GAME_HEIGHT/BOARD_HEIGHT));
	}

	int Xmovement = 0, Ymovement = 0;
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
	
	sprite = &currentLink->sprite;
	
	currentLink->x += Xmovement;
	currentLink->y += Ymovement;

	sprite->setX(currentLink->x * ((float)GAME_WIDTH/BOARD_WIDTH));
	sprite->setY(currentLink->y * ((float)GAME_HEIGHT/BOARD_HEIGHT));
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
void Snake::isInitialized(){
	if(!this->initialized)
		throw GameError::exception("Snake is not initialized");
}