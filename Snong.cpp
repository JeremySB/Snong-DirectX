// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine Part 1
// Chapter 4 spacewar.cpp v1.0
// Spacewar is the class we create.

#include "Snong.h"

//=============================================================================
// Constructor
//=============================================================================
Snong::Snong():timeSinceLastMove(0){
	// todo: currently has error because players aren't constructed.
}

//=============================================================================
// Destructor
//=============================================================================
Snong::~Snong()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Snong::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	Player1.initialize(graphics);
	Player2.initialize(graphics);

	// ball initializations
	if(!ballTexture.initialize(graphics, BALL_IMAGE)) 
			GameError(gameErrorNS::FATAL_ERROR, "Ball texture initialization failed");

	if(!ball.initialize(this, 0, 0, 1, &ballTexture))
			GameError(gameErrorNS::FATAL_ERROR, "Ball image initialization failed");

	Player1.setMovementDirection(Right);
	Player2.setMovementDirection(Down);
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Snong::update()
{
	ball.update(frameTime);

#pragma region generalInput
	if(input->isKeyDown(VK_ESCAPE))
		exitGame();
#pragma endregion


#pragma region player1Input
	if(input->isKeyDown(P1_UP) && Player1.getMovementDirection() != Down)
		Player1.setMovementDirection(Up);
	else if(input->isKeyDown(P1_DOWN) && Player1.getMovementDirection() != Up)
		Player1.setMovementDirection(Down);
	else if(input->isKeyDown(P1_RIGHT) && Player1.getMovementDirection() != Left)
		Player1.setMovementDirection(Right);
	else if(input->isKeyDown(P1_LEFT) && Player1.getMovementDirection() != Right)
		Player1.setMovementDirection(Left);

#pragma endregion

#pragma region player2Input

	if(input->isKeyDown(P2_UP) && Player2.getMovementDirection() != Down)
		Player2.setMovementDirection(Up);
	else if(input->isKeyDown(P2_DOWN) && Player2.getMovementDirection() != Up)
		Player2.setMovementDirection(Down);
	else if(input->isKeyDown(P2_RIGHT) && Player2.getMovementDirection() != Left)
		Player2.setMovementDirection(Right);
	else if(input->isKeyDown(P2_LEFT) && Player2.getMovementDirection() != Right)
		Player2.setMovementDirection(Left);
#pragma endregion

if((timeSinceLastMove += frameTime) >= SNAKE_UPDATE_TIME){
	Player1.move();
	Player2.move();
	timeSinceLastMove = 0;
	Player1.append(2);
	if(Player1.isDead() && Player2.isDead()){
		Player1.wipe();
		Player2.wipe();
	}
	else if(Player1.isDead() || Player2.isDead()){
		(Player1.isDead() ? Player2Score : Player1Score)++;
		Player1.wipe();
		Player2.wipe();
	}
}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Snong::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Snong::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Snong::render()
{
	graphics->spriteBegin();
	ball.draw();
	Player1.draw();
	Player2.draw();
	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Snong::releaseAll()
{
	Player1.onLostDevice();
	Player2.onLostDevice();
    ballTexture.onLostDevice();
	Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Snong::resetAll()
{
	Player1.onResetDevice();
	Player2.onResetDevice();
    ballTexture.onResetDevice();
	Game::resetAll();
    return;
}
