#ifndef _SNAKE_H
#define _SNAKE_H

#include "textureManager.h"
#include "image.h"
#include "entity.h"


// enum to store what direction we are moving
enum Direction {Up,Down,Left,Right};

class Snake {
public:
	// initializer with all of the variables we will need to generate a functioning snake class
	// Jeremy: sam, usually better to have this just be default (so Snake objects are constructored automatically) and do this in an initialize function like Image & TextureManager do
	Snake();
	~Snake();

	void initialize(Graphics* graphics, int x = 0, int y = 0, const char *headTexture = SNAKE_HEAD_TEXTURE, const char *linkTexture = SNAKE_LINK_TEXTURE);

	void wipe();	// will be made to reduce the snake to a size of 1 and set its append variable to SNAKE_HEAD_SIZE
	void move();	// updates the position of the snake
	void append(UINT toAdd);

	Direction getMovementDirection();
	void setMovementDirection(Direction newDir);

	void draw();

	Entity **getEntities();

	void setDead(bool state);
	bool isDead() const;

	void onLostDevice();
	void onResetDevice();

private:
	struct Link{
		Link():x(0),y(0),inUse(false){};
		//Image 
		Entity sprite;
		int x, y;
		bool inUse;
	};
	inline void isInitialized();
	void updateLink(Link &input, int newX, int newY);
	
	// Doubly Linked List<Link>
	Graphics* graphics;
	
	TextureManager linkTexture;
	TextureManager headTexture;
	
	Link links[SNAKE_MAX_LENGTH];
	Direction movementDir;
	unsigned int appendNum;
	unsigned int linksUsed;
	unsigned int defaultX,defaultY;
	bool initialized;
	bool dead;
};
                              
#endif