#include "Ball.h"


Ball::Ball(void)
{

}

bool Ball::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	setScale(BALL_SCALE);
	velocity.x = BALL_STARTING_VEL_X;
	velocity.y = BALL_STARTING_VEL_Y;
	reset();
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

void Ball::update(float frameTime) {
	Entity::update(frameTime);

	setX(getX() + frameTime * velocity.x);
	setY(getY() + frameTime * velocity.y);
 

	// top/bottom wall collision
	
	// top border
	if(getY() <= BORDER_HORIZONTAL_WIDTH && velocity.y <= 0) {
		velocity.y *= -1;
	}

	// bottom border
	if(getY() + getHeight()*getScale() >= GAME_HEIGHT - BORDER_HORIZONTAL_WIDTH 
		&& velocity.y >= 0) {
		velocity.y *= -1;
	}

	// left border
	if(getX() <= BORDER_VERTICAL_WIDTH && velocity.x <= 0) {
		reset();
	}

	// right border
	if(getX() + getWidth()*getScale() >= GAME_WIDTH - BORDER_VERTICAL_WIDTH && velocity.x >= 0) {
		reset();
	}
}

void Ball::reset() {
	setX(GAME_WIDTH/2 - getWidth() * getScale() / 2);
	setY(GAME_HEIGHT/2 - getHeight() * getScale() / 2);

	srand(time(NULL));

	velocity.x = BALL_STARTING_VEL_X * (rand() % 2 ? 1 : -1);
	velocity.y = BALL_STARTING_VEL_Y * (rand() % 2 ? 1 : -1);
}