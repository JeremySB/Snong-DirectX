#include "Ball.h"


Ball::Ball(void)
{

}

bool Ball::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	setScale(BALL_SCALE);
	speed = BALL_STARTING_SPEED;
	setCollisionRadius(getWidth()*getScale()/2);
	reset();
	activate();
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

}

void Ball::reset() {
	setX(GAME_WIDTH/2 - getWidth() * getScale() / 2);
	setY(GAME_HEIGHT/2 - getHeight() * getScale() / 2);

	srand(time(NULL));

	velocity.x = (rand() % 80 + 5)*(rand() % 2 ? 1 : -1);
	velocity.y = (rand() % 90 + 10)*(rand() % 2 ? 1 : -1);
	Graphics::Vector2Normalize(&velocity);
	velocity *= speed;
}