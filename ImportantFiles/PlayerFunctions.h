#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "SDLFunctions.h"
#include "ObjectsFunctions.h"
#include "PlayerFlags.h"


extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void initializePlayer(Stage* stage); //set defaults "values" for player

void drawPlayer(Stage* stage, SDLConst* SDL);

void checkWalkDirection(Stage* stage);

void checkClimbDirection(Stage* stage);

void checkDirection(Stage* stage); //check WalkDirection + check ClimbDirection

void playerWalk(Stage* stage); //move player in X axis by the current speedX

void playerClimb(Stage* stage); //move player in Y axis by the current speedY

void approximateOnGround(Stage* stage); //check if player is near the ground

void approximateOnPlatform(Stage* stage); //check if player is near the platform, while falling down

void hitBottomOfThePlatform(Stage* stage); //check if player hit the bottom of the platform

void hitSidesOfThePlatform(Stage* stage); //check if player hit the sides of platform

//check if player is jumping||falling down, change his position by the current speedY
void gravityApply(Stage* stage);

void playerJump(Stage* stage); //give the speedY value -JumpingSpeed

void checkIfPlayerIsJumping(Stage* stage); //no "double" jump or inifinity jump

void playerMovement(Stage* stage);

void loseLive(Stage* stage, SDLConst* SDL);

void isPlayerOutsideTheBorders(Stage* stage); //check if player isn't outside of the screen borders

void isPlayerOnLadder(Stage* stage); //chceck if player is on ladder

void isPlayerOnPlatform(Stage* stage); //chceck if player is on platform

void isPlayerOnGround(Stage* stage); //chceck if player is on ground

void whereIsPLayer(Stage* stage);

void quit(Stage* stage, SDLConst* SDL);


void initializePlayer(Stage* stage)
{
	stage->player.lowerCoordinates = { PLAYER_SPAWN_POINT_X, PLAYER_SPAWN_POINT_Y };
	stage->player.speed.speedX = NULL_SPEED;
	stage->player.speed.speedY = NULL_SPEED;
}

void drawPlayer(Stage* stage,SDLConst* SDL)
{
	DrawSurface(SDL->screen, SDL->player, stage->player.lowerCoordinates.x + PLAYER_DIFFERENCE_IN_X, stage->player.lowerCoordinates.y + PLAYER_DIFFERENCE_IN_Y, &stage->player.animation);
}

void checkWalkDirection(Stage* stage)
{
	if (stage->player.walkLeft || stage->player.walkRight)
	{
		stage->player.speed.speedX = WALKING_SPEED;
		playerWalk(stage);
	}
}

void checkClimbDirection(Stage* stage)
{
	if (stage->player.climbUp || stage->player.climbDown)
	{
		stage->player.speed.speedY = CLIMBING_SPEED;
		playerClimb(stage);
	}
}

void checkDirection(Stage* stage)
{
	checkWalkDirection(stage);
	checkClimbDirection(stage);
}

void playerWalk(Stage* stage)
{
	if(stage->player.walkLeft)
		stage->player.lowerCoordinates.x -= (stage->player.speed.speedX * stage->gameInfo.deltaTime);
	if (stage->player.walkRight)
		stage->player.lowerCoordinates.x += (stage->player.speed.speedX * stage->gameInfo.deltaTime);
}

void playerClimb(Stage* stage)
{
	if (stage->player.begLadder && stage->player.climbDown)
		stage->player.speed.speedY = NULL_SPEED;
	if (stage->player.endLadder && stage->player.climbUp)
		stage->player.speed.speedY = NULL_SPEED;
	if (stage->player.climbDown)
		stage->player.lowerCoordinates.y += (stage->player.speed.speedY * stage->gameInfo.deltaTime);
	if (stage->player.climbUp)
		stage->player.lowerCoordinates.y -= (stage->player.speed.speedY * stage->gameInfo.deltaTime);
}

