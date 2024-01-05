#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "structures.h"
#include "define.h"
#include "PlayerFunctions.h"


extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

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