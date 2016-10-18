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
	timeSincePointDisplayed = 0;
	spaceBarMessage = new TextDX();
	scoreText = new TextDX();
	victoryText = new TextDX();
	roundText = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
Snong::~Snong()
{
    releaseAll();           // call onLostDevice() for every graphics item
	SAFE_DELETE_ARRAY(P1Head);
	SAFE_DELETE_ARRAY(P2Head);
	SAFE_DELETE(spaceBarMessage);
	SAFE_DELETE(scoreText);
	SAFE_DELETE(victoryText);
	SAFE_DELETE(roundText);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Snong::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	Player1Score = 0;
	Player2Score = 0;

	gamePaused = true;
	firstRound = true;
	victoryScreen = false;
	
	Player1.initialize(this, BOARD_WIDTH/3, BOARD_HEIGHT/2, P1_SNAKE_HEAD_TEXTURE, P1_SNAKE_LINK_TEXTURE);
	Player2.initialize(this, (BOARD_WIDTH/3) * 2, BOARD_HEIGHT/2, P2_SNAKE_HEAD_TEXTURE, P2_SNAKE_LINK_TEXTURE);

	
	// background initializations
	if(!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE)) 
			GameError(gameErrorNS::FATAL_ERROR, "Background texture initialization failed");

	if(!backgroundImage.initialize(graphics, 0, 0, 1, &backgroundTexture))
			GameError(gameErrorNS::FATAL_ERROR, "Background image initialization failed");
	backgroundImage.setScale((float)GAME_WIDTH/(float)backgroundImage.getWidth() );//0.444444f);
	backgroundImage.setX(GAME_WIDTH/2-backgroundImage.getWidth()*backgroundImage.getScale()/2);//0);
	backgroundImage.setY(GAME_HEIGHT/2 - backgroundImage.getHeight() * backgroundImage.getScale()/2);//-backgroundImage.getWidth()*backgroundImage.getScale()/2);


	// border initializations
	if(!borderRedTexture.initialize(graphics, BORDER_RED_IMAGE)) 
			GameError(gameErrorNS::FATAL_ERROR, "Border texture initialization failed");

	if(!borderGreenTexture.initialize(graphics, BORDER_GREEN_IMAGE)) 
			GameError(gameErrorNS::FATAL_ERROR, "Border texture initialization failed");

	if(!borderImage1.initialize(graphics, BORDER_VERTICAL_WIDTH, GAME_HEIGHT, 0, &borderRedTexture))
			GameError(gameErrorNS::FATAL_ERROR, "Border image initialization failed");
    borderImage1.setScale(2);
	borderImage1.setX(0);
	borderImage1.setY(0);

	if(!borderImage2.initialize(graphics, BORDER_VERTICAL_WIDTH, GAME_HEIGHT, 0, &borderGreenTexture))
			GameError(gameErrorNS::FATAL_ERROR, "Border image initialization failed");
    borderImage2.setScale(3);
	borderImage2.setX(GAME_WIDTH - borderImage2.getWidth() * borderImage2.getScale());
	borderImage2.setY(0);

	// ball initializations
	if(!ballTexture.initialize(graphics, BALL_IMAGE)) 
			GameError(gameErrorNS::FATAL_ERROR, "Ball texture initialization failed");

	if(!ball.initialize(this, BALL_ANIMATION_WIDTH, BALL_ANIMATION_HEIGHT, BALL_ANIMATION_COLUMNS, &ballTexture))
			GameError(gameErrorNS::FATAL_ERROR, "Ball image initialization failed");

	Player1.setMovementDirection(P1_DEFAULT_DIRECTION);
	Player2.setMovementDirection(P2_DEFAULT_DIRECTION);
	
	P1Head = Player1.getEntities();
	P2Head = Player2.getEntities();
    
	audio->playCue("BGM");

	ball.setScale(BALL_SCALE);
	ball.setFrames(BALL_MOVEMENT_START, BALL_MOVEMENT_END);
	ball.setCurrentFrame(BALL_MOVEMENT_START);
	ball.setFrameDelay(BALL_ANIMATION_UPDATE_TIME);

	// text initializations

    if(spaceBarMessage->initialize(graphics, 30, true, false, "Copperplate Gothic Bold") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font (Copperplate Gothic Bold)"));

	if(scoreText->initialize(graphics, 20, true, false, "Copperplate Gothic Bold") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font (Copperplate Gothic Bold)"));

	if(victoryText->initialize(graphics, 60, true, false, "Copperplate Gothic Bold") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font (Copperplate Gothic Bold)"));

	if (roundText->initialize(graphics, 45, true, false, "Copperplate Gothic Bold") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font (Copperplate Gothic Bold)"));

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Snong::update()
{
#pragma region generalInput
	if(input->isKeyDown(VK_ESCAPE))
		exitGame();
    if (gamePaused) {
        if (input->isKeyDown(' ')){
            gamePaused = false;
			lastPoint = none;
			if (victoryScreen) {
				victoryScreen = false;
				//firstRound = true;
				Player1Score = 0;
				Player2Score = 0;
			}
			else {
				firstRound = false;
			}
        }
        return;
    }
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

#pragma region Movement
    ball.update(frameTime);
	if((timeSinceLastMove += frameTime) >= SNAKE_UPDATE_TIME){
		Player1.move();
		Player2.move();
		timeSinceLastMove = 0;
	}
#pragma endregion

#pragma region Death
	if(Player1.isDead() || Player2.isDead()){
		lastPoint = none;
		if(!(Player1.isDead() && Player2.isDead())) {
			if(Player1.isDead()) {
				Player2Score++;
				lastPoint = green;
			}
			else {
				Player1Score++;
				lastPoint = red;
			}

			// check for win
			if (Player1Score >= VICTORY_POINTS) {
				victoryScreen = true;
				winner = red;
			}
			else if (Player2Score >= VICTORY_POINTS) {
				winner = green;
				victoryScreen = true;
			}
		}
		
		Player1.wipe();
		Player2.wipe();
		ball.reset();
        Player1.setMovementDirection(P1_DEFAULT_DIRECTION);
        Player2.setMovementDirection(P2_DEFAULT_DIRECTION);
        gamePaused = true;
	}
#pragma endregion
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
{
	VECTOR2 collision;
    bool collided = false;
	
	// left border
	if(ball.getX() <= -ball.getScale()*ball.getWidth()/*BORDER_VERTICAL_WIDTH*/  && ball.getVelocity().x <= 0) {
		Player1.setDead(true);
        //collided = true;
		//ball.reset();
	}

	// right border
	if(ball.getX() /*+ ball.getWidth()*ball.getScale()*/ >= GAME_WIDTH - BORDER_VERTICAL_WIDTH && ball.getVelocity().x >= 0) {
		Player2.setDead(true);
        //collided = true;
		//ball.reset();
	}
    // top/bottom wall collision
    VECTOR2 oldVelocity = ball.getVelocity();
    // top border
    if (ball.getY() <= BORDER_HORIZONTAL_WIDTH && oldVelocity.y <= 0) {
        ball.setVelocity(VECTOR2(oldVelocity.x,oldVelocity.y *-1));
        collided = true;
    }

    // bottom border
    if (ball.getY() + ball.getHeight()*ball.getScale() >= GAME_HEIGHT - BORDER_HORIZONTAL_WIDTH
        && oldVelocity.y >= 0) {
        ball.setVelocity(VECTOR2(oldVelocity.x, oldVelocity.y *-1));
        collided = true;
    }


	for( int i = 0; i < SNAKE_HEAD_SIZE; i++){
		if(ball.collidesWith(*P1Head[i], collision)){
			ball.bounce(collision,*P1Head[i]);
			ball.setVelocity(ball.getVelocity() * BALL_SPEED_MODIFIER);
			Player1.append(1);
            collided = true;
			break;
		}
		if(ball.collidesWith(*P2Head[i],collision)){
			ball.bounce(collision, *P2Head[i]);
			ball.setVelocity(ball.getVelocity() * BALL_SPEED_MODIFIER);
			Player2.append(1);
            collided = true;
			break;
		}
	}
    if(collided){
        audio->stopCue("Hit Sound");
        audio->playCue("Hit Sound");
    }
    /*if(ball.getVelocity() < 50){
        ball.setVelocity(50);
    }*/
}

//=============================================================================
// Render game items
//=============================================================================
void Snong::render()
{
	graphics->spriteBegin();
	
	backgroundImage.draw();
	
	borderImage1.draw();
	borderImage2.draw();
	
	ball.draw();
	
	Player1.draw();
	Player2.draw();


	scoreText->setFontColor(graphicsNS::WHITE);
	scoreText->print(std::to_string(Player1Score) + "  |  " + std::to_string(Player2Score), 0, GAME_HEIGHT * 9/10);

	if(gamePaused){
		spaceBarMessage->setFontColor(graphicsNS::WHITE);
		if (victoryScreen) {
			if (winner == red) {
				victoryText->setFontColor(RED_COLOR);
				victoryText->print("Red Player Wins!", 0, GAME_HEIGHT / 5);
			}
			else if (winner == green) {
				victoryText->setFontColor(GREEN_COLOR);
				victoryText->print("Green Player Wins!", 0, GAME_HEIGHT / 5);
			}
			spaceBarMessage->print("Press space bar to restart", 0, GAME_HEIGHT / 3 * 2.07);
		}
		else if (firstRound) {
			spaceBarMessage->print("First player to " + std::to_string(VICTORY_POINTS) + " wins", 0, GAME_HEIGHT / 4.2);
			spaceBarMessage->print("Press space bar to begin", 0, GAME_HEIGHT / 3 * 2.07);
		}
		else {
			if (lastPoint == red) {
				roundText->setFontColor(RED_COLOR);
				roundText->print("Red Player Point", 0, GAME_HEIGHT / 4.2);
			}
			else if (lastPoint == green) {
				roundText->setFontColor(GREEN_COLOR);
				roundText->print("Green Player Point", 0, GAME_HEIGHT / 4.2);
			}
			else {
				roundText->setFontColor(graphicsNS::WHITE);
				roundText->print("Tie", 0, GAME_HEIGHT / 4.2);
			}
			spaceBarMessage->print("Press space bar to continue", 0, GAME_HEIGHT / 3 * 2.07);
		}
	}
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
	
	backgroundTexture.onLostDevice();
	
	borderRedTexture.onLostDevice();
	borderGreenTexture.onLostDevice();

	spaceBarMessage->onLostDevice();
	scoreText->onLostDevice();
	victoryText->onLostDevice();
	roundText->onLostDevice();

	Game::releaseAll();
    return;
}

//=============================================================================
// The graphics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Snong::resetAll()
{
	Player1.onResetDevice();
	Player2.onResetDevice();

	ballTexture.onResetDevice();
	backgroundTexture.onResetDevice();
	
	borderRedTexture.onResetDevice();
	borderGreenTexture.onResetDevice();
	
	scoreText->onResetDevice();
	spaceBarMessage->onResetDevice();
	victoryText->onResetDevice();
	roundText->onResetDevice();

	Game::resetAll();
    return;
}