#include "Ball.h"


Ball::Ball(void)
{

}

bool Ball::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	bool result = Entity::initialize(gamePtr, width, height, ncols, textureM);
	setScale(BALL_SCALE);
	speed = BALL_STARTING_SPEED;
	setCollisionRadius(getWidth()*getScale()/2);
	reset();
	activate();
	return result;
}

void Ball::update(float frameTime) {
	Entity::update(frameTime);

	// check ball min/max speeds
	if (pow(velocity.x, 2) + pow(velocity.y, 2) < pow(BALL_MIN_SPEED, 2)) {
		Graphics::Vector2Normalize(&velocity);
		velocity *= BALL_MIN_SPEED;
	}
	else if (pow(velocity.x, 2) + pow(velocity.y, 2) > pow(BALL_MAX_SPEED, 2)) {
		Graphics::Vector2Normalize(&velocity);
		velocity *= BALL_MAX_SPEED;
	}

	setX(getX() + frameTime * velocity.x);
	setY(getY() + frameTime * velocity.y);
 
}

void Ball::reset() {
	setX(GAME_WIDTH/2 - getWidth() * getScale() / 2);
	setY(GAME_HEIGHT/2 - getHeight() * getScale() / 2);

	srand((UINT)time(NULL));

	velocity.x = (FLOAT) (rand() % 80 + 5)*(rand() % 2 ? 1 : -1);
	velocity.y = (FLOAT)(rand() % 90 + 10)*(rand() % 2 ? 1 : -1);
	Graphics::Vector2Normalize(&velocity);
	velocity *= speed;
}