void approximateOnGround(Stage* stage)
{
	if (stage->player.lowerCoordinates.y + stage->player.speed.speedY + (GRAVITY_SPEED * stage->gameInfo.deltaTime) >= GROUND_HEIGHT)
	{
		stage->player.lowerCoordinates.y = GROUND_HEIGHT;
		playerNotFallingDown(stage);
		playerNotJumping(stage);
	}
}

void approximateOnPlatform(Stage* stage)
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (stage->player.speed.speedY > 0 && stage->player.lowerCoordinates.y > stage->platforms[i].upperCorner.y &&
			stage->player.lowerCoordinates.y < stage->platforms[i].upperCorner.y + stage->platforms[i].width &&
			stage->player.lowerCoordinates.x<stage->platforms[i].upperCorner.x + stage->platforms[i].length &&
			stage->player.lowerCoordinates.x + stage->player.realSize[0]>stage->platforms[i].upperCorner.x)
		{
			stage->player.lowerCoordinates.y = stage->platforms[i].upperCorner.y;
			stage->player.speed.speedY = NULL_SPEED;
			playerNotFallingDown(stage);
			playerNotJumping(stage);
		}
	}
}

void hitBottomOfThePlatform(Stage* stage) 
{
	double upperYCorner = stage->player.lowerCoordinates.y - stage->player.realSize[1]; //"-" beacuse y increases in down direction
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (upperYCorner <= stage->platforms[i].upperCorner.y + stage->platforms[i].width &&
			upperYCorner > stage->platforms[i].upperCorner.y)
			if (stage->platforms[i].upperCorner.x <= stage->player.lowerCoordinates.x + stage->player.realSize[0] &&
				stage->player.lowerCoordinates.x <= stage->platforms[i].upperCorner.x + stage->platforms[i].length)
			{
				double elasticColision = stage->gameInfo.deltaTime * ELASTIC_COLISION_CONST * (stage->player.speed.speedY + GRAVITY_SPEED * stage->gameInfo.deltaTime);
				stage->player.speed.speedY = elasticColision;
			}
	}
}

void hitSidesOfThePlatform(Stage* stage)
{
	double upperYCorner = stage->player.lowerCoordinates.y - stage->player.realSize[1];
	double LeftCorner = stage->player.lowerCoordinates.x;
	double RightCorner = stage->player.lowerCoordinates.x + stage->player.realSize[0];
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (LeftCorner <= stage->platforms[i].upperCorner.x + stage->platforms[i].length &&
			LeftCorner >= stage->platforms[i].upperCorner.x + stage->platforms[i].length - ONE)
			if (upperYCorner <= stage->platforms[i].upperCorner.y + stage->platforms[i].width &&
				upperYCorner > stage->platforms[i].upperCorner.y)
			{
				stage->player.lowerCoordinates.x = stage->platforms[i].upperCorner.x + stage->platforms[i].length;
				return;
			}
		if (RightCorner >= stage->platforms[i].upperCorner.x &&
			RightCorner <= stage->platforms[i].upperCorner.x + ONE)
			if (upperYCorner <= stage->platforms[i].upperCorner.y + stage->platforms[i].width &&
				upperYCorner > stage->platforms[i].upperCorner.y)
				stage->player.lowerCoordinates.x = stage->platforms[i].upperCorner.x - stage->player.realSize[0];
	}
}

void gravityApply(Stage* stage)
{
	if (stage->player.isJumping || stage->player.fallDown)
	{
		stage->player.speed.speedY += (GRAVITY_SPEED * stage->gameInfo.deltaTime);
		stage->player.lowerCoordinates.y += stage->player.speed.speedY;
		approximateOnGround(stage);
		hitBottomOfThePlatform(stage);
		hitSidesOfThePlatform(stage);
		approximateOnPlatform(stage);
	}
}

void playerJump(Stage* stage)
{
	stage->player.speed.speedY = -JUMPING_SPEED;
}

void checkIfPlayerIsJumping(Stage* stage)
{
	if (stage->player.isJumping == true)
		return;
	else
	{
		playerJumping(stage);
		playerJump(stage);
	}
}

