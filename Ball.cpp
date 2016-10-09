#include "Ball.h"


Ball::Ball(void)
{

}


bool Ball::initialize(Graphics* g) {
	try {
		if(!ballTexture.initialize(g, BALL_IMAGE)) {
			GameError(gameErrorNS::FATAL_ERROR, "Ball texture initialization failed");
		}
		if(!ballImage.initialize(g, 27, 17, 1, &ballTexture)) {
			GameError(gameErrorNS::FATAL_ERROR, "Ball image initialization failed");
		}
		ballImage.setScale(1);
		reset();
	}
	catch(...) {
		return false;
	}
	return true;
}

void Ball::update(float frameTime) {
	// todo: add collision checks - probably with entity

	// top/bottom wall collision
	
	// top border
	if(ballImage.getY() <= BORDER_HORIZONTAL_WIDTH && velocity.y <= 0) {
		velocity.y *= -1;
	}

	// bottom border
	if(ballImage.getY() + ballImage.getHeight()*ballImage.getScale() >= GAME_HEIGHT - BORDER_HORIZONTAL_WIDTH 
		&& velocity.y >= 0) {
		velocity.y *= -1;
	}

	// left border
	if(ballImage.getX() <= BORDER_VERTICAL_WIDTH && velocity.x <= 0) {
		reset();
	}

	// right border
	if(ballImage.getX() + ballImage.getWidth()*ballImage.getScale() >= GAME_WIDTH - BORDER_VERTICAL_WIDTH 
		&& velocity.x >= 0) {
		reset();
	}

	ballImage.setX(ballImage.getX() + frameTime * velocity.x);
	ballImage.setY(ballImage.getY() + frameTime * velocity.y);
}

void Ball::reset() {
	ballImage.setX(GAME_WIDTH/2 - ballImage.getWidth() * ballImage.getScale() / 2);
	ballImage.setY(GAME_HEIGHT/2 - ballImage.getHeight() * ballImage.getScale() / 2);

	srand(time(NULL));

	velocity.x = BALL_STARTING_VEL_X * (rand() % 2 ? 1 : -1);
	velocity.y = BALL_STARTING_VEL_Y * (rand() % 2 ? 1 : -1);
}