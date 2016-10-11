#ifndef _SNAKE_H
#define _SNAKE_H

#include "textureManager.h"
#include "image.h"


// enum to store what direction we are moving
enum Direction {Up,Down,Left,Right};

class Snake {
public:
	// initializer with all of the variables we will need to generate a functioning snake class
	// Jeremy: sam, usually better to have this just be default (so Snake objects are constructored automatically) and do this in an initialize function like Image & TextureManager do
	Snake();
	~Snake();

	void initialize(Graphics* graphics, int x = 0, int y = 0);

	void wipe();	// will be made to reduce the snake to a size of 1 and set its append variable to SNAKE_HEAD_SIZE
	void move();	// updates the position of the snake
	void append(UINT toAdd);

	Direction getMovementDirection();
	void setMovementDirection(Direction newDir);

	void draw();
	
	bool isDead() const;
	void onLostDevice();
	void onResetDevice();

private:
	inline void isInitialized();

	Direction movementDir;
	
	struct Link{
		//Link(Graphics* graphics, TextureManager* texture, int ncols = 1);
		Link():x(0),y(0),inUse(false){};
		Image sprite;
		int x, y;
		bool inUse;
	};
	void updateLink(Link &input, int newX, int newY);
	
	// Doubly Linked List<Link>
	Graphics* graphics;
	
	TextureManager linkTexture;
	TextureManager headTexture;
	
	//std::list<Link> links;
	Link links[SNAKE_MAX_LENGTH];
	unsigned int appendNum;
	unsigned int linksUsed;
	unsigned int defaultX,defaultY;
	bool initialized;
	bool dead;
};
                              
#endif