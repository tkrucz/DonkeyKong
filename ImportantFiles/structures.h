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

struct Player
{
	SDL_Rect animation; //sets the look of player
	int lowerXCorner;
	int lowerYCorner;
	int realSize[2] = { PLAYER_ANIMATION_SIZE,PLAYER_ANIMATION_SIZE }; //pixels size of Mario
	double speedX;
	double speedY;
	double jumpingSpeedX;
	bool isJumping;
	bool onPlatform;
	bool onLadder;
	bool fallDown;	
}Mario;

struct Barrels
{
	SDL_Rect animation; //sets the look of barrels
	int upperXCorner;
	double upperYCorner; //must be double 
	int realSizep[2] = { BARRELS_ANIMATION_SIZE,BARRELS_ANIMATION_SIZE };
	double fallingSpeed=GRAVITY_SPEED;
}barrel;

struct GameInfo
{
	int t1, t2;
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
	int x; 
	int y;
	int l; 
	int w=PLATFORM_WIDTH; 
};

struct Ladder //Arguemnts: x,y (upper corners), w-width is const=LadderWidth, h-height is const=LadderHeight
{
	int x; 
	int y;
	int w = LADDER_WIDTH; 
	int h = LADDER_HEIGHT; 
};