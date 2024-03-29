#ifndef _SNAKE_H
#define _SNAKE_H

#include "textureManager.h"
#include "image.h"
#include "entity.h"
#include "game.h"




class Snake {
public:
	// initializer with all of the variables we will need to generate a functioning snake class
	Snake();
	~Snake();

//	void initialize(Graphics* graphics, int x = 0, int y = 0, const char *headTexture = SNAKE_HEAD_TEXTURE, const char *linkTexture = SNAKE_LINK_TEXTURE);
	void initialize(Game* game, int x = 0, int y = 0, const char *headTexture = SNAKE_HEAD_TEXTURE, const char *linkTexture = SNAKE_LINK_TEXTURE);
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

	struct Link: public Entity{
		Link();
		//Image 
		//Entity sprite;
		int boardX, boardY;
		//bool inUse;
	};
	Link links[SNAKE_MAX_LENGTH];
private:
	inline void isInitialized();
	void updateLink(Link &input, int newX, int newY);
	
	// Doubly Linked List<Link>
	//Graphics* graphics;
	
	TextureManager linkTexture;
	TextureManager headTexture;
	
	Direction movementDir;
	unsigned int appendNum;
	unsigned int linksUsed;
	unsigned int defaultX,defaultY;
	bool initialized;
	bool dead;
};
                              
#endif