#pragma once
extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}
#include "Define.h"
#include "ObjectsDefine.h"

struct SDLConst
{
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* player, * barrel, * trophy, *lives;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

struct Color
{
	int platformColor;
	int black;
	int white;
	int pink; //for 1st stage platforms
	int indygo; //for 2nd stage platforms
	int lime; //for 3th stage platforms	
	int grey; //for ladders
};

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

struct Time
{
	double showingTime;
	double actualShowingTime = NULL;
};

struct ShowText
{
	bool isVisible = false;
	Time time = { SHOWING_TEXT_TIME };
};

struct Animator
{
	SDL_Rect playerSpriteArray;
	SDL_Rect barrelsSpriteArray;
	bool changePlayerAnimation;
	bool changeBarrelsAnimation;
	int actualPlayerAnimation[TWO];
	int actualBarrelsAnimation[TWO];
	Time time = { SHOWING_ANIMATION_TIME };
};

struct PlayerInfo
{
	int score;
	int lives;
};

struct GameInfo
{
	double t1, t2;
	double gameTime, deltaTime;
	bool quit;
	int err;
	char text[TEXT_TABLE_SIZE];
};

struct Menu
{
	char text[TEXT_TABLE_SIZE];
	char message[MESSAGE_TABLE_SIZE];
	int index = -1;
	bool showMenu = true;
	bool showBarrelMenu = false;
	bool showFinishMenu = false;
	bool defaultMessage = true;
	bool noneStage = false;
	bool stageChoose = false;
	bool wrongStage = false;
	bool nameEnter = false;
	bool nameConfirmed = false;
	bool scoreboard = false;
	bool loadStage = false;
};

struct Score
{
	int getTrophy = GET_TROPHY_POINTS;
	int endTheStage = END_THE_STAGE_POINTS;
	int deltaScore = NULL_POINTS;
};

struct Scoreboard
{
	char name[NAME_TABLE_SIZE];
	int score;
	int lives;
};

struct Player
{
	SDL_Rect animation; //sets the look of player
	Coordinates lowerCoordinates;
	Speed speed;	
	char text[TEXT_TABLE_SIZE];
	char name[NAME_TABLE_SIZE];
	int realSize[TWO] = { PLAYER_REAL_SIZE,PLAYER_REAL_SIZE }; //pixels size of Mario
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
};

struct Barrel
{
	Coordinates lowerRightCoordinates;
	SDL_Rect animation; //sets the look of barrels
	Speed speed = { BARRELS_BOWLING_SPEED,BARRELS_FALLING_SPEED };
	int realSize[TWO] = { BARRELS_REAL_SIZE,BARRELS_REAL_SIZE }; //pixels size of barrel
	bool fallDown = false;
	bool onPlatform = false;
	bool onGround = false;
	int barrelScore = JUMP_OVER_BARREL_POINTS;
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
	Coordinates lowerCoordinates;
	SDL_Rect animation; //sets look of the trophy
	int realSize[TWO] = { TROPHIES_REAL_SIZE,TROPHIES_REAL_SIZE };
};

struct Lives
{
	SDL_Rect animation; //sets look of the lives
	Coordinates lowerCoordinates;
	int realSize[TWO] = { LIVES_REAL_SIZE, LIVES_REAL_SIZE };
};

enum StageSpecifier
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4
};

struct Stage 
{
	bool canChangePage = false;
	int numberOfPlayersInFile = NULL;
	int page = NULL;
	int numberOfRowsInStageFile = NULL;
	int numberOfPlatformsInFile = NULL;
	int numberOfLaddersInFile = NULL;
	int numberOfBarrelsInFile = NULL;
	int numberOfTrohpiesInFile = NULL;
	StageSpecifier stageSpecifier;
	Menu menu;
	Scoreboard* scoreboard;
	Player player;
	Platform platforms[NUMBER_OF_PLATFORMS];
	Ladder ladders[NUMBER_OF_LADDERS];
	Barrel barrels[NUMBER_OF_BARRELS];
	Trophy trophies[NUMBER_OF_TROPHIES];
	Lives lives[PLAYER_DEFAULT_LIVES];
	PlayerInfo playerInfo;
	GameInfo gameInfo;
	Color platformColor;
};