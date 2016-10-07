#pragma once

#include "textureManager.h"
#include "image.h"

class Ball
{
public:
	Ball(void);
	~Ball(void);

	// initialize Image object and position ball in center
	// takes Graphics pointer, x velocity, and y velocity
	bool initialize(Graphics* graphics, float xVel, float yVel);

	// update ball position using current velocity. call per frame
	void update(float frameTime);
	
	// draw the ball - just calls draw on the image
	void draw() { ballImage.draw(); }

	void onLostDevice() { ballTexture.onLostDevice(); }
	void onResetDevice() { ballTexture.onResetDevice(); }

private:
	Image ballImage;
	TextureManager ballTexture;
	D3DXVECTOR2 velocity;
};

