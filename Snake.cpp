#include "Snake.h"



Snake::~Snake(){

}
void Snake::wipe(){
	
}

void Snake::move(){
	
	std::list<Link>::iterator currentLink;
	std::list<Link>::iterator nextLink;
	Image *sprite;
	if(append){
		// demo function showing how append would be used
		if(links.size() < SNAKE_HEAD_SIZE){
			links.push_back(Link(nullptr, headTexture->getWidth(), headTexture->getHeight(), headTexture));
			links.back().head = true;
		}
		else{
			links.push_back(Link(nullptr, linkTexture->getWidth(), linkTexture->getHeight(), linkTexture));
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
	return movementDir;
}

void Snake::setMovementDirection(Direction newDir){
	movementDir = newDir;
}