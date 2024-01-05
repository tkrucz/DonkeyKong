#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "structures.h"
#include "define.h"
#include "ObjectsFunctions.h"


extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}


void initializePlayer();

void checkDirection(GameInfo* gameInfo);

void playerWalk(GameInfo* gameInfo); //move player in X axis by the current speedX

void playerClimb(GameInfo* gameInfo); //move player in Y axis by the current speedY

void approximateOnGround(GameInfo* gameInfo); //check if player is near the ground

void approximateOnPlatform(Platform* platforms); //check if player is near the platform, while falling down

void hitBottomOfThePlatform(Platform* platforms, GameInfo* gameInfo); //check if player hit the bottom of platform

void hitSidesOfThePlatform(Platform* platforms); //check if player hit the sides of platform

//check if player is jumping||falling down change his position by the current speedY, check if there is collision or if player should get points 
void gravityApply(GameInfo* gameInfo, Platform* platforms, Barrel* barrels);

void playerJump(); //give the speedY value -JumpingSpeed

void checkIfPlayerIsJumping();

void playerMovement(GameInfo* gameInfo);

void jumpOverBarrel(PlayerInfo* playerInfo, Score* score, Barrel* barrels);

void getTrophy(PlayerInfo* playerInfo, Score* score, Trophy* trophies);

void endTheStage(PlayerInfo* playerInfo, Score* score);

void addScore(PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies);

void loseLive(GameInfo* gameInfo, PlayerInfo* playerInfo);

void playerOnLadderBeg();

void playerNotOnLadderBeg();

void playerOnLadderEnd();

void playerNotOnLadderEnd();

void playerOnLadder();

void playerNotOnLadder();

void playerOnPlatform();

void playerNotOnPlatform();

void playerFallingDown();

void playerNotFallingDown();

void playerJumping();

void playerNotJumping();

void playerOnGround();

void playerWalkRight();

void playerNotWalkRight();

void playerWalkLeft();

void playerNotWalkLeft();

void playerNotWalking();

void playerClimbUp();

void playerNotClimbUp();

void playerClimbDown();

void playerNotClimbDown();

void playerNotClimbing();

void isPlayerOutsideTheBorders(); //check if player isn't outside of the screen borders

void isPlayerOnLadder(Ladder* ladders);

void isPlayerOnPlatform(Platform* platforms);

void isPlayerOnGround(); 

void whereIsPLayer(Platform* platforms, Ladder* ladders);

void quit(GameInfo* gameInfo);

void initializePlayer()
{
	Mario.lowerCoordinates = { PLAYER_SPAWN_POINT_X,PLAYER_SPAWN_POINT_Y };
	//TODO comments
	Mario.animation = { DEAFULT_PLAYER_SPRITE_I + MARIO_BMP_DISTANCE, DEAFULT_PLAYER_SPRITE_II ,Mario.realSize[0],Mario.realSize[1] };
	Mario.speed.speedX = NULL_SPEED;
	Mario.speed.speedY = NULL_SPEED;
	playerOnPlatform();
}

void checkDirection(GameInfo* gameInfo)
{
	if (Mario.walkLeft || Mario.walkRight)
	{
		Mario.speed.speedX = WALKING_SPEED;
		playerWalk(gameInfo);
	}
	if (Mario.climbUp || Mario.climbDown)
	{
		Mario.speed.speedY = CLIMBING_SPEED;
		playerClimb(gameInfo);
	}
}

void playerWalk(GameInfo* gameInfo)
{
	if(Mario.walkLeft)
		Mario.lowerCoordinates.x -= (Mario.speed.speedX * gameInfo->deltaTime);
	if (Mario.walkRight)
		Mario.lowerCoordinates.x += (Mario.speed.speedX * gameInfo->deltaTime);
}

