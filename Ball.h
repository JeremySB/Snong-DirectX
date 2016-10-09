#pragma once

#include <chrono>
#include "textureManager.h"
#include "image.h"
#include "entity.h"


class Ball : public Entity
{
public:
	Ball(void);

	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);

	// update ball position using current velocity. call per frame
	void update(float frameTime);

	// send ball back to middle with random velocity
	void reset();


private:

	
};

