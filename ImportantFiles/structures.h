#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "define.h"


struct Coordinates
{
	double x;
	double y;
};

struct Speed
{
	double speedX;
	double speedY;
};

struct PlayerInfo
{
	int score;
	int lives;
};

struct Player
{
	SDL_Rect animation; //sets the look of player
	Coordinates lowerCoordinates;
	Speed speed;	
	int realSize[2] = { PLAYER_REAL_SIZE,PLAYER_REAL_SIZE }; //pixels size of Mario
	bool isJumping = false;
	bool onPlatform = false;
	bool onLadder = false;
	bool fallDown = false;
	bool begLadder = false; //player at the beginning of ladder
	bool endLadder = false; //player at the end of ladder
	bool walkRight = false;
	bool walkLeft = false;
	bool climbUp = false;
	bool climbDown = false;
}Mario;

struct Barrel
{
	SDL_Rect animation; //sets the look of barrels
	Coordinates lowerRightCoordinates;
	Speed speed = { BARRELS_BOWLING_SPEED,BARRELS_FALLING_SPEED };
	int realSize[2] = { BARRELS_REAL_SIZE,BARRELS_REAL_SIZE }; //pixels size of barrel
	bool fallDown = false;
	bool onPlatform = false;
	bool onGround = false;
	int barrelScore = JUMP_OVER_BARREL_POINTS;
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
	int getTrophy = GET_TROPHY_POINTS;
	int endTheStage = END_THE_STAGE_POINTS;
};

struct SDLConst
{
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* player, * barrel, * trophy;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

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
	Coordinates upperCorner;
	double length; 
	double width=PLATFORM_WIDTH; 
};

struct Ladder
{
	Coordinates upperCorner;
	double width = LADDER_WIDTH; 
	double height = LADDER_HEIGHT; 
};

struct Trophy
{
	SDL_Rect animation; //sets look of the trophy
	Coordinates lowerCoordinates;
	int realSize[2] = { TROPHIES_REAL_SIZE,TROPHIES_REAL_SIZE };
};


// TODO
/*
// ODDZIELNY PLIK DLA STRUCT GAME (BEDZIE ZA DUZA), ROZDZIEL FUNCTIONS.H na mniejsze "podpliki"
// SPRAWDZ CZY WSZEDZIE JEST TIMEDELTA
struct Game {
	Stage stage1 {
		player = mario ....
	}
	Stage stage2 ...
}
struct Stage {
	Player player;
	Platform platforms;
	Ladder ladders;
};

// struct animator {
	SDL_Rect * spritesArray;
	int actualAnimation;
}
*/