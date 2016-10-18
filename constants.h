// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
//const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  // photo source NASA/courtesy of nasaimages.org 
const char BALL_IMAGE[] = "pictures\\ball.png";  // photo source NASA/courtesy of nasaimages.org 
const char BACKGROUND_IMAGE[] = "pictures\\background2.png";
const char BORDER_RED_IMAGE[] = "pictures\\borderRed.png";
const char BORDER_GREEN_IMAGE[] = "pictures\\borderGreen.png";
const char POINT_RED[] = "pictures\\pointRed.png";
const char POINT_GREEN[] = "pictures\\pointGreen.png";

// window
const char CLASS_NAME[] = "Snong";
const char GAME_TITLE[] = "Snong: The Game";
//const char GAME_TITLE[] = "Snong";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
const UINT WIDTH_BETWEEN_ARENAS = GAME_WIDTH/4;//80;		// width of the "no man's land" between snake arenas

// game
const double PI = 3.14159265;
const float FRAME_RATE  = 60.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float POINT_DISPLAY_TIME = 1;

// Board constants
const UINT BOARD_WIDTH = GAME_WIDTH/10;
const UINT BOARD_HEIGHT = GAME_HEIGHT/10;
const UINT BORDER_HORIZONTAL_WIDTH = 5;
const UINT BORDER_VERTICAL_WIDTH = 5;
const FLOAT BOARD_CELL_WIDTH = (float) GAME_WIDTH / (float) BOARD_WIDTH;
const FLOAT BOARD_CELL_HEIGHT = (float) GAME_HEIGHT / (float) BOARD_HEIGHT;

// Snake constants
const UINT SNAKE_MAX_LENGTH = (BOARD_WIDTH * BOARD_HEIGHT) / 30;
const UINT SNAKE_HEAD_SIZE = SNAKE_MAX_LENGTH / 6;/// 8;//4;
const FLOAT SNAKE_MASS = 5;
const RECT SNAKE_LINK_RECT = {-BOARD_CELL_WIDTH/2, -BOARD_CELL_HEIGHT/2, BOARD_CELL_WIDTH/2, BOARD_CELL_HEIGHT/2};
const RECT SNAKE_LINK_RECT = {(LONG) -BOARD_CELL_WIDTH/2, (LONG) -BOARD_CELL_HEIGHT/2, (LONG) BOARD_CELL_WIDTH/2, (LONG)BOARD_CELL_HEIGHT/2};
const FLOAT SNAKE_LINK_RADIUS = sqrt(pow(BOARD_CELL_WIDTH/2,2)+pow(BOARD_CELL_HEIGHT/2,2));
const UINT SNAKE_LINK_MASS = 500;
const char SNAKE_LINK_TEXTURE[] = "pictures\\LinkTextureP1.png";
const char SNAKE_HEAD_TEXTURE[] = "pictures\\HeadTextureP1.png";

const char P1_SNAKE_LINK_TEXTURE[] = "pictures\\LinkTextureP1.png";
const char P1_SNAKE_HEAD_TEXTURE[] = "pictures\\HeadTextureP1.png";

const char P2_SNAKE_LINK_TEXTURE[] = "pictures\\LinkTextureP2.png";
const char P2_SNAKE_HEAD_TEXTURE[] = "pictures\\HeadTextureP2.png";
// Ball constants
const float BALL_STARTING_SPEED = 80;
const float BALL_STARTING_SPEED = 90;//80;
const float BALL_SCALE = 0.3f;
const FLOAT BALL_SPEED_MODIFIER = 1.2;
const FLOAT BALL_SPEED_MODIFIER = 1.2f;
// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave\ Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound\ Bank.xsb";

const UCHAR P1_UP = 'W';
const UCHAR P1_DOWN = 'S';
const UCHAR P1_RIGHT = 'D';
const UCHAR P1_LEFT = 'A';

const UCHAR P2_UP = VK_UP;//'I';
const UCHAR P2_DOWN = VK_DOWN;//'K';
const UCHAR P2_RIGHT = VK_RIGHT;//'L';
const UCHAR P2_LEFT = VK_LEFT;//'J';

#endif