void playerClimb(GameInfo* gameInfo)
{
	if (Mario.begLadder && Mario.climbDown)
		Mario.speed.speedY = NULL_SPEED;
	if (Mario.endLadder && Mario.climbUp)
		Mario.speed.speedY = NULL_SPEED;
	if (Mario.climbDown)
		Mario.lowerCoordinates.y += (Mario.speed.speedY * gameInfo->deltaTime);
	if (Mario.climbUp)
		Mario.lowerCoordinates.y -= (Mario.speed.speedY * gameInfo->deltaTime);
}

void approximateOnGround(GameInfo* gameInfo)
{
	if (Mario.lowerCoordinates.y + Mario.speed.speedY + (GRAVITY_SPEED * gameInfo->deltaTime) >= GROUND_HEIGHT)
	{
		Mario.lowerCoordinates.y = GROUND_HEIGHT;
		playerNotFallingDown();
		playerNotJumping();
	}
}

void approximateOnPlatform(Platform* platforms)
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (Mario.speed.speedY > 0 && Mario.lowerCoordinates.y > platforms[i].upperCorner.y &&
			Mario.lowerCoordinates.y < platforms[i].upperCorner.y + platforms[i].width &&
			Mario.lowerCoordinates.x<platforms[i].upperCorner.x + platforms[i].length &&
			Mario.lowerCoordinates.x + Mario.realSize[0]>platforms[i].upperCorner.x)
		{
			Mario.lowerCoordinates.y = platforms[i].upperCorner.y;
			Mario.speed.speedY = NULL_SPEED;
			playerNotFallingDown();
			playerNotJumping();
		}
	}
}

void hitBottomOfThePlatform(Platform* platforms, GameInfo* gameInfo) //check if player doesn't hit the bottom of the platform
{
	double upperYCorner = Mario.lowerCoordinates.y - Mario.realSize[1]; //"-" beacuse y increases in down direction
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (upperYCorner <= platforms[i].upperCorner.y + platforms[i].width &&
			upperYCorner > platforms[i].upperCorner.y)
			if (platforms[i].upperCorner.x <= Mario.lowerCoordinates.x + Mario.realSize[0] &&
				Mario.lowerCoordinates.x <= platforms[i].upperCorner.x + platforms[i].length)
			{
				double elasticColision = gameInfo->deltaTime * ELASTIC_COLISION_CONST * (Mario.speed.speedY + GRAVITY_SPEED * gameInfo->deltaTime);
				Mario.speed.speedY = elasticColision; //dodaæ elastic colision do sturktury skok kiedyœ?
			}
	}
}

void hitSidesOfThePlatform(Platform* platforms)
{
	double upperYCorner = Mario.lowerCoordinates.y - Mario.realSize[1];
	double LeftCorner = Mario.lowerCoordinates.x;
	double RightCorner = Mario.lowerCoordinates.x + Mario.realSize[0];
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (LeftCorner <= platforms[i].upperCorner.x + platforms[i].length && LeftCorner >= platforms[i].upperCorner.x + platforms[i].length - ONE)
			if (upperYCorner <= platforms[i].upperCorner.y + platforms[i].width && upperYCorner > platforms[i].upperCorner.y)
			{
				Mario.lowerCoordinates.x = platforms[i].upperCorner.x + platforms[i].length;
				return;
			}
		if (RightCorner >= platforms[i].upperCorner.x && RightCorner <= platforms[i].upperCorner.x + ONE)
			if (upperYCorner <= platforms[i].upperCorner.y + platforms[i].width && upperYCorner > platforms[i].upperCorner.y)
				Mario.lowerCoordinates.x = platforms[i].upperCorner.x - Mario.realSize[0];
	}
}

//TODO KONIECZNIE WSZYSTKIE STRUKTURY/ZMIENNE NIE MOGA BYC GLOBALNE !!!!!! ////////////////////////////////////////////////////////////////
void gravityApply(GameInfo* gameInfo, Platform* platforms, Barrel* barrels)
{
	if (Mario.isJumping || Mario.fallDown)
	{
		Mario.speed.speedY += (GRAVITY_SPEED * gameInfo->deltaTime);
		Mario.lowerCoordinates.y += Mario.speed.speedY;
		approximateOnGround(gameInfo);
		hitBottomOfThePlatform(platforms, gameInfo);
		hitSidesOfThePlatform(platforms);
		approximateOnPlatform(platforms);
	}
}

