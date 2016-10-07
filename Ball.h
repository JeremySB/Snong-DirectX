#pragma once

#include "textureManager.h"
#include "image.h"

class Ball
{
public:
	Ball(void);
	~Ball(void);

	// initialize Image object and position ball in center
	bool initialize(Graphics*);

	// update ball position using current velocity. call per frame
	void updatePosition();
	
	// draw the ball - just calls draw on the image
	void draw() { ballImage.draw(); }

private:
	Image ballImage;
	TextureManager ballTexture;
	D3DXVECTOR2 velocity;
};

