#ifndef _SNAKE_H
#define _SNAKE_H

#include "textureManager.h"
#include "image.h"
#include <list>

class Snake {
public:
	Snake();

private:
	enum Direction {Up,Down,Left,Right};
	struct Link{
	
		TextureManager sprite;
		int x,y;
		bool head;
	};
	// Doubly Linked List<Link>
	Image linkTexture;
	Image headTexture;
	Direction movementDirection;
	std::list<Link> links;
};
                              
#endif