// TODO playerJumping to readKeys?
void playerJump()
{
	Mario.speed.speedY = -JUMPING_SPEED;
}

void checkIfPlayerIsJumping() //no "double" jump or inifinity jump
{
	if (Mario.isJumping == true)
		return;
	else
	{
		playerJumping();
		playerJump();
	}
}

void playerMovement(GameInfo* gameInfo)
{
	checkDirection(gameInfo);
	if (Mario.onPlatform || Mario.isJumping || Mario.fallDown)
		playerWalk(gameInfo);
	if (Mario.onLadder)
		playerClimb(gameInfo);
	if (Mario.begLadder || Mario.endLadder)
	{
		playerWalk(gameInfo);
		playerClimb(gameInfo);
	}
}

void jumpOverBarrel(PlayerInfo* playerInfo, Score* score, Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (Mario.isJumping || Mario.fallDown)
		{
			if (Mario.lowerCoordinates.y <= barrels[i].lowerRightCoordinates.y - BARRELS_DIFFERENCE_IN_Y &&
				barrels[i].lowerRightCoordinates.x >= Mario.lowerCoordinates.x &&
				barrels[i].lowerRightCoordinates.x + BARRELS_HITBOX_SIZE <= Mario.lowerCoordinates.x + Mario.realSize[0])
			{
				playerInfo->score += barrels[i].barrelScore;
				barrels[i].barrelScore = ZERO;
				break;
			}
		}
		barrels[i].barrelScore = JUMP_OVER_BARREL_POINTS;
	}
}

void getTrophy(PlayerInfo* playerInfo, Score* score, Trophy* trophies)
{
	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		if (Mario.lowerCoordinates.y == trophies[i].lowerCoordinates.y + TROPHIES_DIFFERENCE_IN_Y &&
			Mario.lowerCoordinates.x >= trophies[i].lowerCoordinates.x - trophies[i].realSize[0] &&
			Mario.lowerCoordinates.x <= trophies[i].lowerCoordinates.x + trophies[i].realSize[0])
		{
			playerInfo->score += score->getTrophy;
			trophies[i].lowerCoordinates.x = 590 + (i * 20);
			trophies[i].lowerCoordinates.y = AUTHOR_INFO_ROW + 4;
			return;
		}
	}
}

void endTheStage(PlayerInfo* playerInfo, Score* score)
{
	if (Mario.lowerCoordinates.y == PLATFORM_V_HEIGHT)
	{
		playerInfo->score += score->endTheStage;
		score->endTheStage = ZERO;
	}
}

void addScore(PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies)
{
	jumpOverBarrel(playerInfo, score, barrels);
	getTrophy(playerInfo, score, trophies);
	endTheStage(playerInfo, score);
}

void loseLive(GameInfo* gameInfo, PlayerInfo* playerInfo)
{
	playerInfo->lives -= 1;
	if (playerInfo->lives == ZERO)
		quit(gameInfo);
}

void playerOnLadderBeg()
{
	Mario.begLadder = true;
}

void playerNotOnLadderBeg()
{
	Mario.begLadder = false;
}

void playerOnLadderEnd()
{
	Mario.endLadder = true;
}

void playerNotOnLadderEnd()
{
	Mario.endLadder = false;
}

void playerOnLadder()
{
	Mario.onLadder = true;
}

void playerNotOnLadder()
{
	Mario.onLadder = false;
}

void playerOnPlatform()
{
	Mario.onPlatform = true;
}

void playerNotOnPlatform()
{
	Mario.onPlatform = false;
}

void playerFallingDown()
{
	Mario.fallDown = true;
}

void playerNotFallingDown()
{
	Mario.fallDown = false;
}

