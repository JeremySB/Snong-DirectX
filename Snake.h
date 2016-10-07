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
	// Jeremy: sam, usually better to have this just be default (so Snake objects are constructored automatically) and do this in an initialize function like Image & TextureManager do
	Snake():initialized(false){};
	~Snake();
	void initialize(Graphics* graphics, int append = SNAKE_HEAD_SIZE);

	void wipe();	// will be made to reduce the snake to a size of 1 and set its append variable to SNAKE_HEAD_SIZE
	void move();	// updates the position of the snake

	Direction getMovementDirection();
	void setMovementDirection(Direction newDir);

	void draw();
	void onLostDevice();
	void onResetDevice();

private:
	void isInitialized();
	Direction movementDir;
	struct Link{
		Link(Graphics* graphics, TextureManager* texture, int ncols = 1):head(false),x(0),y(0){
			if(!sprite.initialize(graphics, texture->getWidth(),texture->getHeight(),ncols,texture))
				throw GameError::exception("Snake link not able to initialize");
			sprite.setX(x * (GAME_WIDTH / BOARD_WIDTH));
			sprite.setY(y * (GAME_HEIGHT / BOARD_HEIGHT));
			sprite.setScale(((float)GAME_HEIGHT/(float)BOARD_HEIGHT)/(float)texture->getHeight());
		}
		Image sprite;
		int x,y;
		bool head;
	};
	
	// Doubly Linked List<Link>
	Graphics* graphics;
	TextureManager linkTexture;
	TextureManager headTexture;
	std::list<Link> links;
	int append;
	bool initialized;
};
                              
#endif