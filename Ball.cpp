#include "Ball.h"


Ball::Ball(void)
{

}


Ball::~Ball(void)
{
}

bool Ball::initialize(Graphics* g, float xVel, float yVel) {
	try {
		if(!ballTexture.initialize(g, BALL_IMAGE)) {
			GameError(gameErrorNS::FATAL_ERROR, "Ball texture initialization failed");
		}
		if(!ballImage.initialize(g, 27, 17, 1, &ballTexture)) {
			GameError(gameErrorNS::FATAL_ERROR, "Ball image initialization failed");
		}
		ballImage.setScale(1);
		ballImage.setX(GAME_WIDTH/2 - ballImage.getWidth() * ballImage.getScale() / 2);
		ballImage.setY(GAME_HEIGHT/2 - ballImage.getHeight() * ballImage.getScale() / 2);

		velocity.x = xVel;
		velocity.y = yVel;
	}
	catch(...) {
		return false;
	}
	return true;
}

void Ball::update(float frameTime) {
	// todo: add collision checks - probably with entity
	ballImage.setX(ballImage.getX() + frameTime * velocity.x);
	ballImage.setY(ballImage.getY() + frameTime * velocity.y);
}