void playerJumping()
{
	Mario.isJumping = true;
}

void playerNotJumping()
{
	Mario.isJumping = false;
}

void playerOnGround()
{
	Mario.onPlatform = true;
}

void playerWalkRight()
{
	Mario.walkRight = true;
	playerNotWalkLeft();
}

void playerNotWalkRight()
{
	Mario.walkRight = false;
}

void playerWalkLeft()
{
	Mario.walkLeft = true;
	playerNotWalkRight();
}

void playerNotWalkLeft()
{
	Mario.walkLeft = false;
}

void playerNotWalking()
{
	Mario.walkLeft = false;
	Mario.walkRight = false;
}

void playerClimbUp()
{
	Mario.climbUp = true;
	playerNotClimbDown();
}

void playerNotClimbUp()
{
	Mario.climbUp = false;
}

void playerClimbDown()
{
	Mario.climbDown = true;
	playerNotClimbUp();
}

void playerNotClimbDown()
{
	Mario.climbDown = false;
}

void playerNotClimbing()
{
	Mario.climbDown = false;
	Mario.climbUp = false;
}

void isPlayerOutsideTheBorders()
{
	if (Mario.lowerCoordinates.x <= ZERO)
		Mario.lowerCoordinates.x = ZERO;
	if (Mario.lowerCoordinates.x + Mario.realSize[0] >= SCREEN_WIDTH)
		Mario.lowerCoordinates.x = SCREEN_WIDTH - Mario.realSize[0];
}

void isPlayerOnLadder(Ladder* ladders)
{
	int leftLowerCorner[2] = { Mario.lowerCoordinates.x, Mario.lowerCoordinates.y };
	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		if (ladders[i].upperCorner.x <= Mario.lowerCoordinates.x && Mario.lowerCoordinates.x <= ladders[i].upperCorner.x + ladders[i].width) //x increses in right direciton
		{
			//is Mario at the beginning of ladder?
			if (leftLowerCorner[1] == ladders[i].upperCorner.y + ladders[i].height) //y increases in down direction
			{
				playerOnLadderBeg();
				playerNotOnLadderEnd();
				playerOnLadder();
				return;
			}
			//is Mario at the end of ladder?
			else if (leftLowerCorner[1] == ladders[i].upperCorner.y)
			{
				playerOnLadderEnd();
				playerNotOnLadderBeg();
				playerOnLadder();
				return;
			}
			//is Mario in the "middle" of ladder?
			else if (ladders[i].upperCorner.y < leftLowerCorner[1] && leftLowerCorner[1] < ladders[i].upperCorner.y + ladders[i].height)
			{
				playerOnLadder();
				playerNotOnLadderEnd();
				playerNotOnLadderBeg();
				return;
			}
		}
	}
	playerNotOnLadderEnd();
	playerNotOnLadderBeg();
	playerNotOnLadder();
}

void isPlayerOnPlatform(Platform* platforms)
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		// is Mario on platform height?
		if (Mario.lowerCoordinates.y == platforms[i].upperCorner.y)
			// how far from edges?
			if (platforms[i].upperCorner.x <= Mario.lowerCoordinates.x + Mario.realSize[0] && Mario.lowerCoordinates.x <= platforms[i].upperCorner.x + platforms[i].length)
			{
				playerOnPlatform();
				return;
			}
	}
	playerNotOnPlatform();
}

void isPlayerOnGround()
{
	if (!Mario.onPlatform && !Mario.onLadder && Mario.lowerCoordinates.y != GROUND_HEIGHT)
		playerFallingDown();
	if (Mario.lowerCoordinates.y == GROUND_HEIGHT)
	{
		playerOnGround();
		playerNotFallingDown();
	}
}

void whereIsPLayer(Platform* platforms, Ladder* ladders)
{
	isPlayerOutsideTheBorders();
	isPlayerOnLadder(ladders);
	isPlayerOnPlatform(platforms);
	isPlayerOnGround();
}