void playerMovement(Stage* stage)
{
	if (stage->player.onPlatform || stage->player.isJumping || stage->player.fallDown)
	{
		checkWalkDirection(stage);
		playerWalk(stage);		
	}
	if (stage->player.onLadder)
	{
		checkDirection(stage); //if checkClimbDirection(), you can only climb on ladder, no moving in X axis
		playerClimb(stage);
	}
	if (stage->player.begLadder || stage->player.endLadder)
	{
		checkDirection(stage);
		playerWalk(stage);
		playerClimb(stage);
	}
}

void loseLive(Stage* stage, SDLConst* SDL)
{
	int pom;
	stage->playerInfo.lives -= 1;
	pom = stage->playerInfo.lives;
	stage->lives[pom].animation = { 0,0,0,0 };
	if (stage->playerInfo.lives == 0)
	{
		initializePlayer(stage);
		stage->menu.showMenu = true;
	}
}

void isPlayerOutsideTheBorders(Stage* stage)
{
	if (stage->player.lowerCoordinates.x <= 0)
		stage->player.lowerCoordinates.x = 0;
	if (stage->player.lowerCoordinates.x + stage->player.realSize[0] >= SCREEN_WIDTH)
		stage->player.lowerCoordinates.x = SCREEN_WIDTH - stage->player.realSize[0];
}

void isPlayerOnLadder(Stage* stage)
{
	int leftLowerCorner[2] = { stage->player.lowerCoordinates.x, stage->player.lowerCoordinates.y };
	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		if (stage->ladders[i].upperCorner.x <= stage->player.lowerCoordinates.x &&
			stage->player.lowerCoordinates.x <= stage->ladders[i].upperCorner.x + stage->ladders[i].width) //x increses in right direciton
		{
			//is Mario at the beginning of ladder?
			if (leftLowerCorner[1] == stage->ladders[i].upperCorner.y + stage->ladders[i].height) //y increases in down direction
			{
				playerOnLadderBeg(stage);
				playerNotOnLadderEnd(stage);
				playerOnLadder(stage);
				return;
			}
			//is Mario at the end of ladder?
			else if (leftLowerCorner[1] == stage->ladders[i].upperCorner.y)
			{
				playerOnLadderEnd(stage);
				playerNotOnLadderBeg(stage);
				playerOnLadder(stage);
				return;
			}
			//is Mario in the "middle" of ladder?
			else if (stage->ladders[i].upperCorner.y < leftLowerCorner[1] && leftLowerCorner[1] < stage->ladders[i].upperCorner.y + stage->ladders[i].height)
			{
				playerOnLadder(stage);
				playerNotOnLadderEnd(stage);
				playerNotOnLadderBeg(stage);
				return;
			}
		}
	}
	playerNotOnLadderEnd(stage);
	playerNotOnLadderBeg(stage);
	playerNotOnLadder(stage);
}

void isPlayerOnPlatform(Stage* stage)
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		// is Mario on platform height?
		if (stage->player.lowerCoordinates.y == stage->platforms[i].upperCorner.y)
			// how far from edges?
			if (stage->platforms[i].upperCorner.x <= stage->player.lowerCoordinates.x + stage->player.realSize[0] &&
				stage->player.lowerCoordinates.x <= stage->platforms[i].upperCorner.x + stage->platforms[i].length)
			{
				playerOnPlatform(stage);
				return;
			}
	}
	playerNotOnPlatform(stage);
}

void isPlayerOnGround(Stage* stage)
{
	if (!stage->player.onPlatform && !stage->player.onLadder &&
		stage->player.lowerCoordinates.y != GROUND_HEIGHT)
		playerFallingDown(stage);
	if (stage->player.lowerCoordinates.y == GROUND_HEIGHT)
	{
		playerOnGround(stage);
		playerNotFallingDown(stage);
	}
}

void whereIsPLayer(Stage* stage)
{
	isPlayerOutsideTheBorders(stage);
	isPlayerOnLadder(stage);
	isPlayerOnPlatform(stage);
	isPlayerOnGround(stage);
}