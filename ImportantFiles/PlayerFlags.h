#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "PlayerFunctions.h"


extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void playerOnLadderBeg(Stage* stage);

void playerNotOnLadderBeg(Stage* stage);

void playerOnLadderEnd(Stage* stage);

void playerNotOnLadderEnd(Stage* stage);

void playerOnLadder(Stage* stage);

void playerNotOnLadder(Stage* stage);

void playerOnPlatform(Stage* stage);

void playerNotOnPlatform(Stage* stage);

void playerFallingDown(Stage* stage);

void playerNotFallingDown(Stage* stage);

void playerJumping(Stage* stage);

void playerNotJumping(Stage* stage);

void playerOnGround(Stage* stage);

void playerWalkRight(Stage* stage);

void playerNotWalkRight(Stage* stage);

void playerWalkLeft(Stage* stage);

void playerNotWalkLeft(Stage* stage);

void playerNotWalking(Stage* stage);

void playerClimbUp(Stage* stage);

void playerNotClimbUp(Stage* stage);

void playerClimbDown(Stage* stage);

void playerNotClimbDown(Stage* stage);

void playerNotClimbing(Stage* stage);


void playerOnLadderBeg(Stage* stage)
{
	stage->player.begLadder = true;
}

void playerNotOnLadderBeg(Stage* stage)
{
	stage->player.begLadder = false;
}

void playerOnLadderEnd(Stage* stage)
{
	stage->player.endLadder = true;
}

void playerNotOnLadderEnd(Stage* stage)
{
	stage->player.endLadder = false;
}

void playerOnLadder(Stage* stage)
{
	stage->player.onLadder = true;
}

void playerNotOnLadder(Stage* stage)
{
	stage->player.onLadder = false;
}

void playerOnPlatform(Stage* stage)
{
	stage->player.onPlatform = true;
}

void playerNotOnPlatform(Stage* stage)
{
	stage->player.onPlatform = false;
}

void playerFallingDown(Stage* stage)
{
	stage->player.fallDown = true;
}

void playerNotFallingDown(Stage* stage)
{
	stage->player.fallDown = false;
}

void playerJumping(Stage* stage)
{
	stage->player.isJumping = true;
}

void playerNotJumping(Stage* stage)
{
	stage->player.isJumping = false;
}

void playerOnGround(Stage* stage)
{
	stage->player.onPlatform = true;
}

void playerWalkRight(Stage* stage)
{
	stage->player.walkRight = true;
	playerNotWalkLeft(stage);
}

void playerNotWalkRight(Stage* stage)
{
	stage->player.walkRight = false;
}

void playerWalkLeft(Stage* stage)
{
	stage->player.walkLeft = true;
	playerNotWalkRight(stage);
}

void playerNotWalkLeft(Stage* stage)
{
	stage->player.walkLeft = false;
}

void playerNotWalking(Stage* stage)
{
	stage->player.walkLeft = false;
	stage->player.walkRight = false;
}

void playerClimbUp(Stage* stage)
{
	stage->player.climbUp = true;
}

void playerNotClimbUp(Stage* stage)
{
	stage->player.climbUp = false;
}

void playerClimbDown(Stage* stage)
{
	stage->player.climbDown = true;
}

void playerNotClimbDown(Stage* stage)
{
	stage->player.climbDown = false;
}

void playerNotClimbing(Stage* stage)
{
	stage->player.climbDown = false;
	stage->player.climbUp = false;
}