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
};

// TODO struct flags.
// That how it should look like?

struct Flags
{

	bool onPlatform = true;
	bool notOnPlatform = false;
	bool fallDown = true;
	bool notFallDown = false;
	bool onGround = true;
	bool notOnGround = false;
};

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

struct Barrel
{
	SDL_Rect animation; //sets the look of barrels
	double lowerXCorner; //right corner !
	double lowerYCorner;
	int realSize[2] = { BARRELS_REAL_SIZE,BARRELS_REAL_SIZE }; //pixels size of barrel
	double speedX=BARRELS_BOWLING_SPEED;	
	double bowlingSpeed = BARRELS_BOWLING_SPEED;
	double fallingSpeed = BARRELS_FALLING_SPEED;
	bool fallDown = false;
	bool onPlatform = false;
	bool onGround = false;
};

struct GameInfo
{
	double t1, t2;
	double gameTime, deltaTime;
	bool quit;
	int err;
	char text[128];
};

struct Score
{
	int score = 10;
	int jumpOverBarrel = 500;
	int getTrophy = 1000;
	int endTheStage = 10000;
};

struct SDLConst
{
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* player, * barrel, * trophy;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
}SDL;

struct Color
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
};

struct Platform 
{
	double upperXCorner; 
	double upperYCorner;
	double length; 
	double width=PLATFORM_WIDTH; 
};

struct Ladder
{
	double upperXCorner; 
	double upperYCorner;
	double width = LADDER_WIDTH; 
	double height = LADDER_HEIGHT; 
};

struct Trophy
{
	SDL_Rect animation; //sets look of the trophy
	double lowerXCorner;
	double lowerYCorner;
	int realSize[2] = { TROPHIES_REAL_SIZE,TROPHIES_REAL_SIZE };
};