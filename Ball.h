#pragma once

#include <chrono>
#include "textureManager.h"
#include "image.h"


class Ball
{
public:
	Ball(void);
	~Ball(void);

	// initialize Image object and position ball in center
	// takes Graphics pointer, x velocity, and y velocity
	bool initialize(Graphics* graphics);

	// update ball position using current velocity. call per frame
	void update(float frameTime);
	
	// draw the ball - just calls draw on the image
	void draw() { ballImage.draw(); }

	// send ball back to middle with random velocity
	void reset();

	void onLostDevice() { ballTexture.onLostDevice(); }
	void onResetDevice() { ballTexture.onResetDevice(); }

private:
	Image ballImage;
	TextureManager ballTexture;
	D3DXVECTOR2 velocity;

	
};

