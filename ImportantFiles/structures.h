#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "define.h"

struct PlayerInfo
{
	int score;
	int lives;	
}playerInfo;

// TODO struct flags, maybe barrel will require flags?
struct Player
{
	SDL_Rect animation; //sets the look of player
	double lowerXCorner;
	double lowerYCorner;
	int realSize[2] = { PLAYER_REAL_SIZE,PLAYER_REAL_SIZE }; //pixels size of Mario
	double speedX;
	double speedY;
	bool isJumping = false;
	bool onPlatform = false;
	bool onLadder = false;
	bool fallDown = false;
	bool begLadder = false; //player at the beginning of ladder
	bool endLadder = false; //player at the end of ladder
}Mario;

struct Barrels
{
	SDL_Rect animation; //sets the look of barrels
	int lowerXCorner;
	double lowerYCorner; //must be double 
	int realSize[2] = { BARRELS_REAL_SIZE,BARRELS_REAL_SIZE };
	double fallingSpeed = GRAVITY_SPEED * 5;
}barrel;

struct GameInfo
{
	double t1, t2;
	double gameTime, deltaTime;
	bool quit;
	int err;
	char text[128];
}gameInfo;

struct Score
{
	int jumpOverBarrel = 500;
	int getTrophy = 1000;
	int endTheStage = 10000;
}score;

struct SDLConst
{
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* player, * barrels;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
}SDL;

struct Colors
{
	int black;
	int white;
	int green;
	int red;
	int blue;
	int pink; //for 1st stage platforms
	int indygo; //for 2nd stage platforms
	int lime; //for 3th stage platforms	
	int grey; //for ladders
}colors;

struct Platform //Arguemnts: x,y (upper corners), l-length, w-width is const=PlatformWidth
{
	double x; 
	double y;
	double l; 
	double w=PLATFORM_WIDTH; 
};

struct Ladder //Arguemnts: x,y (upper corners), w-width is const=LadderWidth, h-height is const=LadderHeight
{
	double x; 
	double y;
	double w = LADDER_WIDTH; 
	double h = LADDER_HEIGHT; 
};
