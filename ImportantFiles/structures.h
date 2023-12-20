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
	SDL_Rect size; 
	int upperXCorner;
	int upperYCorner;
	int realSize[2] = { 16,16 };
	double speedX;
	double speedY;
	bool isJumping;
	bool onPlatform;
	bool onLadder;
	bool fallDown;
}Mario;

struct GameInfo
{
	int t1, t2;
	double gameTime, deltaTime;
	//TODO quit bool
	int quit;
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
	SDL_Surface* player;
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

struct Jumping
{
	double g = GravitySpeed;
	double velocity = JumpingSpeed;
	double beginning, duration; // beginning of jump, time duration of jump
}jumping;

struct Platform //Arguemnts: x,y (upper corners), l-length, w-width is const=PlatformWidth
{
	int x; 
	int y;
	int l; 
	int w=PlatformWidth; 
};

struct Ladder //Arguemnts: x,y (upper corners), w-width is const=LadderWidth, h-height is const=LadderHeight
{
	int x; 
	int y;
	int w = LadderWidth; 
	int h = LadderHeight; 
};