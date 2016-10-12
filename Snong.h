// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 4 spacewar.h v1.0

#ifndef _SNONG_H             // prevent multiple definitions if this 
#define _SNONG_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "Snake.h"
#include "Ball.h"

//=============================================================================
// Create game class
//=============================================================================
class Snong : public Game
{
private:
    // variables
	Snake Player1, Player2;
	Entity **P1Head;
	Entity **P2Head;
	UINT Player1Score, Player2Score;
	Ball ball; // ball entity
	TextureManager ballTexture;
	float timeSinceLastMove;

public:
    // Constructor
    Snong();

    // Destructor
    virtual ~Snong();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
