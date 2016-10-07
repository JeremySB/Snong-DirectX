#ifndef _SNAKE_H
#define _SNAKE_H

#include "textureManager.h"
#include "image.h"
#include <list>


// enum to store what direction we are moving
enum Direction {Up,Down,Left,Right};

class Snake {
public:
	// initializer with all of the variables we will need to generate a functioning snake class
	Snake(TextureManager *linkTexture, TextureManager *headTexture, int append = SNAKE_HEAD_SIZE):linkTexture(linkTexture),
		headTexture(headTexture),append(append){};
	~Snake();

	void wipe();	// will be made to reduce the snake to a size of 1 and set its append variable to SNAKE_HEAD_SIZE
	void move();	// updates the position of the snake

	Direction getMovementDirection();
	void setMovementDirection(Direction newDir);

private:
	Direction movementDir;
	struct Link{
		Link(Graphics* graphics,int width, int height, TextureManager* texture, int ncols = 1):head(false),x(0),y(0){
			if(!sprite.initialize(graphics,width,height,ncols,texture))
				throw GameError::exception("Snake link not able to initialize");
			sprite.setX(x * (GAME_WIDTH / BOARD_WIDTH));
			sprite.setY(y * (GAME_HEIGHT / BOARD_HEIGHT));
			sprite.setScale(((float)GAME_HEIGHT/(float)BOARD_HEIGHT)/(float)height);
		}
		Image sprite;
		int x,y;
		bool head;
	};
	
	// Doubly Linked List<Link>
	TextureManager* linkTexture;
	TextureManager* headTexture;
	std::list<Link> links;
	int append;
};
                              
#endif