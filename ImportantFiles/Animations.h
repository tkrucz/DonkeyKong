#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "ObjectsFunctions.h"
#include "PlayerFlags.h"


extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void initializePlayerAnimator(Stage* stage, Animator* animator);

void initializeBarrelsAnimator(Stage* stage, Animator* animator);

void checkPlayerAnimation(Stage* stage, Animator* animator);

void checkPlayerWalkingAnimation(Stage* stage, Animator* animator);

void playerAnimationWalkLeft(Stage* stage, Animator* animator);

void playerAnimationWalkRight(Stage* stage, Animator* animator);

void checkPlayerClimbingAnimation(Stage* stage, Animator* animator);

void playerAnimationClimbUp(Stage* stage, Animator* animator);

void playerAnimationClimbDown(Stage* stage, Animator* animator);

void checkPlayerJumpingAnimation(Stage* stage, Animator* animator);

void playerAnimationJumpLeft(Stage* stage, Animator* animator);

void playerAnimationJumpRight(Stage* stage, Animator* animator);

void checkPlayerStandingAnimation(Stage* stage, Animator* animator);

void playerAnimationStandLeft(Stage* stage, Animator* animator);

void playerAnimationStandRight(Stage* stage, Animator* animator);

void playerAnimations( Stage* stage, Animator* animator);

void chceckBarrelAnimation(Stage* stage, Animator* animator);

void barrelBowlingAnimation(Stage* stage, Animator* animator);

void barrelAnimations(Stage* stage, Animator* animator);

void checkAnimations(Stage* stage, Animator* animator);


void initializePlayerAnimator(Stage* stage, Animator* animator)
{
	animator->playerSpriteArray = { PLAYER_WIDTH * animator->actualPlayerAnimation[0] + MARIO_BMP_COLUMN_DISTANCE * animator->actualPlayerAnimation[0] ,
	PLAYER_HEIGHT * animator->actualPlayerAnimation[1] + MARIO_BMP_ROW_DISTANCE * animator->actualPlayerAnimation[1],	PLAYER_REAL_SIZE, PLAYER_REAL_SIZE };
}

void initializeBarrelsAnimator(Stage* stage, Animator* animator)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
		animator->barrelsSpriteArray = { BARRELS_WIDTH , BARRELS_REAL_SIZE * animator->actualBarrelsAnimation[1] ,
		stage->barrels[i].realSize[0], stage->barrels[i].realSize[1] };
}

void checkPlayerAnimation(Stage* stage, Animator* animator)
{	
	checkPlayerWalkingAnimation(stage, animator);
	checkPlayerClimbingAnimation(stage, animator);
	checkPlayerJumpingAnimation(stage, animator);
	stage->player.animation = animator->playerSpriteArray;
}

void checkPlayerWalkingAnimation(Stage* stage, Animator* animator)
{
	if (stage->player.walkLeft)
		playerAnimationWalkLeft(stage, animator);
	else if (stage->player.walkRight)
		playerAnimationWalkRight(stage, animator);
	else 
		checkPlayerStandingAnimation(stage, animator);
}

void playerAnimationWalkLeft(Stage* stage, Animator* animator)
{
	animator->changePlayerAnimation = true;
	animator->time.actualShowingTime += stage->gameInfo.deltaTime;
	animator->actualPlayerAnimation[0] = PLAYER_WALK_LEFT;
	animator->actualPlayerAnimation[1] = 0;
	animator->actualPlayerAnimation[0] += int(animator->time.actualShowingTime / animator->time.showingTime) % TWO;
}

void playerAnimationWalkRight(Stage* stage, Animator* animator)
{
	animator->changePlayerAnimation = true;
	animator->time.actualShowingTime += stage->gameInfo.deltaTime;
	animator->actualPlayerAnimation[0] = PLAYER_WALK_RIGHT;
	animator->actualPlayerAnimation[1] = 0;
	animator->actualPlayerAnimation[0] -= int(animator->time.actualShowingTime / animator->time.showingTime) % TWO;
}

void checkPlayerClimbingAnimation(Stage* stage, Animator* animator)
{
	if (stage->player.onLadder)
	{
		if (stage->player.climbUp)
			playerAnimationClimbUp(stage, animator);
		else if (stage->player.climbDown)
			playerAnimationClimbDown(stage, animator);
	}
}

