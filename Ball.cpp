#include "Ball.h"


Ball::Ball(void)
{

}


Ball::~Ball(void)
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
		ballImage.setX(GAME_WIDTH/2 - ballImage.getX() * ballImage.getScale() / 2);
		ballImage.setY(GAME_HEIGHT/2 - ballImage.getY() * ballImage.getScale() / 2);
	}
	catch(...) {
		return false;
	}
	return true;
}