#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "define.h"
#include "structures.h"
#include "GameStructure.h"
#include "ObjectsFunctions.h"
#include "PlayerFlags.h"


extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void initializeAnimator(Stage* stage, Animator* animator);

void checkPlayerAnimation(Stage* stage, Animator* animator);

void checkPlayerWalkingAnimation(Stage* stage, Animator* animator);

void checkPlayerClimbingAnimation(Stage* stage, Animator* animator);

void checkPlayerJumpingAnimation(Stage* stage, Animator* animator);

void checkPlayerStandingAnimation(Stage* stage, Animator* animator);

void playerAnimations(SDLConst* SDL, Stage* stage, Animator* animator);

void chceckBarrelAnimation(Stage* stage, Animator* animator);

void barrelAnimations(Stage* stage, Animator* animator);

void checkAnimaitons(Stage* stage, Animator* animator);

void initializeAnimator(Stage* stage, Animator* animator)
{
	animator->spriteArray = { PLAYER_WIDTH * animator->actualAnimation[0] + MARIO_BMP_COLUMN_DISTANCE * animator->actualAnimation[0] ,
		PLAYER_HEIGHT * animator->actualAnimation[1] + MARIO_BMP_ROW_DISTANCE * animator->actualAnimation[1],	PLAYER_REAL_SIZE, PLAYER_REAL_SIZE};
 // animator->spriteArray = { DEAFULT_PLAYER_SPRITE_I + MARIO_BMP_DISTANCE, DEAFULT_PLAYER_SPRITE_II, stage->player.realSize[0], stage->player.realSize[1] };
}

void checkPlayerAnimation(Stage* stage, Animator* animator)
{
	checkPlayerWalkingAnimation(stage, animator);
	checkPlayerClimbingAnimation(stage, animator);
	checkPlayerJumpingAnimation(stage, animator);
	stage->player.animation = animator->spriteArray;
}

void checkPlayerWalkingAnimation(Stage* stage, Animator* animator)
{
	if (stage->player.walkLeft)
	{
		animator->changeAnimation = true;
		animator->time.actualShowingTime += stage->gameInfo.deltaTime;
		animator->actualAnimation[0] = 2;
		animator->actualAnimation[1] = 0;
		animator->actualAnimation[0] += int(animator->time.actualShowingTime / animator->time.showingTime) % 2;
	}	
	else if (stage->player.walkRight)
	{
		animator->changeAnimation = true;
		animator->time.actualShowingTime += stage->gameInfo.deltaTime;
		animator->actualAnimation[0] = 5;
		animator->actualAnimation[1] = 0;
		animator->actualAnimation[0] -= int(animator->time.actualShowingTime / animator->time.showingTime) % 2;
	}
	else 
		checkPlayerStandingAnimation(stage, animator);
}

void checkPlayerClimbingAnimation(Stage* stage, Animator* animator)
{
	if (stage->player.climbUp)
	{
		animator->changeAnimation = true;
		animator->time.actualShowingTime += stage->gameInfo.deltaTime;
		animator->actualAnimation[0] = 3;
		animator->actualAnimation[1] = 1;
		animator->actualAnimation[0] += int(animator->time.actualShowingTime / animator->time.showingTime) % 2;
	}
	else if (stage->player.climbDown)
	{
		animator->changeAnimation = true;
		animator->time.actualShowingTime += stage->gameInfo.deltaTime;
		animator->actualAnimation[0] = 4;
		animator->actualAnimation[1] = 1;
		animator->actualAnimation[0] -= int(animator->time.actualShowingTime / animator->time.showingTime) % 2;
	}
}

void checkPlayerJumpingAnimation(Stage* stage, Animator* animator)
{
	if ((stage->player.isJumping || stage->player.fallDown) && stage->player.walkLeft)
	{
		animator->changeAnimation = true;
		animator->actualAnimation[0] = 1;
		animator->actualAnimation[1] = 0;
	}
	else if ((stage->player.isJumping || stage->player.fallDown) && stage->player.walkRight)
	{
		animator->changeAnimation = true;
		animator->actualAnimation[0] = 6;
		animator->actualAnimation[1] = 0;
	}
}

void checkPlayerStandingAnimation(Stage* stage, Animator* animator)
{
	if (animator->actualAnimation[0]==2 || animator->actualAnimation[0] == 3)
	{
		animator->changeAnimation = true;
		animator->actualAnimation[0] = 3;
		animator->actualAnimation[1] = 0;
	}
	else
	{
		animator->changeAnimation = true;
		animator->actualAnimation[0] = 4;
		animator->actualAnimation[1] = 0;
	}
}

void playerAnimations(SDLConst* SDL, Stage* stage, Animator* animator)
{
	checkPlayerAnimation(stage, animator);
	initializeAnimator(stage, animator);
}

void chceckBarrelAnimation(Stage* stage, Animator* animator)
{

}

void barrelAnimations(Stage* stage, Animator* animator)
{

}

void checkAnimaitons(Stage* stage, Animator* animator)
{
	checkPlayerAnimation(stage, animator);
	chceckBarrelAnimation(stage, animator);
}