void playerAnimationClimbUp(Stage* stage, Animator* animator)
{
	animator->changePlayerAnimation = true;
	animator->time.actualShowingTime += stage->gameInfo.deltaTime;
	animator->actualPlayerAnimation[0] = PLAYER_CLIMB_ONE;
	animator->actualPlayerAnimation[1] = ONE;
	animator->actualPlayerAnimation[0] += int(animator->time.actualShowingTime / animator->time.showingTime) % TWO;
}

void playerAnimationClimbDown(Stage* stage, Animator* animator)
{
	animator->changePlayerAnimation = true;
	animator->time.actualShowingTime += stage->gameInfo.deltaTime;
	animator->actualPlayerAnimation[0] = PLAYER_CLIMB_TWO;
	animator->actualPlayerAnimation[1] = ONE;
	animator->actualPlayerAnimation[0] -= int(animator->time.actualShowingTime / animator->time.showingTime) % TWO;
}

void checkPlayerJumpingAnimation(Stage* stage, Animator* animator)
{
	if ((stage->player.isJumping || stage->player.fallDown) && stage->player.walkLeft)
		playerAnimationJumpLeft(stage, animator);
	else if ((stage->player.isJumping || stage->player.fallDown) && stage->player.walkRight)
		playerAnimationJumpRight(stage, animator);
}

void playerAnimationJumpLeft(Stage* stage, Animator* animator)
{
	animator->changePlayerAnimation = true;
	animator->actualPlayerAnimation[0] = PLAYER_JUMP_LEFT;
	animator->actualPlayerAnimation[1] = 0;
}

void playerAnimationJumpRight(Stage* stage, Animator* animator)
{
	animator->changePlayerAnimation = true;
	animator->actualPlayerAnimation[0] = PLAYER_JUMP_RIGHT;
	animator->actualPlayerAnimation[1] = 0;
}

void checkPlayerStandingAnimation(Stage* stage, Animator* animator)
{
	if (animator->actualPlayerAnimation[0] == PLAYER_JUMP_LEFT ||
		animator->actualPlayerAnimation[0] == PLAYER_WALK_LEFT ||
		animator->actualPlayerAnimation[0] == PLAYER_STAND_LEFT)
		playerAnimationStandLeft(stage, animator);
	else if (animator->actualPlayerAnimation[0] == PLAYER_STAND_RIGHT ||
		animator->actualPlayerAnimation[0] == PLAYER_WALK_RIGHT ||
		animator->actualPlayerAnimation[0] == PLAYER_JUMP_RIGHT)
		playerAnimationStandRight(stage, animator);
	else
		playerAnimationStandRight(stage, animator);
}

void playerAnimationStandLeft(Stage* stage, Animator* animator)
{
	animator->changePlayerAnimation = true;
	animator->actualPlayerAnimation[0] = PLAYER_STAND_LEFT;
	animator->actualPlayerAnimation[1] = 0;
}

void playerAnimationStandRight(Stage* stage, Animator* animator)
{
	animator->changePlayerAnimation = true;
	animator->actualPlayerAnimation[0] = PLAYER_STAND_RIGHT;
	animator->actualPlayerAnimation[1] = 0;
}

void playerAnimations(Stage* stage, Animator* animator)
{
	checkPlayerAnimation(stage, animator);
	initializePlayerAnimator(stage, animator);
}

void chceckBarrelAnimation(Stage* stage, Animator* animator)
{
	barrelBowlingAnimation(stage, animator);
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
		stage->barrels[i].animation = animator->barrelsSpriteArray;
}

void barrelBowlingAnimation(Stage* stage, Animator* animator)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (stage->barrels[i].onPlatform)
		{
			animator->changeBarrelsAnimation = true;
			animator->time.actualShowingTime += stage->gameInfo.deltaTime;
			animator->actualBarrelsAnimation[0] = ONE;
			animator->actualBarrelsAnimation[1] = 0;
			animator->actualBarrelsAnimation[1] += int(animator->time.actualShowingTime / animator->time.showingTime) % TWO;
		}		
	}
}

void barrelAnimations(Stage* stage, Animator* animator)
{
	chceckBarrelAnimation(stage, animator);
	initializeBarrelsAnimator(stage, animator);
}

void checkAnimations(Stage* stage, Animator* animator)
{
	playerAnimations(stage, animator);
	barrelAnimations(stage, animator);
}